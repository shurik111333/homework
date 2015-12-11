#include <iostream>
#include <fstream>
#include <cstring>
#include "tree.h"

using namespace std;

const int maxLen = 256;

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
    cout << "Программа декодирует строку, закодированную алгоритмом хаффмана" << endl;
    cout << "Введите имя файла с деревом разбора и закодированной строкой" << endl;
    FILE *input = getFileToRead();
    Tree *tree = getTree(input);
    getc(input);
    cout << "Введите имя файла для вывода строки" << endl;
    char output[maxLen] = {};
    cin >> output;
    ofstream fout(output);
    decode(tree, input, fout);
    fclose(input);
    deleteTree(tree);
    return 0;
}

