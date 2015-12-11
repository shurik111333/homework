#include <iostream>
#include "myString.h"

using namespace std;

int main()
{
    setlocale(LC_ALL, "rus");
    String *str1 = getNewString("hello, ");
    cout << "Строка 1: \"" << *str1 << "\"" << endl;
    cout << "Длина строки \"" << *str1 << "\" = " << length(str1) << endl;
    String *strClone = clone(str1);
    cout << "Клонированная строка: \"" << *strClone << "\"" << endl;
    cout << "Исходная строка ";
    if (*str1 != *strClone)
        cout << "не ";
    cout << "равна клонированной" << endl;
    String *str2 = getNewString("world!");
    cout << "Строка 2: \"" << *str2 << "\"" << endl;
    cout << "Строка 1 ";
    if (*str1 < *str2)
        cout << "меньше";
    else
        cout << "больше";
    cout << " строки 2" << endl;
    cout << "Строка 2 ";
    if (*str2 < *str1)
        cout << "меньше";
    else
        cout << "больше";
    cout << " строки 1" << endl;
    concat(str1, str2);
    cout << "Конкатенация первых двух строк: \"" << *str1 << "\"" << endl;
    int substrLength = 9;
    int startIndex = 0;
    String *str3 = substring(str1, startIndex, substrLength);
    cout << "Подстрока с " << startIndex << " индекса длины " << length(str3) << ": \"" << *str3 << "\"" << endl;
    cout << "Конвертирование строки 1 в char *: \"" << stringToChar(str1) << "\"" << endl;
    String *str4 = getNewString("");
    cout << "Строка 4: \"" << *str4 << "\"" << endl;
    cout << "Строка 4 ";
    if (!isEmpty(str4))
        cout << "не";
    cout << "пустая" << endl;
    delete str1;
    delete str2;
    delete str3;
    delete str4;
    delete strClone;
    return 0;
}

