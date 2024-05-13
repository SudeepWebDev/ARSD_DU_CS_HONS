#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <queue>
#include <climits>
// #include <bits/stdc++.h>
using namespace std;

void insertionSort(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && key < arr[j])
            arr[j + 1] = arr[j--];
        arr[j + 1] = key;
    }
}

void merge(int arr[], int l, int m, int r)
{
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

void maxHeapify(int arr[], int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;
    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i)
    {
        swap(arr[i], arr[largest]);
        maxHeapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        maxHeapify(arr, n, i);
    for (int i = n - 1; i > 0; i--)
    {
        swap(arr[0], arr[i]);
        maxHeapify(arr, i, 0);
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
            min = arr[i];
    }
    cout << min << endl;
}

int partition(int arr[], int p, int r)
{
    int x = arr[r];
    int i = p - 1;
    for (int j = p; j < r; j++)
        if (arr[j] < x)
            swap(arr[++i], arr[j]);
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
    int max = arr[0];
    for (int i = 1; i < size; ++i)
        if (arr[i] > max)
            max = arr[i];
    int output[size];
    int count[max + 1];

    for (int i = 0; i <= max; ++i)
        count[i] = 0;

    for (int i = 0; i < size; ++i)
        count[arr[i]]++;

    for (int i = 1; i <= max; ++i)
        count[i] += count[i - 1];

    for (int i = size - 1; i >= 0; --i)
    {
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }

    for (int i = 0; i < size; ++i)
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

// class Graph
// {
// public:
//     map<int, bool> visited;
//     map<int, list<int>> adj;
//     void addEdge(int v, int w)
//     {
//         adj[v].push_back(w);
//         adj[w].push_back(v);
//     }
//     void DFS1(int v)
//     {
//         visited[v] = true;
//         cout << v << " ";
//         for (int neighbor : adj[v])
//             if (!visited[neighbor])
//                 DFS1(neighbor);
//     }
//     void DFS(int v)
//     {
//         stack<int> stack;
//         stack.push(v);
//         while (!stack.empty())
//         {
//             int currentVertex = stack.top();
//             stack.pop();
//             if (!visited[currentVertex])
//             {
//                 visited[currentVertex] = true;
//                 cout << currentVertex << " ";
//                 for (auto it = adj[currentVertex].rbegin(); it != adj[currentVertex].rend(); ++it)
//                     if (!visited[*it])
//                         stack.push(*it);
//             }
//         }
//     }
//     void BFS(int v)
//     {
//         queue<int> queue;
//         queue.push(v);
//         visited[v] = true;
//         while (!queue.empty())
//         {
//             int currentVertex = queue.front();
//             cout << currentVertex << " ";
//             queue.pop();
//             for (int neighbor : adj[currentVertex])
//             {
//                 if (!visited[neighbor])
//                 {
//                     visited[neighbor] = true;
//                     queue.push(neighbor);
//                 }
//             }
//         }
//     }
// };

int knapSack(int n, int W, int v[], int w[])
{
    int k[n + 1][W + 1];
    for (int i = 0; i <= n; i++)
        for (int wt = 0; wt <= W; wt++)
            if (i == 0 || wt == 0)
                k[i][wt] = 0;
            else if (wt >= w[i - 1])
                k[i][wt] = max(v[i - 1] + k[i - 1][wt - w[i - 1]], k[i - 1][wt]);
            else
                k[i][wt] = k[i - 1][wt];
    return k[n][W];
}

vector<vector<int>> addMatrix(const vector<vector<int>> &A, const vector<vector<int>> &B)
{
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
    return C;
}

vector<vector<int>> subtractMatrix(const vector<vector<int>> &A, const vector<vector<int>> &B)
{
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
    return C;
}

void strassenMultiply(const vector<vector<int>> &A, const vector<vector<int>> &B, vector<vector<int>> &C)
{
    int n = A.size();
    if (n == 1)
        C[0][0] = A[0][0] * B[0][0];
    return;

    vector<vector<int>> A11(n / 2, vector<int>(n / 2));
    vector<vector<int>> A12(n / 2, vector<int>(n / 2));
    vector<vector<int>> A21(n / 2, vector<int>(n / 2));
    vector<vector<int>> A22(n / 2, vector<int>(n / 2));
    vector<vector<int>> B11(n / 2, vector<int>(n / 2));
    vector<vector<int>> B12(n / 2, vector<int>(n / 2));
    vector<vector<int>> B21(n / 2, vector<int>(n / 2));
    vector<vector<int>> B22(n / 2, vector<int>(n / 2));

    for (int i = 0; i < n / 2; i++)
        for (int j = 0; j < n / 2; j++)
        {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + n / 2];
            A21[i][j] = A[i + n / 2][j];
            A22[i][j] = A[i + n / 2][j + n / 2];
            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + n / 2];
            B21[i][j] = B[i + n / 2][j];
            B22[i][j] = B[i + n / 2][j + n / 2];
        }

    // Calculate Strassen's products
    vector<vector<int>> M1(n / 2, vector<int>(n / 2));
    vector<vector<int>> M2(n / 2, vector<int>(n / 2));
    vector<vector<int>> M3(n / 2, vector<int>(n / 2));
    vector<vector<int>> M4(n / 2, vector<int>(n / 2));
    vector<vector<int>> M5(n / 2, vector<int>(n / 2));
    vector<vector<int>> M6(n / 2, vector<int>(n / 2));
    vector<vector<int>> M7(n / 2, vector<int>(n / 2));

    strassenMultiply(addMatrix(A11, A22), addMatrix(B11, B22), M1);
    strassenMultiply(addMatrix(A21, A22), B11, M2);
    strassenMultiply(A11, subtractMatrix(B12, B22), M3);
    strassenMultiply(A22, subtractMatrix(B21, B11), M4);
    strassenMultiply(addMatrix(A11, A12), B22, M5);
    strassenMultiply(subtractMatrix(A21, A11), addMatrix(B11, B12), M6);
    strassenMultiply(subtractMatrix(A12, A22), addMatrix(B21, B22), M7);

    // Calculate result matrix C
    vector<vector<int>> C11(n / 2, vector<int>(n / 2));
    vector<vector<int>> C12(n / 2, vector<int>(n / 2));
    vector<vector<int>> C21(n / 2, vector<int>(n / 2));
    vector<vector<int>> C22(n / 2, vector<int>(n / 2));

    C11 = addMatrix(subtractMatrix(addMatrix(M1, M4), M5), M7);
    C12 = addMatrix(M3, M5);
    C21 = addMatrix(M2, M4);
    C22 = addMatrix(subtractMatrix(addMatrix(M1, M3), M2), M6);

    // Combine submatrices into C
    for (int i = 0; i < n / 2; i++)
        for (int j = 0; j < n / 2; j++)
        {
            C[i][j] = C11[i][j];
            C[i][j + n / 2] = C12[i][j];
            C[i + n / 2][j] = C21[i][j];
            C[i + n / 2][j + n / 2] = C22[i][j];
        }
}

void printMatrix(const vector<vector<int>> &matrix)
{
    int n = matrix.size();
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            cout << matrix[i][j] << " ";
        cout << endl;
    }
}

void addEdge(vector<vector<pair<int, int>>> &adjList, int u, int v, int weight) {
    adjList[u].push_back(make_pair(v, weight));
    adjList[v].push_back(make_pair(u, weight));
}

int minKey(int key[], bool mstSet[], int vertices)
{
    int min = INT_MAX, min_index;
    for (int v = 0; v < vertices; v++)
        if (mstSet[v] == false && key[v] < min)
            min = key[v], min_index = v;
    return min_index;
}

void printMST(int parent[], int key[], int vertices)
{
    cout << "Edge \tWeight\n";
    for (int i = 1; i < vertices; i++)
        cout << parent[i] << " - " << i << " \t" << key[i] << " \n";
}

void primMST(vector<vector<pair<int, int>>> &adjList, int vertices)
{
    int parent[vertices];
    int key[vertices];
    bool mstSet[vertices];
    for (int i = 0; i < vertices; i++)
        key[i] = INT_MAX, mstSet[i] = false;
    key[0] = 0;
    parent[0] = -1;
    for (int count = 0; count < vertices - 1; count++)
    {
        int u = minKey(key, mstSet, vertices);
        mstSet[u] = true;
        for (auto edge : adjList[u])
        {
            int v = edge.first;
            int weight = edge.second;
            if (mstSet[v] == false && weight < key[v])
            {
                parent[v] = u;
                key[v] = weight;
            }
        }
    }
    printMST(parent, key, vertices);
}

int main()
{

    int vertices, edges;
    cout << "Enter the number of vertices in the graph: ";
    cin >> vertices;
    vector<vector<pair<int, int>>> adjList(vertices);

    cout << "Enter the number of edges: ";
    cin >> edges;
    for (int j = 0; j < edges; j++)
    {
        int u, v, weight;
        cout << "Enter vertices associated with edge " << j + 1 << " and its weight: ";
        cin >> u >> v >> weight;
        addEdge(adjList, u, v, weight);
    }

    primMST(adjList, vertices);
    return 0;
}

// int main()
// {
//     int n;
//     cout << "Enter the size of matrix" << endl;
//     cin >> n;
//     vector<vector<int>> A(n, vector<int>(n));
//     vector<vector<int>> B(n, vector<int>(n));

//     cout << "Enter the element of the A matrix" << endl;
//     for (int i = 0; i < n; i++)
//         for (int j = 0; j < n; j++)
//         {
//             cout << "Enter the element at A" << i + 1 << j + 1 << endl;
//             cin >> A[i][j];
//         }
//     cout << "Enter the element of the B matrix" << endl;
//     for (int i = 0; i < n; i++)
//         for (int j = 0; j < n; j++)
//         {
//             cout << "Enter the element at B" << i + 1 << j + 1 << endl;
//             cin >> B[i][j];
//         }
//     // int n = A.size();
//     vector<vector<int>> C(n, vector<int>(n));
//     strassenMultiply(A, B, C);
//     cout << "Matrix A:\n";
//     printMatrix(A);
//     cout << "Matrix B:\n";
//     printMatrix(B);
//     cout << "Matrix C (Result of Multiplication):\n";
//     printMatrix(C);
// }
// int main()
// {
//     int weights[] = {10, 20, 30};
//     int values[] = {60, 100, 120};
//     int capacity = 50;

//     int maxProfit = knapSack(3, capacity, values, weights);
//     cout << "Maximum profit: " << maxProfit << endl;

//     return 0;
// }

// int main()
// {
//     Graph g;
//     g.addEdge(0, 1);
//     g.addEdge(0, 2);
//     g.addEdge(1, 2);
//     g.addEdge(2, 0);
//     g.addEdge(2, 3);
//     g.addEdge(3, 3);

//     cout << "Depth First Traversal (starting from vertex 0):\n";
//     g.DFS(2);
//     g.DFS1(2);

//     return 0;
// }

// int main()
// {
// int arr[] = {};
// int size;
// cout << "Enter the number of elements in your array: ";
// cin >> size;
// inputArr(arr, size);
// cout << endl;

// cout << "Original array: ";
// printArr(arr, size);

// // quickSort(arr, 0, size - 1);
// // cout << "Array sorted by quick sort: ";
// // printArr(arr, size);

// countSort(arr, size);
// cout << "Array sorted by count sort: ";
// printArr(arr, size);
// minElement(arr, size);
// }
