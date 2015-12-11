#include <iostream>
#include <limits.h>
#include <fstream>
#include <cstring>
#include <cstdio>
#include "priorityqueue.h"
#include "tree.h"

using namespace std;

const int maxLen = 256;
const int charLen = CHAR_MAX - CHAR_MIN + 1;

void deleteNewLineSymbol(char *string)
{
    if (string[strlen(string) - 1] == '\n')
    {
        string[strlen(string) - 1] = '\0';
    }
}

FILE *getFileToRead()
{
    char fileName[maxLen] = {};
    cout << "Введите имя файла" << endl;
    fgets(fileName, maxLen - 1, stdin);
    deleteNewLineSymbol(fileName);
    FILE *fileToRead = fopen(fileName, "r");
    while (fileToRead == nullptr)
    {
        cout << "Не удалось открыть файл. Попробуйте снова" << endl;
        fgets(fileName, maxLen - 1, stdin);
        deleteNewLineSymbol(fileName);
        fileToRead = fopen(fileName, "r");
    }
    return fileToRead;
}

int main()
{
    setlocale(LC_ALL, "rus");
    cout << "Программа кодирует текст из файла алгоритмом Хаффмана" << endl;
    FILE *input = getFileToRead();
    int countChar[charLen] = {};
    char c = getc(input);
    while (!feof(input))
    {
        countChar[c - CHAR_MIN]++;
        c = getc(input);
    }
    PriorityQueue *queue = getNewQueue();
    for (int i = 0; i < charLen; i++)
    {
        if (countChar[i] > 0)
        {
            push(queue, getNewTree(i + CHAR_MIN, countChar[i]));
        }
    }
    while (size(queue) > 1)
    {
        Tree *tree1 = pop(queue);
        Tree *tree2 = pop(queue);
        push(queue, merge(tree1, tree2));
    }
    Tree *tree = pop(queue);
    deleteQueue(queue);
    char **codes = getCodes(tree);
    cout << "Введите имя файла для вывода" << endl;
    char output[maxLen] = {};
    cin >> output;
    ofstream fout(output);
    writeTree(tree, fout);
    deleteTree(tree);
    fout << endl;
    fseek(input, 0, SEEK_SET);
    c = getc(input);
    while (!feof(input))
    {
        fout << codes[c - CHAR_MIN];
        c = getc(input);
    }
    fclose(input);
    fout.close();
    for (int i = 0; i < charLen; i++)
    {
        delete[] codes[i];
    }
    delete[] codes;
    return 0;
}

