#include <iostream>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <limits.h>

using namespace std;

const int maxLen = 256;

void deleteNewLineSymbol(char *string)
{
    if (string[strlen(string) - 1] == '\n')
    {
        string[strlen(string) - 1] = '\0';
    }
}

char *getLine()
{
    char *newString = new char[maxLen];
    newString[0] = '\n';
    while (newString[0] == '\n')
    {
        fgets(newString, maxLen - 1, stdin);
    }
    deleteNewLineSymbol(newString);
    return newString;
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
    cout << "Программа выводит из файла все слова, оставив только первое вхождение каждой буквы в слове" << endl;
    cout << "Введите имя файла" << endl;
    FILE *fileToRead = getFileToRead();
    char *currentLine = new char[maxLen];
    bool isUsed[CHAR_MAX - CHAR_MIN + 1];
    bool isInWord = false;
    while (fgets(currentLine, maxLen - 1, fileToRead) != nullptr)
    {
        isInWord = false;
        int currentLength = strlen(currentLine);
        for (int i = 0; i < currentLength; i++)
        {
            if (isalpha(currentLine[i]))
            {
                if (!isInWord)
                {
                    isInWord = true;
                    memset(isUsed, false, CHAR_MAX - CHAR_MIN + 1);
                }
                if (!isUsed[currentLine[i] - CHAR_MIN])
                {
                    cout << currentLine[i];
                    isUsed[currentLine[i] - CHAR_MIN] = true;
                }
            }
            else
            {
                cout << currentLine[i];
                if (isInWord)
                {
                    isInWord = false;
                }
            }
        }
    }
    fclose(fileToRead);
    if (isInWord)
    {
        cout << endl;
    }
    delete[] currentLine;
    return 0;
}

