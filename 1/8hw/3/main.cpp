#include <iostream>

using namespace std;

void dfs(int vertex, int color, int used[], int **matrix, int numberOfVertex)
{
    used[vertex] = color;
    for (int i = 0; i < numberOfVertex; i++)
    {
        if (matrix[vertex][i] == 1 && used[i] == 0)
        {
            dfs(i, color, used, matrix, numberOfVertex);
        }
    }
}

int main()
{
    setlocale(LC_ALL, "rus");
    cout << "Программа выводи компненты связности графа" << endl;
    cout << "Введите количество вершин в графе" << endl;
    int numberOfVertex = 0;
    cin >> numberOfVertex;
    cout << "Введите матрицу смежности графа" << endl;
    int **matrix = new int*[numberOfVertex];
    int *used = new int[numberOfVertex];
    for (int i = 0; i < numberOfVertex; i++)
    {
        matrix[i] = new int[numberOfVertex];
        used[i] = 0;
        for (int j = 0; j < numberOfVertex; j++)
        {
            cin >> matrix[i][j];
        }
    }
    int color = 0;
    for (int i = 0; i < numberOfVertex; i++)
    {
        if (used[i] == 0)
        {
            color++;
            dfs(i, color, used, matrix, numberOfVertex);
        }
    }
    for (int i = 0; i < numberOfVertex; i++)
    {
        delete[] matrix[i];
    }
    delete[] matrix;
    cout << "Компоненты связности:\n";
    for (int i = 1; i <= color; i++)
    {
        cout << i << ": ";
        for (int j = 0; j < numberOfVertex; j++)
        {
            if (used[j] == i)
            {
                cout << j + 1 << " ";
            }
        }
        cout << endl;
    }
    delete[] used;
    return 0;
}

