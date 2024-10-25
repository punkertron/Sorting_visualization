#include "SortingManager.hpp"

#include <algorithm>
#include <functional>
#include <numeric>  // for iota
#include <optional>
#include <thread>

#include "sortingAlgorithms/ISortingAlgorithm.hpp"

SortingManager::SortingManager() : rng_(rd_())
{
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

void SortingManager::start(const int numberOfElements, const std::vector<std::unique_ptr<ISortingAlgorithm>> algorithms)
{
    // cleanup old data if needed
    cleanupVector(changesInData_);
    cleanupVector(sortedData_);
    cleanupVector(algoNames_);
    cleanupVector(algoFinished_);

    auto dataToSort = createData(numberOfElements);

    for (const auto& a : algorithms) {
        algoNames_.push_back(a->getName());
        changesInData_.push_back(std::make_unique<ConcurrentQueue<SwappedPositions>>());
        sortedData_.push_back(dataToSort);
        algoFinished_.push_back(false);

        std::thread th([&] {
            a->sort(dataToSort, *changesInData_.back());
            algoFinished_.back() = true;
        });
        if (th.joinable()) {
            th.join();
        }
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
    return std::ranges::all_of(algoFinished_, std::identity{}) &&
           std::ranges::all_of(changesInData_, [](const std::unique_ptr<ConcurrentQueue<SwappedPositions>>& inner) {
               return inner->size() == 0;
           });
}
