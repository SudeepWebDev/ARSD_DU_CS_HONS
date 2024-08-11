#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

void quick_sort(vector<int> &arr, int left, int right)
{
    if (left >= right)
        return;
    srand(time(nullptr));
    int pivot_index = left + rand() % (right - left + 1);
    int pivot = arr[pivot_index], i = left;
    swap(arr[pivot_index], arr[right]);
    for (int j = left; j < right; ++j)
        if (arr[j] < pivot)
            swap(arr[i++], arr[j]);
    swap(arr[i], arr[right]);

    quick_sort(arr, left, i - 1);
    quick_sort(arr, i + 1, right);
}

int main()
{
    vector<int> arr = {3, 6, 8, 10, 1, 2, 1};
    quick_sort(arr, 0, arr.size() - 1);
    for (int num : arr)
        cout << num << " ";
    cout << endl;

    return 0;
}
