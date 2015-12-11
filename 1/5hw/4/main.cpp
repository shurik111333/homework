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
    cout << "Введите имя контакта" << endl;
    char *newName = getLine();
    cout << "Введите номер телефона" << endl;
    char *newPhone = getLine();
    addPhoneNumber(book, newName, newPhone);
}

void doFindPhone(Phonebook *book)
{
    cout << "Введите имя для поиска" << endl;
    char *name = getLine();
    char *phone = new char[maxLen];
    if (getPhone(book, name, phone))
    {
        cout << phone;
    }
    else
    {
        cout << "Запись с таким именем не найдена";
    }
    cout << endl;
    delete[] name;
    delete[] phone;
}

void doFindName(Phonebook *book)
{
    cout << "Введите телефон для поиска" << endl;
    char *phone = getLine();
    char *name = new char[maxLen];
    if (getName(book, name, phone))
    {
        cout << name;
    }
    else
    {
        cout << "Запись с таким телефоном не найдена";
    }
    delete[] name;
    delete[] phone;
    cout << endl;
}

int getCommand()
{
    cout << "Введите команду" << endl;
    int command = 0;
    cin >> command;
    return command;
}

int main()
{
    setlocale(LC_ALL, "rus");
    cout << "Программа телефонный справочник" << endl;
    Phonebook *book = getPhonebook();
    cout << "Команды:" << endl;
    cout << "0 - выход" << endl;
    cout << "1 - добавить запись в справочник" << endl;
    cout << "2 - найти телефон по имени" << endl;
    cout << "3 - найти имя по телефону" << endl;
    cout << "4 - сохранить справочник в файл" << endl;
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
                    cout << "Все данные успешно сохранены в файл" << endl;
                }
                else
                {
                    cout << "Не удалось сохранить данные в файл" << endl;
                }
                break;
            }
        }
    }
    deletePhonebook(book);
    return 0;
}

