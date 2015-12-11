#include <iostream>
#include <cstring>
#include "bst.h"

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
    cout << "��������� ��������������� ��������� �� ����� � ������ � ������� ���" << endl;
    cout << "������� ��� �����" << endl;
    FILE *fileToRead = getFileToRead();
    BST *tree = getNewBST(fileToRead);
    fclose(fileToRead);
    writeTree(tree);
    cout << "���������: " << calculateTree(tree) << endl;
    removeTree(tree);
    return 0;
}

