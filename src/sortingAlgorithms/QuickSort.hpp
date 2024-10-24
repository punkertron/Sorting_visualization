#ifndef QUICK_SORT_HPP
#define QUICK_SORT_HPP

#include <vector>

#include "../ConcurrentQueue.hpp"
#include "../SwappedPositions.hpp"
#include "ISortingAlgorithm.hpp"

class QuickSort : public ISortingAlgorithm {
private:
    void sort(std::vector<int> vector, ConcurrentQueue<SwappedPositions>& swappedPositions) override;
    const char* getName() const override
    {
        return "Quick sort";
    }
};

#endif  // QUICK_SORT_HPP