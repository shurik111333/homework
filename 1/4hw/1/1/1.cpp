// 1.cpp: определяет точку входа для консольного приложения.
//

#include <iostream>
#include <stdio.h>
#include <cstring>
#include <limits.h>

using namespace std;

const int maxLen = 255;

int *countSymbols(char *string)
{
	int stringLenght = strlen(string);
	int *counting = new int[CHAR_MAX - CHAR_MIN + 1];
	memset(counting, 0, (CHAR_MAX - CHAR_MIN + 1) * sizeof(counting[0]));
	for (int i = 0; i < stringLenght; i++)
	{
		counting[string[i] - CHAR_MIN]++;
	}
	return counting;
}

int main()
{
	setlocale(LC_ALL, "rus");
	printf("Программа определяет, можно ли из одной строки получить другую, переставляя символы\n");
	printf("Введите первую строку\n");
	char inputString[maxLen] = {};
	scanf("%s", inputString);
	int *countSymbolsInString1 = countSymbols(inputString);
	printf("Введите вторую строку\n");
	scanf("%s", inputString);
	int *countSymbolsInString2 = countSymbols(inputString);
	bool isEqual = true;
	for (int i = CHAR_MIN; i <= CHAR_MAX; i++)
	{
		if (countSymbolsInString1[i - CHAR_MIN] != countSymbolsInString2[i - CHAR_MIN])
		{
			isEqual = false;
			break;
		}
	}
	delete[] countSymbolsInString1;
	delete[] countSymbolsInString2;
	printf("Ответ: ");
	if (isEqual)
	{
		printf("можно");
	}
	else
	{
		printf("нельзя");
	}
	printf("\n");
	return 0;
}