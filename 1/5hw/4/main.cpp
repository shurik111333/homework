#include <iostream>
#include <cstring>
#include <ctype.h>
#include "phonebook.h"

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

void doAddNewPhone(Phonebook *book)
{
    cout << "������� ��� ��������" << endl;
    char *newName = getLine();
    cout << "������� ����� ��������" << endl;
    char *newPhone = getLine();
    addPhoneNumber(book, newName, newPhone);
}

void doFindPhone(Phonebook *book)
{
    cout << "������� ��� ��� ������" << endl;
    char *name = getLine();
    char *phone = new char[maxLen];
    if (getPhone(book, name, phone))
    {
        cout << phone;
    }
    else
    {
        cout << "������ � ����� ������ �� �������";
    }
    cout << endl;
    delete[] name;
    delete[] phone;
}

void doFindName(Phonebook *book)
{
    cout << "������� ������� ��� ������" << endl;
    char *phone = getLine();
    char *name = new char[maxLen];
    if (getName(book, name, phone))
    {
        cout << name;
    }
    else
    {
        cout << "������ � ����� ��������� �� �������";
    }
    delete[] name;
    delete[] phone;
    cout << endl;
}

int getCommand()
{
    cout << "������� �������" << endl;
    int command = 0;
    cin >> command;
    return command;
}

int main()
{
    setlocale(LC_ALL, "rus");
    cout << "��������� ���������� ����������" << endl;
    Phonebook *book = getPhonebook();
    cout << "�������:" << endl;
    cout << "0 - �����" << endl;
    cout << "1 - �������� ������ � ����������" << endl;
    cout << "2 - ����� ������� �� �����" << endl;
    cout << "3 - ����� ��� �� ��������" << endl;
    cout << "4 - ��������� ���������� � ����" << endl;
    bool isExit = false;
    while (!isExit)
    {
        int command = getCommand();
        switch (command)
        {
            case 0:
            {
                isExit = true;
                break;
            }
            case 1:
            {
                doAddNewPhone(book);
                break;
            }
            case 2:
            {
                doFindPhone(book);
                break;
            }
            case 3:
            {
                doFindName(book);
                break;
            }
            case 4:
            {
                if (saveBookToFile(book))
                {
                    cout << "��� ������ ������� ��������� � ����" << endl;
                }
                else
                {
                    cout << "�� ������� ��������� ������ � ����" << endl;
                }
                break;
            }
        }
    }
    deletePhonebook(book);
    return 0;
}

