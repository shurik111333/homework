// 5.cpp: определяет точку входа для консольного приложения.
//

#include <iostream>
#include <string.h>

using namespace std;

int main()
{
	setlocale(LC_ALL, "rus");
	cout << "Программа проверяет корректность скобочной последовательности в строке" << endl;
	cout << "Введите строку" << endl;
	char *inputString = new char[];
	scanf("%s", inputString);
	int balance = 0;
	for (int i = 0; i < strlen(inputString); i++)
	{
		if (inputString[i] == '(')
		{
			balance++;
		}
		if (inputString[i] == ')')
		{
			balance--;
		}
		if (balance < 0)
		{
			break;
		}
	}
	cout << "Скобочная последовательность является ";
	if (balance != 0)
	{
		cout << "не";
	}
	cout << "корректной" << endl;
	return 0;
}