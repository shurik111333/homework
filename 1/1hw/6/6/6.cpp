// 6.cpp: определяет точку входа для консольного приложения.
//

#include <iostream>
#include <string.h>

using namespace std;

const int maxLen = 255;

char *readString()
{
	char inputString[maxLen] = {};
	scanf("%s", inputString);
	if (inputString[strlen(inputString) - 1] == '\n')
	{
		inputString[strlen(inputString) - 1] = '\0';
	}
	return inputString;
}

int main()
{
	setlocale(LC_ALL, "rus");
	cout << "Программа находит количество вхождений второй строки в первую" << endl;
	cout << "Введите первую строку" << endl;
	char *inputString1 = readString();
	cout << "Введите вторую строку" << endl;
	char *inputString2 = readString();
	int count = 0;
	int inputString1Length = strlen(inputString1);
	int inputString2Length = strlen(inputString2);
	for (int i = 0; i < inputString1Length - inputString2Length + 1; i++)
	{
		int inputString1Index = i;
		int inputString2Index = 0;
		while (inputString2Index < inputString2Length && inputString1[inputString1Index] == inputString2[inputString2Index])
		{
			inputString1Index++;
			inputString2Index++;
		}
		if (inputString2Index == inputString2Length)
		{
			count++;
		}
	}
	cout << "Число вхождений: " << count << endl;
	delete[] inputString1;
	delete[] inputString2;
	return 0;
}