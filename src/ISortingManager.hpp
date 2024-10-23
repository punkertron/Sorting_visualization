#ifndef ISORTING_MANAGER_HPP
#define ISORTING_MANAGER_HPP

#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "ISortingAlgorithm.hpp"

class ISortingManager {
public:
    virtual ~ISortingManager() = default;
    virtual void start(const int numberOfElements,
                       const std::unordered_set<std::unique_ptr<ISortingAlgorithm>> algorithms) = 0;
    virtual const std::unordered_map<const char*, const std::vector<int>*> getDataFromAlgo(int amountOfSwap) = 0;
};

#endif  // ISORTING_MANAGER_HPP