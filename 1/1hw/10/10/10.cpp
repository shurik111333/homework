// 10.cpp: определяет точку входа для консольного приложения.
//

#include <string.h>
#include <stdio.h>
#include <iostream>

using namespace std;

bool isPalindrome(char string[])
{
	int strLength = strlen(string);
	int i = 0;
	for (i = 0; i <= strLength / 2; i++)
	{
		if (string[i] != string[strLength - i - 1])
		{
			break;
		}
	}
	return (i > strLength / 2);
}

int main()
{
	setlocale(LC_ALL, "rus");
	cout << "Программа  проверяет, является ли строка палиндромом\n";
	cout << "Введите строку\n";
	char *inputString = new char[];
	scanf("%s", inputString);
	if (inputString[strlen(inputString) - 1] == '\n')
	{
		inputString[strlen(inputString) - 1] = '\0';
	}
	cout << "Строка ";
	if (!isPalindrome(inputString))
	{
		cout << "не ";
	}
	cout << "является палиндромом\n";
	return 0;
}