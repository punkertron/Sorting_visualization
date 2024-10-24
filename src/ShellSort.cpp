#include "ShellSort.hpp"

static void shellSort(std::vector<int>& vector, ConcurrentQueue<SwappedPositions>& swappedPositions,
                      ISortingAlgorithm::swapFunc swapAndAddChangesToQueue)
{
    int n = vector.size();

    // Start with a big gap, then reduce the gap
    for (int gap = n / 2; gap > 0; gap /= 2) {
        // Do a gapped insertion sort for this gap size
        for (int i = gap; i < n; i++) {
            int temp = vector[i];
            int j = i;

            // Record the comparison step
            // swapAndAddChangesToQueue(vector, 0, 0, swappedPositions);

            // Shift earlier gap-sorted elements up until the correct location for vector[i] is found
            while (j >= gap && vector[j - gap] > temp) {
                // Record the comparison step
                // swapAndAddChangesToQueue(vector, 0, 0, swappedPositions);

                vector[j] = vector[j - gap];
                // Record the "swap" even though we're moving elements
                swapAndAddChangesToQueue(vector, j, j - gap, swappedPositions);

                j -= gap;
            }

            // Put temp (the original vector[i]) in its correct location
            vector[j] = temp;
            // Record the assignment as a swap with same indices
            // swapAndAddChangesToQueue(vector, j, j, swappedPositions);
        }
    }
}

void ShellSort::sort(std::vector<int> vector, ConcurrentQueue<SwappedPositions>& swappedPositions)
{
    if (vector.empty() || vector.size() == 1) {
        // Array is already sorted
        return;
    }

    shellSort(vector, swappedPositions, swapAndAddChangesToQueue);
}
