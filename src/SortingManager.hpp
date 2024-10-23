#ifndef SORTING_MODEL_HPP
#define SORTING_MODEL_HPP

#include <memory>
#include <random>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "ConcurrentQueue.hpp"
#include "ISortingAlgorithm.hpp"
#include "ISortingManager.hpp"
#include "SwappedPositions.hpp"

class SortingManager : public ISortingManager {
private:
    std::unordered_map<const char*, ConcurrentQueue<SwappedPositions>> changesInData;
    std::unordered_map<const char*, std::vector<int>> sortedData;
    std::unordered_set<const char*> algoNames;

    const std::vector<int> createData(const int numberOfElements);
    std::random_device rd;
    std::mt19937 rng;

public:
    SortingManager();
    ~SortingManager() = default;
    SortingManager(const SortingManager&) = delete;
    SortingManager(SortingManager&&) = delete;
    SortingManager& operator=(const SortingManager&) = delete;
    SortingManager& operator=(SortingManager&&) = delete;

    void start(const int numberOfElements, const std::unordered_set<std::unique_ptr<ISortingAlgorithm>> algorithms) override;
    const std::unordered_map<const char*, const std::vector<int>*> getDataFromAlgo(int amountOfSwap) override;
};

#endif  // SORTING_MODEL_HPP