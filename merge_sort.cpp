#include <iostream>
#include <vector>

/*
Merge Sort is a classic sorting algorithm that follows the "divide and conquer" paradigm.
The basic idea is to break down a problem into smaller, more manageable sub-problems, solve those, and then combine the solutions to solve the original problem.

In the context of sorting an array, Merge Sort works as follows:

1.  **Divide**: The unsorted array is divided into two roughly equal halves. This is the "divide" step. This process is recursive. The array is repeatedly divided until we have sub-arrays containing only one element. An array with a single element is considered inherently sorted.

2.  **Conquer**: This is the "impera" (conquer) part of the strategy. In this phase, we sort the smaller sub-arrays. Since we divide the array until each sub-array has only one element, these sub-arrays are already sorted.

3.  **Combine**: The sorted sub-arrays are then merged back together in a sorted manner. This is the key step. The `merge` function takes two sorted sub-arrays and combines them into a single sorted array. This is done by comparing the elements of the two sub-arrays one by one and placing the smaller element into the new array. This merging process continues until all sub-arrays are combined back into a single sorted array.

The recursion unwinds, and at each step, a merge operation is performed, which is why the algorithm is called "Merge Sort".
*/

// Function to merge two sorted sub-arrays into a single sorted array
void merge(std::vector<int> &arr, int left, int mid, int right)
{
    // Calculate the sizes of the two sub-arrays to be merged
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temporary vectors to hold the data of the two sub-arrays
    std::vector<int> L(n1);
    std::vector<int> R(n2);

    // Copy data to temporary vectors L[] and R[]
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    // Merge the temporary vectors back into arr[left..right]
    int i = 0;    // Initial index of first sub-array
    int j = 0;    // Initial index of second sub-array
    int k = left; // Initial index of merged sub-array

    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], if there are any
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if there are any
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// The main function that implements Merge Sort
// arr[] is the array to be sorted, l is the left index and r is the right index
void mergeSort(std::vector<int> &arr, int left, int right)
{
    if (left < right)
    {
        // Same as (left+right)/2, but avoids overflow for large left and h
        int mid = left + (right - left) / 2;

        // Sort first and second halves
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        // Merge the sorted halves
        merge(arr, left, mid, right);
    }
}

// Utility function to print an array
void printArray(const std::vector<int> &arr)
{
    for (int i = 0; i < arr.size(); i++)
        std::cout << arr[i] << " ";
    std::cout << std::endl;
}

// Main function to test the merge sort algorithm
int main()
{
    std::vector<int> arr = {12, 11, 13, 5, 6, 7};

    std::cout << "Given array is \n";
    printArray(arr);

    mergeSort(arr, 0, arr.size() - 1);

    std::cout << "\nSorted array is \n";
    printArray(arr);
    return 0;
}
// Classe frigorifero con elementi da ordinare