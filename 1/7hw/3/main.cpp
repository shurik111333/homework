#include <iostream>
#include "hashmap.h"
#include "myString.h"
#include <cstring>
#include <cctype>

using namespace std;

const int maxLen = 256;
const int startSize = 100;

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
    cout << "������� ��� �����" << endl;
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

String *getNextWord(FILE *file)
{
    char currentChar = 0;
    while (!feof(file) && !isalpha(currentChar))
    {
        currentChar = getc(file);
    }
    if (feof(file))
        return nullptr;
    char newWord[maxLen] = {};
    int length = 0;
    while (isalpha(currentChar) && !feof(file))
    {
        newWord[length] = currentChar;
        length++;
        currentChar = getc(file);
    }
    newWord[length] = '\0';
    return new String(newWord, length);
}

int main()
{
    setlocale(LC_ALL, "rus");
    cout << "��������� ���������� ��� ����� �� ����� � ��� ������� � ������� �� ���������" << endl;
    FILE *fileToRead = getFileToRead();
    String *nextWord = getNextWord(fileToRead);
    Hashmap *map = getNewHashmap(startSize);
    while (nextWord)
    {
        if (!addToMap(map, nextWord))
            delete nextWord;
        nextWord = getNextWord(fileToRead);
    }
    fclose(fileToRead);
    cout << "Load factor: " << getLoadFactor(map) << endl;
    cout << "������� ����� �������: " << getAverageLengthOfChain(map) << endl;
    int count = 0;
    char *maxChain = getMaxChain(map, count);
    cout << "������������ ����� �������: " << count << endl;
    cout << "�������� �� ������������ �������:" << endl << maxChain;
    delete maxChain;
    cout << "����� ����� ����: " << getTotalNumberOfWords(map) << endl;
    cout << "���������� ������ �����: " << getNumberOfEmpty(map) << endl;
    removeMap(map);
    return 0;
}

