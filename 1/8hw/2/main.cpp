#include <iostream>
#include <limits.h>

using namespace std;

int min(int a, int b)
{
    return a < b ? a : b;
}

int extractMin(int numberOfVertex, int distance[], bool isProcessed[])
{
    int minDistance = INT_MAX;
    int indexMin = -1;
    for (int i = 0; i < numberOfVertex; i++)
    {
        if (distance[i] < minDistance && !isProcessed[i])
        {
            minDistance = distance[i];
            indexMin = i;
        }
    }
    return indexMin;
}

void dijkstra(int startVertex, int numberOfVertex, int **matrix, int distance[], int parent[])
{
    bool *isProcessed = new bool[numberOfVertex];
    for (int i = 0; i < numberOfVertex; i++)
    {
        distance[i] = INT_MAX;
        isProcessed[i] = false;
    }
    distance[startVertex] = 0;
    parent[startVertex] = -1;
    int minVertex = startVertex;
    while (minVertex != -1)
    {
        for (int i = 0; i < numberOfVertex; i++)
        {
            if (matrix[minVertex][i] > 0)
                if (distance[minVertex] + matrix[minVertex][i] < distance[i])
                {
                    distance[i] = distance[minVertex] + matrix[minVertex][i];
                    parent[i] = minVertex;
                }
        }
        isProcessed[minVertex] = true;
        minVertex = extractMin(numberOfVertex, distance, isProcessed);
    }
    delete[] isProcessed;
}

void qSort(int left, int right, int distance[], int parent[], int index[])
{
    int leftIndex = left;
    int rightIndex = right;
    int comparingElement = distance[(left + right) / 2];
    while (leftIndex < rightIndex)
    {
        while (distance[leftIndex] < comparingElement)
        {
            leftIndex++;
        }
        while (distance[rightIndex] > comparingElement)
        {
            rightIndex--;
        }
        if (leftIndex <= rightIndex)
        {
            swap(distance[leftIndex], distance[rightIndex]);
            swap(parent[leftIndex], parent[rightIndex]);
            swap(index[leftIndex], index[rightIndex]);
            leftIndex++;
            rightIndex--;
        }
    }
    if (leftIndex < right)
    {
        qSort(leftIndex, right, distance, parent, index);
    }
    if (rightIndex > left)
    {
        qSort(left, rightIndex, distance, parent, index);
    }
}

int main()
{
    setlocale(LC_ALL, "rus");
    cout << "Введите кол-во городов и дорог" << endl;
    int n = 0, m = 0;
    cin >> n >> m;
    int **matrix = new int*[n];
    for (int i = 0; i < n; i++)
    {
        matrix[i] = new int[n];
    }
    cout << "Введите дороги" << endl;
    for (int i = 0; i < m; i++)
    {
        int a = 0, b = 0, len = 0;
        cin >> a >> b >> len;
        matrix[a - 1][b - 1] = len;
        matrix[b - 1][a - 1] = len;
    }
    int *distance = new int[n];
    int *parent = new int[n];
    dijkstra(0, n, matrix, distance, parent);
    for (int i = 0; i < n; i++)
    {
        delete[] matrix[i];
    }
    delete[] matrix;
    int *index = new int[n];
    for (int i = 0; i < n; i++)
    {
        index[i] = i;
    }
    qSort(0, n - 1, distance, parent, index);
    int *indexAfterSort = new int[n];
    for (int i = 0; i < n; i++)
    {
        indexAfterSort[index[i]] = i;
    }
    int *path = new int[n];
    cout << "Порядок захвата городов:" << endl;
    for (int i = 1; i < n; i++)
    {
        int count = 0;
        int currentVertex = index[i];
        while (currentVertex > 0)
        {
            path[count++] = currentVertex;
            currentVertex = parent[indexAfterSort[currentVertex]];
        }
        path[count] = index[0];
        cout << "Город " << index[i] + 1 << ", расстояние " << distance[i] << ", путь: ";
        for (int i = count; i >= 0; i--)
        {
            cout << path[i] + 1 << " ";
        }
        cout << endl;
    }
    delete[] index;
    delete[] indexAfterSort;
    delete[] distance;
    delete[] parent;
    delete[] path;
    return 0;
}
