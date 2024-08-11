#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

int randomisedSelect(vector<int> &arr, int left, int right, int k)
{
    if (left == right)
        return arr[left];
    srand(time(nullptr));
    int pivot_index = left + rand() % (right - left + 1);
    swap(arr[pivot_index], arr[right]);
    int pivot = arr[right], i = left;
    for (int j = left; j < right; j++)
        if (arr[j] < pivot)
            swap(arr[i++], arr[j]);
    swap(arr[i], arr[right]);

    if (k == i)
        return arr[k];
    return k < i ? randomisedSelect(arr, left, i - 1, k) : randomisedSelect(arr, i + 1, right, k);
}

int main()
{
    vector<int> arr = {5, 2, 9, 1, 7, 6, 3};
    int k = 2;
    cout << "The " << k << "th smallest element is: " << randomisedSelect(arr, 0, arr.size() - 1, k - 1) << endl;
    for (int num : arr)
        cout << num << " ";
    cout << endl;
    return 0;
}
