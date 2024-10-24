#ifndef SHELL_SORT_HPP
#define SHELL_SORT_HPP

#include <vector>

#include "../ConcurrentQueue.hpp"
#include "../SwappedPositions.hpp"
#include "ISortingAlgorithm.hpp"

class ShellSort : public ISortingAlgorithm {
private:
    void sort(std::vector<int> vector, ConcurrentQueue<SwappedPositions>& swappedPositions) override;
    const char* getName() const override
    {
        return "Shellsort";
    }
};

#endif  // SHELL_SORT_HPP