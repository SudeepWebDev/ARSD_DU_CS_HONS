#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int partition(vector<int> &arr, int low, int high)
{
    int pivot = arr[high], i = low - 1;
    for (int j = low; j < high; j++)
        if (arr[j] < pivot)
            swap(arr[++i], arr[j]);
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

int randomisedSelect(vector<int> &arr, int low, int high, int k)
{
    if (low == high)
        return arr[low];
    int pivotIndex = partition(arr, low, high);
    if (k == pivotIndex)
        return arr[k];
    return k < pivotIndex ? randomisedSelect(arr, low, pivotIndex - 1, k) : randomisedSelect(arr, pivotIndex + 1, high, k);
}

int main()
{
    vector<int> arr = {5, 2, 9, 1, 7, 6, 3};
    int k = 3;
    cout << "The " << k << "th smallest element is: " << randomisedSelect(arr, 0, arr.size() - 1, k - 1) << endl;
    return 0;
}