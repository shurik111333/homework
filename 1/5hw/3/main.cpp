#include <iostream>
#include <cstring>

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

void skipMultilineComment(FILE *fileToRead, char *currentLine, int &currentIndex, int &currentLength)
{
    while (true)
    {
        currentLength = strlen(currentLine);
        while (currentIndex < currentLength - 1 &&
               (currentLine[currentIndex] != '*' || currentLine[currentIndex + 1] != '/'))
        {
            currentIndex++;
        }
        if (currentIndex >= currentLength - 1)
        {
            fgets(currentLine, maxLen - 1, fileToRead);
            currentIndex = 0;
            continue;
        }
        else
        {
            currentIndex += 2;
            return;
        }
    }
}

void skipString(char *string, int &currentIndex)
{
    int length = strlen(string);
    while (currentIndex < length && string[currentIndex] != '"')
    {
        currentIndex++;
    }
    currentIndex++;
}

void writeComment(char *string, int &currentIndex)
{
    int length = strlen(string);
    while (currentIndex < length)
    {
        cout << string[currentIndex++];
    }
}

int main()
{
    setlocale(LC_ALL, "rus");
    cout << "Программа выводит все однострочные комментарии из файла" << endl;
    cout << "Введите имя файла" << endl;
    FILE *fileToRead = getFileToRead();
    char currentLine[maxLen] = {};
    while (fgets(currentLine, maxLen - 1, fileToRead) != nullptr)
    {
        int currentLength = strlen(currentLine);
        int currentIndex = 0;
        while (currentIndex < currentLength - 1)
        {
            if (currentLine[currentIndex] == '/' && currentLine[currentIndex + 1] == '*')
            {
                currentIndex += 2;
                skipMultilineComment(fileToRead, currentLine, currentIndex, currentLength);
                continue;
            }
            if (currentLine[currentIndex] == '"')
            {
                skipString(currentLine, ++currentIndex);
                continue;
            }
            if (currentLine[currentIndex] == '/' && currentLine[currentIndex + 1] == '/')
            {
                writeComment(currentLine, currentIndex);
            }
            currentIndex++;
        }
    }
    fclose(fileToRead);
    cout << endl;
    return 0;
}

