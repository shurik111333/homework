// 2.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include <iostream>
#include <cstring>
#include <cstdio>
#include "infixToPostfix.h"

using namespace std;

const int maxLen = 255;

int main()
{
	setlocale(LC_ALL, "rus");
	cout << "��������� ������������ ��������� �� ��������� ����� � �����������" << endl;
	cout << "������� ��������� � ��������� �����" << endl;
	char *inputString = new char[maxLen];
	memset(inputString, '\0', maxLen * sizeof(char));
	fgets(inputString, maxLen, stdin);
	int currentLength = 0;
	while (inputString[currentLength] != '\0')
	{
		currentLength++;
	}
	char *resultString = infixToPostfix(inputString, currentLength);
	cout << "�����: " << resultString << endl;
	delete[] inputString;
	delete[] resultString;
	return 0;
}

