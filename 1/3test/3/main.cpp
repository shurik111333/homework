#include <iostream>
#include <cstring>
#include <cctype>
#include <cstdio>

using namespace std;

const int maxLen = 256;

enum State
{
	startState,
	nameState
};

bool isLetter(char c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

bool isCorrect(char string[])
{
	State state = startState;
	int len = strlen(string);
	for (int i = 0; i < len; i++)
	{
		switch (state)
		{
			case startState:
			{
				if (isLetter(string[i]))
					state = nameState;
				else
					return false;
				break;
			}
			case nameState:
			{
				if (isLetter(string[i]) || isdigit(string[i]) || string[i] == '_')
					break;
				return false;
			}
		}
	}
	return true;
}

void deleteNewLineSymbol(char *string)
{
	int len = strlen(string);
	if (string[len - 1] == '\n')
	{
		string[len - 1] = '\0';
	}
}

int main()
{
	setlocale(LC_ALL, "rus");
	cout << "Введите строку" << endl;
	char input[maxLen] = {};
	fgets(input, maxLen - 1, stdin);
	deleteNewLineSymbol(input);
	cout << "Строка ";
	if (!isCorrect(input))
		cout << "не ";
	cout << "корректна" << endl;
	return 0;
}
