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
        cout << "�� ������� ������� ����. ���������� �����" << endl;
        fgets(fileName, maxLen - 1, stdin);
        deleteNewLineSymbol(fileName);
        fileToRead = fopen(fileName, "r");
    }
    return fileToRead;
}

int main()
{
    setlocale(LC_ALL, "rus");
    cout << "��������� ���������� ������, �������������� ���������� ��������" << endl;
    cout << "������� ��� ����� � ������� ������� � �������������� �������" << endl;
    FILE *input = getFileToRead();
    Tree *tree = getTree(input);
    getc(input);
    cout << "������� ��� ����� ��� ������ ������" << endl;
    char output[maxLen] = {};
    cin >> output;
    ofstream fout(output);
    decode(tree, input, fout);
    fclose(input);
    deleteTree(tree);
    return 0;
}

