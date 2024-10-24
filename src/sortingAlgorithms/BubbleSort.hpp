#ifndef BUBBLE_SORT_HPP
#define BUBBLE_SORT_HPP

#include <vector>

#include "../ConcurrentQueue.hpp"
#include "../SwappedPositions.hpp"
#include "ISortingAlgorithm.hpp"

class BubbleSort : public ISortingAlgorithm {
private:
    void sort(std::vector<int> vector, ConcurrentQueue<SwappedPositions>& swappedPositions) override;
    const char* getName() const override
    {
        return "Bubble sort";
    }
};

#endif  // BUBBLE_SORT_HPP