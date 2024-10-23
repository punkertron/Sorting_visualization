#include "HeapSort.hpp"

// Heapify a subtree rooted with node i, which is an index in arr[]
void heapify(std::vector<int>& vector, int n, int i, ConcurrentQueue<SwappedPositions>& swappedPositions,
             ISortingAlgorithm::swapFunc swapAndAddChangesToQueue)
{
    int largest = i;        // Initialize largest as root
    int left = 2 * i + 1;   // Left child
    int right = 2 * i + 2;  // Right child

    // Record the comparison step
    // swapAndAddChangesToQueue(arr, 0, 0, swappedPositions);

    // If left child exists and is greater than root
    if (left < n && vector[left] > vector[largest]) {
        largest = left;
    }

    // Record the comparison step
    // swapAndAddChangesToQueue(arr, 0, 0, swappedPositions);

    // If right child exists and is greater than largest so far
    if (right < n && vector[right] > vector[largest]) {
        largest = right;
    }

    // If largest is not root
    if (largest != i) {
        swapAndAddChangesToQueue(vector, i, largest, swappedPositions);

        // Recursively heapify the affected subtree
        heapify(vector, n, largest, swappedPositions, swapAndAddChangesToQueue);
    }
    // else {
    //     // Record the step when no swap is needed
    //     swapAndAddChangesToQueue(arr, 0, 0, swappedPositions);
    // }
}

// Heap Sort function
void heapSort(std::vector<int>& vector, ConcurrentQueue<SwappedPositions>& swappedPositions,
              ISortingAlgorithm::swapFunc swapAndAddChangesToQueue)
{
    int n = vector.size();

    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(vector, n, i, swappedPositions, swapAndAddChangesToQueue);
    }

    // One by one extract elements from heap
    for (int i = n - 1; i > 0; i--) {
        // Move current root to end
        // swapAndAddChangesToQueue(vector, 0, 0, swappedPositions); // Record the step
        swapAndAddChangesToQueue(vector, 0, i, swappedPositions);

        // Call max heapify on the reduced heap
        heapify(vector, i, 0, swappedPositions, swapAndAddChangesToQueue);
    }
}

void HeapSort::sort(std::vector<int> vector, ConcurrentQueue<SwappedPositions>& swappedPositions)
{
    if (vector.empty() || vector.size() == 1) {
        // Array is already sorted
        return;
    }

    heapSort(vector, swappedPositions, swapAndAddChangesToQueue);
}