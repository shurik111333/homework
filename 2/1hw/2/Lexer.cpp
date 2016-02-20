#include <cctype>
#include <Calculator.h>

Calculator::Lexer::Lexer(string expression)
    :expression(expression), position(0)
{}

Calculator::Lexer::Token Calculator::Lexer::getNextToken(int &value)
{
	skipSpaces();
	if (position >= expression.length())
		return end;
	if (isdigit(expression[position]))
	{
		value = getNumber();

		return number;
	}
	return (Token)expression[position++];
}

void Calculator::Lexer::skipSpaces()
{
	while (expression[position] == ' ')
		position++;
}

int Calculator::Lexer::getNumber()
{
	int res = expression[position++] - '0';
	while (position < expression.length() && isdigit(expression[position]))
	{
		res = res * 10 + expression[position] - '0';
		position++;
	}
	return res;
}