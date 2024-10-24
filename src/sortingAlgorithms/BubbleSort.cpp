#include "BubbleSort.hpp"

void BubbleSort::sort(std::vector<int> vector, ConcurrentQueue<SwappedPositions>& swappedPositions)
{
    for (int i = 0; i < vector.size(); ++i) {
        for (int j = i + 1; j < vector.size(); ++j) {
            if (vector[j] < vector[i]) {
                swapAndAddChangesToQueue(vector, i, j, swappedPositions);
            }
        }
    }
}