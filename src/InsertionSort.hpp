#ifndef INSERTION_SORT_HPP
#define INSERTION_SORT_HPP

#include <vector>

#include "ConcurrentQueue.hpp"
#include "ISortingAlgorithm.hpp"
#include "SwappedPositions.hpp"

class InsertionSort : public ISortingAlgorithm {
private:
    void sort(std::vector<int> vector, ConcurrentQueue<SwappedPositions>& swappedPositions) override;
    const char* getName() const override
    {
        return "Insertion sort";
    }
};

#endif  // INSERTION_SORT_HPP