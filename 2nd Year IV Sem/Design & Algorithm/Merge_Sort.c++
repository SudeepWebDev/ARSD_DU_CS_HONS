#include <iostream>
using namespace std;

void merge(int arr[], int l, int m, int r)
{
    int comp;
    int n1 = m - l + 1;
    int n2 = r - m;
    int L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + j + 1];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2)
    {
        comp++;
        if (L[i] <= R[j])
            arr[k] = L[i++];
        else
            arr[k] = R[j++];
        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i++];
        k++;
    }
    while (j < n2)
    {
        arr[k] = R[j++];
        k++;
    }
    cout << "\nNo. of comparison: " << comp << endl;
}

void mergeSort(int arr[], int p, int q)
{
    if (p < q)
    {
        int m = (p + q) / 2;
        mergeSort(arr, p, m);
        mergeSort(arr, m + 1, q);
        merge(arr, p, m, q);
    }
}

void insertionSort(int arr[], int n)
{
    int comp;
    for (int i = 1; i < n; i++)
    {
        int key = arr[i];
        int j = i - 1;
        comp++;
        while (j >= 0 && key < arr[j])
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
    cout << "\nNo. of comparison: " << comp << endl;
}

void selectionSort(int arr[], int n)
{
    int i, j, least, comp;
    for (i = 0; i < n - 1; i++)
    {
        least = i;
        for (j = i + 1; j < n; j++)
        {
            comp++;
            if (arr[j] < arr[least])
                least = j;
            if (i != least)
                swap(arr[i], arr[least]);
        }
    }

    cout << "\nNo. of comparison: " << comp << endl;
}

void maxHeapify(int arr[], int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && arr[left] > arr[i])
        largest = left;
    if (right < n && arr[right] > arr[i])
        largest = right;
    if (largest != i)
    {
        swap(arr[i], arr[largest]);
        maxHeapify(arr, n, largest);
    }
}
void minElement(int arr[], int n)
{
    maxHeapify(arr, n, 0);
    int i = n / 2;
    int min = arr[i];
    for (i = n / 2 + 1; i < n; i++)
    {
        if (min > arr[i])
        {
            min = arr[i];
        }
    }
    cout << min << endl;
}
void heapSort(int arr[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        maxHeapify(arr, n, i);

    for (int i = n - 1; i >= 0; i--)
    {
        swap(arr[0], arr[i]);
        maxHeapify(arr, i, 0);
    }
}

int partition(int arr[], int p, int r)
{
    int x = arr[r];
    int i = p - 1;
    for (int j = p; j < r; j++)
    {
        if (arr[j] <= x)
        {
            i = i + 1;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[r]);
    return i + 1;
}

void quickSort(int arr[], int p, int r)
{
    if (p < r)
    {
        int q = partition(arr, p, r);
        quickSort(arr, p, q - 1);
        quickSort(arr, q + 1, r);
    }
}
void countSort(int arr[], int size)
{

    int output[size];
    int max = arr[0];
    for (int i = 1; i < size; i++)
    {
        if (arr[i] > max)
            max = arr[i];
    }
    int count[max];
    for (int i = 0; i <= max; ++i)
        count[i] = 0;

    for (int i = 0; i < size; i++)
        count[arr[i]]++;

    for (int i = 1; i <= max; i++)
        count[i] += count[i - 1];

    for (int i = size - 1; i >= 0; i--)
    {
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }

    for (int i = 0; i < size; i++)
        arr[i] = output[i];
}
void printArr(int arr[], int n)
{
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}

void inputArr(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << "Enter Your " << i + 1 << " Element: ";
        cin >> arr[i];
    }
}

int main()
{
    int arr[] = {};
    int size;
    cout << "Enter the number of elements in your array: ";
    cin >> size;
    inputArr(arr, size);
    cout << endl;

    cout << "Original array: ";
    printArr(arr, size);

    // mergeSort(arr, 0, size - 1);
    // cout << "Array sorted by merge sort: ";
    // printArr(arr, size);

    // insertionSort(arr, size);
    // cout << "Array sorted by insertion sort: ";
    // printArr(arr, size);

    // selectionSort(arr, size);
    // cout << "Array sorted by selection sort: ";
    // printArr(arr, size);

    // heapSort(arr, size);
    // cout << "Array sorted by heap sort: ";
    // printArr(arr, size);

    // minElement(arr, size);
    // printArr(arr, size);

    // quickSort(arr, 0, size - 1);
    // cout << "Array sorted by quick sort: ";
    // printArr(arr, size);

    countSort(arr, size);
    cout << "Array sorted by count sort: ";
    printArr(arr, size);

    return 0;
}
