#include <iostream>
#include <fstream>
#include <cstring>
#include "myString.h"
#include "hashmap.h"

using namespace std;

const int maxLen = 500;

void deleteNewLineSymbol(char *string)
{
    if (string[strlen(string) - 1] == '\n')
    {
        string[strlen(string) - 1] = '\0';
    }
}

void addStringsToMap(Hashmap *map, FILE *file)
{
    char tmp[maxLen] = {};
    while (!feof(file))
    {
        fgets(tmp, maxLen - 1, file);
        deleteNewLineSymbol(tmp);
        String *line = getNewString(tmp);
        if (!addToMap(map, line))
            delete line;
    }
}

int main()
{
    setlocale(LC_ALL, "rus");
    cout << "��������� ���������� � ���� ������, ������� ����������� � ������ � �� ������ ������" << endl;
    cout << "������� ��� ������� �����" << endl;
    char fileName[maxLen] = {};
    cin >> fileName;
    FILE *file = fopen(fileName, "r");
    Hashmap *map = getNewHashmap();
    addStringsToMap(map, file);
    fclose(file);
    cout << "������� ��� ������� �����" << endl;
    cin >> fileName;
    file = fopen(fileName, "r");
    cout << "������� ��� ��������� �����" << endl;
    cin >> fileName;
    ofstream fout(fileName);
    char tmp[maxLen] = {};
    while (!feof(file))
    {
        fgets(tmp, maxLen - 1, file);
        deleteNewLineSymbol(tmp);
        String *line = getNewString(tmp, strlen(tmp));
        if (findInMap(map, line))
            fout << tmp << "\n";
    }
    fclose(file);
    fout.close();
    removeMap(map);
    return 0;
}

