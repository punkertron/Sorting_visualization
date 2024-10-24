#include "SortingManager.hpp"

#include <algorithm>
#include <thread>

SortingManager::SortingManager() : rng(rd())
{
}

const std::vector<int> SortingManager::createData(const int numberOfElements)
{
    std::vector<int> res(numberOfElements);
    std::iota(res.begin(), res.end(), 1);
    std::shuffle(res.begin(), res.end(), rng);
    return res;
}

void SortingManager::start(const int numberOfElements, const std::vector<std::unique_ptr<ISortingAlgorithm>> algorithms)
{
    auto dataToSort = createData(numberOfElements);

    for (const auto& a : algorithms) {
        algoNames.push_back(a->getName());
        changesInData.push_back(std::make_unique<ConcurrentQueue<SwappedPositions>>());
        sortedData.push_back(dataToSort);

        std::thread th([&] {
            a->sort(dataToSort, *changesInData.back());
        });
        if (th.joinable()) {
            th.join();
        }
    }
}

const std::vector<std::pair<const char*, const std::vector<int>*>> SortingManager::getDataFromAlgo(int amountOfSwap)
{
    std::vector<std::pair<const char*, const std::vector<int>*>> res;
    for (int i = 0; i < algoNames.size(); ++i) {
        std::vector<int>* v = &sortedData[i];
        int j = amountOfSwap;
        while (j > 0) {
            auto swappedPositions = changesInData[i]->try_pop_front();
            if (swappedPositions) {
                std::swap((*v)[swappedPositions->first], (*v)[swappedPositions->second]);
            }
            --j;
        }
        res.push_back({algoNames[i], v});
    }
    return res;
}
