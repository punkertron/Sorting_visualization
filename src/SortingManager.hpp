#ifndef SORTING_MODEL_HPP
#define SORTING_MODEL_HPP

#include <memory>
#include <random>
#include <vector>

#include "ConcurrentQueue.hpp"
#include "ISortingManager.hpp"
#include "SwappedPositions.hpp"
#include "sortingAlgorithms/ISortingAlgorithm.hpp"

class SortingManager : public ISortingManager {
private:
    std::vector<std::unique_ptr<ConcurrentQueue<SwappedPositions>>> changesInData;
    std::vector<std::vector<int>> sortedData;
    std::vector<const char*> algoNames;

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

    void start(const int numberOfElements, const std::vector<std::unique_ptr<ISortingAlgorithm>> algorithms) override;
    const std::vector<std::pair<const char*, const std::vector<int>*>> getDataFromAlgo(int amountOfSwap) override;
};

#endif  // SORTING_MODEL_HPP