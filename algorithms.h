//
// Created by Hamad on 10/11/2024.
//

#ifndef ALGORITHMS_H
#define ALGORITHMS_H
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

void merge(int leftArr[], int rightArr[], int leftSize, int rightSize, int sorted[])
{
    int left = 0;
    int right = 0;
    int sortIndex = 0;
    while (left < leftSize && right < rightSize)
        sorted[sortIndex++] =
            (leftArr[left] < rightArr[right]) ? leftArr[left++] : rightArr[right++];

    while (left < leftSize)
        sorted[sortIndex++] = leftArr[left++];

    while (right < rightSize)
        sorted[sortIndex++] = rightArr[right++];
}

void merge_sort(int arr[], int size, int sorted[])
{
    if (size == 1)
    {
        sorted[0] = arr[0];
        return;
    }

    int mid = size / 2;

    int *leftArr = new int[mid];
    int *rightArr = new int[size - mid];

    copy(arr, arr + mid, leftArr);
    copy(arr + mid, arr + size, rightArr);

    int *leftSorted = new int[mid];
    int *rightSorted = new int[size - mid];

    merge_sort(leftArr, mid, leftSorted);
    merge_sort(rightArr, size - mid, rightSorted);

    merge(leftSorted, rightSorted, mid, size - mid, sorted);

    delete[] leftArr;
    delete[] rightArr;
    delete[] leftSorted;
    delete[] rightSorted;
}

int partition(int arr[], int start, int end)
{
    int pivot = arr[end];
    int leftPartion = start;

    for (int i = start; i < end; i++)
    {
        if (arr[i] < pivot)
            swap(arr[leftPartion++], arr[i]);
    }

    swap(arr[leftPartion], arr[end]);
    return leftPartion;
}

void quickSort(int arr[], int start, int end)
{
    if (start >= end)
        return;

    int pivot = partition(arr, start, end);
    quickSort(arr, start, pivot - 1);
    quickSort(arr, pivot + 1, end);
}

int binarySearch(int arr[], int target, int low, int high)
{
    if (low > high)
        return -1;

    int mid = low + (high - low) / 2; // (low + high) / 2 is valid but can cause overflow if both low and high equal to INT_MAX value (2^31 - 1).

    if (arr[mid] > target)
        return binarySearch(arr, target, low, mid - 1);

    if (arr[mid] < target)
        return binarySearch(arr, target, mid + 1, high);

    return mid;
}

vector<int> reverseArray(vector<int> a)
{
    int size = a.size();
    for (int i = 0; i < size / 2; i++)
        swap(a[i], a[size - 1 - i]);
    return a;
}

vector<int> rotateLeft(int d, vector<int> arr)
{
    int size = arr.size();

    vector<int> res(size);
    for (int i = 0; i < size; i++)
        res[i] = arr[d++ % size];

    return res;
}
void insertionSort(int arr[], int size)
{
    for (int current = 1; current < size; current++)
    {
        int prevIndex = current - 1;
        int currentItem = arr[current];
        while (prevIndex >= 0 && arr[prevIndex] > currentItem)
        {
            arr[prevIndex + 1] = arr[prevIndex];
            prevIndex--;
        }
        arr[prevIndex + 1] = currentItem;
    }
}

void merge2(int leftArray[], int leftStart, int leftEnd,    // merge leftArray[leftStart..leftEnd]
            int rightArray[], int rightStart, int rightEnd, // and rightArray[rightStart..rightEnd]
            int mergedArray[])
{ // into mergedArray[mergedStart...]

    int leftIndex = leftStart;
    int rightIndex = rightStart;
    int mergedIndex = 0;

    // Merge elements from both arrays in sorted order
    while (leftIndex <= leftEnd && rightIndex <= rightEnd)
    {
        if (leftArray[leftIndex] <= rightArray[rightIndex])
            mergedArray[mergedIndex++] = leftArray[leftIndex++];
        else
            mergedArray[mergedIndex++] = rightArray[rightIndex++];
    }

    // Copy any remaining elements from leftArray
    while (leftIndex <= leftEnd)
        mergedArray[mergedIndex++] = leftArray[leftIndex++];

    // Copy any remaining elements from rightArray
    while (rightIndex <= rightEnd)
        mergedArray[mergedIndex++] = rightArray[rightIndex++];
}
void mergeSort2(int arr[], int start, int end)
{
    // Base case: If the array has one element, it is already sorted
    if (start == end)
        return;

    int mid = (start + end) / 2;

    // Recursively sort the left half
    mergeSort2(arr, start, mid);

    // Recursively sort the right half
    mergeSort2(arr, mid + 1, end);

    // Merge the two sorted halves back into arr
    int *tempArray = new int[end - start + 1];
    merge2(arr, start, mid, arr, mid + 1, end, tempArray);

    // Copy the sorted result from tempArray back to the original array
    for (int i = 0; i <= end - start; ++i)
        arr[start + i] = tempArray[i];

    delete[] tempArray; // Clean up the temporary array
}
#endif //ALGORITHMS_H
