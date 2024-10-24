#include "MergeSort.hpp"

void mergeInPlace(std::vector<int>& arr, int left, int mid, int right, ConcurrentQueue<SwappedPositions>& swappedPositions,
                  ISortingAlgorithm::swapFunc swapAndAddChangesToQueue)
{
    int start = left;
    int start2 = mid + 1;

    // If the direct merge is already sorted
    if (arr[mid] <= arr[start2]) {
        return;
    }

    while (start <= mid && start2 <= right) {
        // If the element at start is less than or equal to element at start2, it's in the right place
        if (arr[start] <= arr[start2]) {
            start++;
        } else {
            // arr[start] > arr[start2], need to swap and shift elements
            int index = start2;

            // Swap and shift the elements to maintain order
            while (index != start) {
                swapAndAddChangesToQueue(arr, index, index - 1, swappedPositions);
                index--;
            }
            // Update pointers
            start++;
            mid++;
            start2++;
        }
    }
}

// Recursive merge sort function
static void mergeSortInPlace(std::vector<int>& arr, int left, int right, ConcurrentQueue<SwappedPositions>& swappedPositions,
                             ISortingAlgorithm::swapFunc swapAndAddChangesToQueue)
{
    if (left < right) {
        int mid = left + (right - left) / 2;

        // Sort first half
        mergeSortInPlace(arr, left, mid, swappedPositions, swapAndAddChangesToQueue);

        // Sort second half
        mergeSortInPlace(arr, mid + 1, right, swappedPositions, swapAndAddChangesToQueue);

        // Merge the sorted halves
        mergeInPlace(arr, left, mid, right, swappedPositions, swapAndAddChangesToQueue);
    }
}

// Public sort function
void MergeSort::sort(std::vector<int> arr, ConcurrentQueue<SwappedPositions>& swappedPositions)
{
    if (arr.empty() || arr.size() == 1) {
        // Array is already sorted
        return;
    }

    mergeSortInPlace(arr, 0, arr.size() - 1, swappedPositions, swapAndAddChangesToQueue);
}