// 4.cpp: определяет точку входа для консольного приложения.
//

#include <iostream>
#include <stdio.h>
#include <cstring>
#include <cstdio>
#include "infixToPostfix.h"
#include "calculatePostfix.h"

using namespace std;

const int maxLen = 255;

int main()
{
	setlocale(LC_ALL, "rus");
	printf("Программа считает значение выражения\n");
	printf("Введите выражение\n");
	char *inputString = new char[maxLen];
	memset(inputString, '\0', maxLen * sizeof(char));
	fgets(inputString, maxLen, stdin);
	printf("%g\n", calculatePostfix(infixToPostfix(inputString, strlen(inputString))));
	delete[] inputString;
	return 0;
}

