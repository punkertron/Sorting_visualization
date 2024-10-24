#ifndef ISORTING_ALGORITHM_HPP
#define ISORTING_ALGORITHM_HPP

#include <algorithm>
#include <functional>
#include <vector>

#include "../ConcurrentQueue.hpp"
#include "../SwappedPositions.hpp"

class ISortingAlgorithm {
public:
    using swapFunc = std::function<void(std::vector<int>& v, int, int, ConcurrentQueue<SwappedPositions>&)>;

protected:
    swapFunc swapAndAddChangesToQueue = [](std::vector<int>& v, int a, int b, ConcurrentQueue<SwappedPositions>& q) {
        q.push_back({a, b});
        std::swap(v[a], v[b]);
    };

public:
    virtual ~ISortingAlgorithm() = default;
    virtual void sort(std::vector<int> vector, ConcurrentQueue<SwappedPositions>& swappedPositions) = 0;
    virtual const char* getName() const = 0;
};

#endif  // ISORTING_ALGORITHM_HPP