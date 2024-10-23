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

void SortingManager::start(const int numberOfElements,
                           const std::unordered_set<std::unique_ptr<ISortingAlgorithm>> algorithms)
{
    auto dataToSort = createData(numberOfElements);
    for (const auto& a : algorithms) {
        algoNames.insert(a->getName());
        changesInData[a->getName()];
        sortedData[a->getName()] = dataToSort;

        std::thread th([&] {
            a->sort(dataToSort, changesInData[a->getName()]);
        });
        if (th.joinable()) {
            th.join();
        }
    }
}

const std::unordered_map<const char*, const std::vector<int>*> SortingManager::getDataFromAlgo(int amountOfSwap)
{
    std::unordered_map<const char*, const std::vector<int>*> res;
    for (const auto& algoName : algoNames) {
        std::vector<int>* v = &sortedData[algoName];
        int i = amountOfSwap;
        while (i > 0) {
            auto swappedPositions = changesInData[algoName].try_pop_front();
            if (swappedPositions) {
                std::swap((*v)[swappedPositions->first], (*v)[swappedPositions->second]);
            }
            --i;
        }
        res[algoName] = v;
    }
    return res;
}