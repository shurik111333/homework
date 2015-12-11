#include "stack.h"
#include <cstring>
#include <cctype>

int getPriority(char operation)
{
	switch (operation)
	{
		case '+':
		case '-':
		{
			return 1;
		}
		case '*':
		case '/':
		{
			return 2;
		}
		default:
		{
			return 0;
		}
	}

}

void addSymbol(char *string, int &length, char symbol)
{
	string[length] = symbol;
	length++;
}

bool isOperation(char symbol)
{
	return (getPriority(symbol) > 0);
}

char *infixToPostfix(char *infixNotation, int inputLength)
{
	Stack *operators = getNewStack();
	char *postfixNotation = new char[inputLength + 1];
	memset(postfixNotation, '\0', inputLength * sizeof(infixNotation[0]));
	int postfixLength = 0;
	for (int i = 0; i < inputLength; i++)
	{
		if (isdigit(infixNotation[i]))
		{
			addSymbol(postfixNotation, postfixLength, infixNotation[i]);
			continue;
		}
		if (isOperation(infixNotation[i]))
		{
			while (!isEmpty(operators) && getPriority((char)getTop(operators)) > getPriority((char)infixNotation[i]))
			{
				addSymbol(postfixNotation, postfixLength, (char)pop(operators));
			}
			push(operators, infixNotation[i]);
		}
		else
		{
			if (infixNotation[i] == '(')
			{
				push(operators, infixNotation[i]);
				continue;
			}
			if (infixNotation[i] == ')')
			{
				while (getTop(operators) != '(')
				{
					addSymbol(postfixNotation, postfixLength, (char)pop(operators));
				}
				pop(operators);
			}
		}
	}
	while (!isEmpty(operators))
	{
		addSymbol(postfixNotation, postfixLength, (char)pop(operators));
	}
	addSymbol(postfixNotation, postfixLength, '\0');
	deleteStack(operators);
	return postfixNotation;
}