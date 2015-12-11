#include <iostream>
#include "myString.h"

using namespace std;

int main()
{
    setlocale(LC_ALL, "rus");
    String *str1 = getNewString("hello, ");
    cout << "������ 1: \"" << *str1 << "\"" << endl;
    cout << "����� ������ \"" << *str1 << "\" = " << length(str1) << endl;
    String *strClone = clone(str1);
    cout << "������������� ������: \"" << *strClone << "\"" << endl;
    cout << "�������� ������ ";
    if (*str1 != *strClone)
        cout << "�� ";
    cout << "����� �������������" << endl;
    String *str2 = getNewString("world!");
    cout << "������ 2: \"" << *str2 << "\"" << endl;
    cout << "������ 1 ";
    if (*str1 < *str2)
        cout << "������";
    else
        cout << "������";
    cout << " ������ 2" << endl;
    cout << "������ 2 ";
    if (*str2 < *str1)
        cout << "������";
    else
        cout << "������";
    cout << " ������ 1" << endl;
    concat(str1, str2);
    cout << "������������ ������ ���� �����: \"" << *str1 << "\"" << endl;
    int substrLength = 9;
    int startIndex = 0;
    String *str3 = substring(str1, startIndex, substrLength);
    cout << "��������� � " << startIndex << " ������� ����� " << length(str3) << ": \"" << *str3 << "\"" << endl;
    cout << "��������������� ������ 1 � char *: \"" << stringToChar(str1) << "\"" << endl;
    String *str4 = getNewString("");
    cout << "������ 4: \"" << *str4 << "\"" << endl;
    cout << "������ 4 ";
    if (!isEmpty(str4))
        cout << "��";
    cout << "������" << endl;
    delete str1;
    delete str2;
    delete str3;
    delete str4;
    delete strClone;
    return 0;
}

