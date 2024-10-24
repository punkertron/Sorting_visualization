#ifndef ISORTING_MANAGER_HPP
#define ISORTING_MANAGER_HPP

#include <memory>
#include <utility>
#include <vector>

#include "sortingAlgorithms/ISortingAlgorithm.hpp"

class ISortingManager {
public:
    virtual ~ISortingManager() = default;
    virtual void start(const int numberOfElements, const std::vector<std::unique_ptr<ISortingAlgorithm>> algorithms) = 0;
    virtual const std::vector<std::pair<const char*, const std::vector<int>*>> getDataFromAlgo(int amountOfSwap) = 0;
};

#endif  // ISORTING_MANAGER_HPP