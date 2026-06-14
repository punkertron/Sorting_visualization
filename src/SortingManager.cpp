#include "SortingManager.hpp"

#include <algorithm>
#include <numeric>  // for iota
#include <optional>

#include "sortingAlgorithms/ISortingAlgorithm.hpp"

SortingManager::SortingManager() : rng_(rd_())
{
}

SortingManager::~SortingManager()
{
    joinSortingThreads();
}

const std::vector<int> SortingManager::createData(const int numberOfElements)
{
    std::vector<int> res(numberOfElements);
    std::iota(res.begin(), res.end(), 1);
    std::shuffle(res.begin(), res.end(), rng_);
    return res;
}

template <typename T>
static void cleanupVector(std::vector<T>& v)
{
    v.clear();
    v.shrink_to_fit();
}

void SortingManager::joinSortingThreads()
{
    for (auto& thread : sortingThreads_) {
        if (thread.joinable()) {
            thread.join();
        }
    }
    cleanupVector(sortingThreads_);
}

void SortingManager::start(const int numberOfElements, std::vector<std::unique_ptr<ISortingAlgorithm>> algorithms)
{
    joinSortingThreads();

    // cleanup old data if needed
    cleanupVector(changesInData_);
    cleanupVector(sortedData_);
    cleanupVector(algoNames_);
    std::vector<std::atomic_bool> newAlgoFinished(algorithms.size());
    algoFinished_.swap(newAlgoFinished);

    const auto dataToSort = createData(numberOfElements);

    changesInData_.reserve(algorithms.size());
    sortedData_.reserve(algorithms.size());
    algoNames_.reserve(algorithms.size());
    sortingThreads_.reserve(algorithms.size());

    for (std::size_t i = 0; i < algorithms.size(); ++i) {
        auto& a = algorithms[i];
        algoNames_.push_back(a->getName());
        changesInData_.push_back(std::make_unique<ConcurrentQueue<SwappedPositions>>());
        sortedData_.push_back(dataToSort);
        algoFinished_[i].store(false, std::memory_order_relaxed);

        auto* changesQueue = changesInData_.back().get();
        auto* finished = &algoFinished_[i];
        sortingThreads_.emplace_back([algorithm = std::move(a), dataToSort, changesQueue, finished]() mutable {
            algorithm->sort(std::move(dataToSort), *changesQueue);
            finished->store(true, std::memory_order_release);
        });
    }
}

const std::vector<std::pair<const char*, const std::vector<int>*>> SortingManager::getDataFromAlgo(int amountOfSwap)
{
    std::vector<std::pair<const char*, const std::vector<int>*>> res;
    for (int i = 0; i < algoNames_.size(); ++i) {
        std::vector<int>* v = &sortedData_[i];
        int j = amountOfSwap;
        while (j > 0) {
            auto swappedPositions = changesInData_[i]->try_pop_front();
            if (swappedPositions) {
                std::swap((*v)[swappedPositions->first], (*v)[swappedPositions->second]);
            }
            --j;
        }
        res.push_back({algoNames_[i], v});
    }
    return res;
}

const std::vector<std::pair<const char*, const std::vector<int>*>> SortingManager::getCurrentData() const
{
    std::vector<std::pair<const char*, const std::vector<int>*>> res;
    for (int i = 0; i < algoNames_.size(); ++i) {
        res.push_back({algoNames_[i], &sortedData_[i]});
    }
    return res;
}

bool SortingManager::isNoMoreDataLeft()
{
    return std::ranges::all_of(algoFinished_,
                               [](const std::atomic_bool& finished) {
                                   return finished.load(std::memory_order_acquire);
                               }) &&
           std::ranges::all_of(changesInData_, [](const std::unique_ptr<ConcurrentQueue<SwappedPositions>>& inner) {
               return inner->size() == 0;
           });
}
