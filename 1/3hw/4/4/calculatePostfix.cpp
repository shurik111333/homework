#include "stack.h"
#include <cctype>

double calculateOperation(double number1, double number2, char operation)
{
	switch (operation)
	{
		case '+':
		{
			return number1 + number2;
		}
		case '-':
		{
			return number1 - number2;
		}
		case '*':
		{
			return number1 * number2;
		}
		case '/':
		{
			return number1 / number2;
		}
		default:
		{
			return -1;
		}
	}
}

double calculatePostfix(char *postfixExpression)
{
	Stack *result = getNewStack();
	int currentIndex = 0;
	while (postfixExpression[currentIndex] != '\0')
	{
		if (isdigit(postfixExpression[currentIndex]))
		{
			push(result, postfixExpression[currentIndex] - '0');
		}
		else
		{
			push(result, calculateOperation(pop(result), pop(result), postfixExpression[currentIndex]));
		}
		currentIndex++;
	}
	double resultValue = pop(result);
	deleteStack(result);
	return resultValue;
}