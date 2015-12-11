#include <iostream>
#include <fstream>

using namespace std;

const int maxLen = 256;

void dfs(int vertex, int numberOfVertex, int **matrix, char *names, char &name)
{
    names[vertex] = name;
    for (int i = 0; i < numberOfVertex; i++)
    {
        if (matrix[vertex][i] > 0 && names[i] == '\0')
        {
            name++;
            dfs(i, numberOfVertex, matrix, names, name);
        }
    }
}

int main()
{
    setlocale(LC_ALL, "rus");
    cout << "Программа нумерует вершины графа латинскими буквами" << endl;
    cout << "Из файла считывается количество вершин, матрица смежности графа и номер начальной вершины" << endl;
    cout << "Введите имя файла" << endl;
    char file[maxLen] = {};
    cin >> file;
    ifstream fin(file);
    int numberOfVertex = 0;
    fin >> numberOfVertex;
    int **matrix = new int*[numberOfVertex];
    char *names = new char[numberOfVertex];
    for (int i = 0; i < numberOfVertex; i++)
    {
        matrix[i] = new int[numberOfVertex];
        names[i] = '\0';
        for (int j = 0; j < numberOfVertex; j++)
        {
            fin >> matrix[i][j];
        }
    }
    int startVertex = 0;
    fin >> startVertex;
    char startName = 'a';
    dfs(startVertex - 1, numberOfVertex, matrix, names, startName);
    for (int i = 0; i < numberOfVertex; i++)
    {
        cout << names[i] << " ";
        delete[] matrix[i];
    }
    cout << endl;
    delete[] matrix;
    delete[] names;
    return 0;
}

