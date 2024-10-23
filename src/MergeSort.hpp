#ifndef MERGE_SORT_HPP
#define MERGE_SORT_HPP

#include <vector>

#include "ConcurrentQueue.hpp"
#include "ISortingAlgorithm.hpp"
#include "SwappedPositions.hpp"

class MergeSort : public ISortingAlgorithm {
private:
    void mergeInPlace(std::vector<int>& vector, int left, int mid, int right, ConcurrentQueue<SwappedPositions>& swappedPositions);
    void mergeSortInPlace(std::vector<int>& vector, int left, int right, ConcurrentQueue<SwappedPositions>& swappedPositions);

    void sort(std::vector<int> vector, ConcurrentQueue<SwappedPositions>& swappedPositions) override;
    const char* getName() const override
    {
        return "Merge sort";
    }
};

#endif  // MERGE_SORT_HPP