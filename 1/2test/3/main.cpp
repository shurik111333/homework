#include <iostream>
#include "myQueue.h"
#include <fstream>

using namespace std;

const int maxLen = 256;

void writeQueue(Queue *queue, ofstream &fout)
{
    while (!isEmpty(queue))
    {
        fout << pop(queue) << " ";
    }
    fout << endl;
}

int main()
{
    setlocale(LC_ALL, "rus");
    cout << "¬ведите им€ файла дл€ считывани€" << endl;
    char input[maxLen] = {};
    cin >> input;
    cout << "¬ведите им€ файлы дл€ записи" << endl;
    char output[maxLen] = {};
    cin >> output;
    int a = 0, b = 0;
    cout << "¬ведите границы отрезка [a;b]" << endl;
    cin >> a >> b;
    ifstream fin(input);
    Queue *less = getNewQueue();
    Queue *medium = getNewQueue();
    Queue *large = getNewQueue();
    while (!fin.eof())
    {
        int number = 0;
        fin >> number;
        if (number < a)
        {
            push(less, number);
            continue;
        }
        if (number > b)
        {
            push(large, number);
            continue;
        }
        push(medium, number);
    }
    fin.close();
    ofstream fout(output);
    writeQueue(less, fout);
    removeQueue(less);
    writeQueue(medium, fout);
    removeQueue(medium);
    writeQueue(large, fout);
    removeQueue(large);
    fout.close();
    return 0;
}
