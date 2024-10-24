#include "QuickSort.hpp"

#include <iostream>

// Partition function for Quick Sort
int partition(std::vector<int>& arr, int low, int high, ConcurrentQueue<SwappedPositions>& swappedPositions,
              ISortingAlgorithm::swapFunc swapAndAddChangesToQueue)
{
    int pivot = arr[high];
    int i = low - 1;  // Index of smaller element

    for (int j = low; j <= high - 1; j++) {
        // Record the comparison step
        // swapAndAddChangesToQueue(arr, 0, 0, swappedPositions);

        // If current element is smaller than or equal to pivot
        if (arr[j] <= pivot) {
            i++;
            // Swap arr[i] and arr[j]
            if (i != j) {
                swapAndAddChangesToQueue(arr, i, j, swappedPositions);
            }
            // else {
            //     // Record the step when no swap is needed
            //     swapAndAddChangesToQueue(arr, 0, 0, swappedPositions);
            // }
        }
        // else {
        //     // Record the step when no swap is needed
        //     swapAndAddChangesToQueue(arr, 0, 0, swappedPositions);
        // }
    }
    // Swap arr[i+1] and arr[high] (or pivot)
    if (i + 1 != high) {
        swapAndAddChangesToQueue(arr, i + 1, high, swappedPositions);
    }
    // else {
    //     swapAndAddChangesToQueue(arr, 0, 0, swappedPositions);
    // }
    return i + 1;
}

// Quick Sort recursive function
void quickSort(std::vector<int>& arr, int low, int high, ConcurrentQueue<SwappedPositions>& swappedPositions,
               ISortingAlgorithm::swapFunc swapAndAddChangesToQueue)
{
    if (low < high) {
        int pi = partition(arr, low, high, swappedPositions, swapAndAddChangesToQueue);

        // Separately sort elements before and after partition
        quickSort(arr, low, pi - 1, swappedPositions, swapAndAddChangesToQueue);
        quickSort(arr, pi + 1, high, swappedPositions, swapAndAddChangesToQueue);
    }
}

void QuickSort::sort(std::vector<int> vector, ConcurrentQueue<SwappedPositions>& swappedPositions)
{
    quickSort(vector, 0, vector.size() - 1, swappedPositions, swapAndAddChangesToQueue);
}
