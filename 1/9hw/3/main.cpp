#include <iostream>
#include <cstring>

using namespace std;

struct Edge
{
    int a;
    int b;
    int weight;

    Edge()
    {
        a = 0;
        b = 0;
        weight = 0;
    }

    Edge(int a, int b, int weight)
    {
        this->a = a;
        this->b = b;
        this->weight = weight;
    }
};

Edge *prim(int n, int m, Edge *edges)
{
    Edge *minTree = new Edge[n - 1];
    bool *isUsed = new bool[n];
    memset(isUsed, false, n);
    isUsed[0] = true;
    for (int i = 0; i < n - 1; i++)
    {
        int minEdgeIndex = -1;
        for (int j = 0; j < m; j++)
        {
            if (isUsed[edges[j].a] ^ isUsed[edges[j].b] && (minEdgeIndex == -1 || edges[j].weight < edges[minEdgeIndex].weight))
            {
                minEdgeIndex = j;
            }
        }
        if (minEdgeIndex == -1)
        {
            delete[] minTree;
            minTree = nullptr;
            break;
        }
        minTree[i] = edges[minEdgeIndex];
        isUsed[minTree[i].a] = isUsed[minTree[i].b] = true;
    }
    delete[] isUsed;
    return minTree;
}

int main()
{
    setlocale(LC_ALL, "rus");
    cout << "Введите количество вершин и ребер в графе" << endl;
    int n = 0, m = 0;
    cin >> n >> m;
    cout << "Введите список ребер" << endl;
    Edge *edges = new Edge[m];
    for (int i = 0; i < m; i++)
    {
        int a = 0, b = 0, c = 0;
        cin >> a >> b >> c;
        edges[i] = Edge(a - 1, b - 1, c);
    }
    Edge *minTree = prim(n, m, edges);
    delete[] edges;
    if (minTree == nullptr)
    {
        cout << "Не удалось построить остовное дерево" << endl;
        return 0;
    }
    cout << "Ребра, входящие в минимальное остовное дерево:" << endl;
    for (int i = 0; i < n - 1; i++)
    {
        cout << minTree[i].a + 1 << " " << minTree[i].b + 1 << endl;
    }
    delete[] minTree;
    return 0;
}

