#ifndef HEAP_SORT_HPP
#define HEAP_SORT_HPP

#include <vector>

#include "ConcurrentQueue.hpp"
#include "ISortingAlgorithm.hpp"
#include "SwappedPositions.hpp"

class HeapSort : public ISortingAlgorithm {
private:
    void sort(std::vector<int> vector, ConcurrentQueue<SwappedPositions>& swappedPositions) override;
    const char* getName() const override
    {
        return "Heapsort";
    }
};

#endif  // HEAP_SORT_HPP