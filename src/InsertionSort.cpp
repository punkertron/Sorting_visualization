#include "InsertionSort.hpp"

void InsertionSort::sort(std::vector<int> vector, ConcurrentQueue<SwappedPositions>& swappedPositions)
{
    for (int i = 1; i < vector.size(); ++i) {
        for (int j = i; j > 0 && vector[j - 1] > vector[j]; --j) {
            swapAndAddChangesToQueue(vector, j, j - 1, swappedPositions);
        }
    }
}