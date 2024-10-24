#ifndef MERGE_SORT_HPP
#define MERGE_SORT_HPP

#include <vector>

#include "../ConcurrentQueue.hpp"
#include "../SwappedPositions.hpp"
#include "ISortingAlgorithm.hpp"

class MergeSort : public ISortingAlgorithm {
private:
    void sort(std::vector<int> vector, ConcurrentQueue<SwappedPositions>& swappedPositions) override;
    const char* getName() const override
    {
        return "Merge sort";
    }
};

#endif  // MERGE_SORT_HPP