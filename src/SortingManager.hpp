#ifndef SORTING_MODEL_HPP
#define SORTING_MODEL_HPP

#include <atomic>
#include <memory>
#include <random>
#include <thread>
#include <utility>
#include <vector>

#include "ConcurrentQueue.hpp"
#include "ISortingManager.hpp"
#include "SwappedPositions.hpp"

class ISortingAlgorithm;

class SortingManager : public ISortingManager {
private:
    std::vector<std::unique_ptr<ConcurrentQueue<SwappedPositions>>> changesInData_;
    std::vector<std::vector<int>> sortedData_;
    std::vector<const char*> algoNames_;
    std::vector<std::atomic_bool> algoFinished_;
    std::vector<std::thread> sortingThreads_;

    const std::vector<int> createData(const int numberOfElements);
    void joinSortingThreads();
    std::random_device rd_;
    std::mt19937 rng_;

public:
    SortingManager();
    ~SortingManager() override;
    SortingManager(const SortingManager&) = delete;
    SortingManager(SortingManager&&) = delete;
    SortingManager& operator=(const SortingManager&) = delete;
    SortingManager& operator=(SortingManager&&) = delete;

    void start(const int numberOfElements, std::vector<std::unique_ptr<ISortingAlgorithm>> algorithms) override;
    const std::vector<std::pair<const char*, const std::vector<int>*>> getDataFromAlgo(int amountOfSwap) override;
    const std::vector<std::pair<const char*, const std::vector<int>*>> getCurrentData() const override;
    bool isNoMoreDataLeft() override;
};

#endif  // SORTING_MODEL_HPP
