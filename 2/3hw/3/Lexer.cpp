#include <cctype>
#include <Calculator.h>
#include <QDoubleValidator>

Calculator::Lexer::Lexer(string expression)
    :expression(expression), position(0)
{}

bool isOperation(char c)
{
	return (c == '+' || c == '-' || c == '*' || c == '/');
}

bool isBracket(char c)
{
	return (c == ')' || c == '(');
}

Calculator::Lexer::Token Calculator::Lexer::getNextToken(double &value)
{
	skipSpaces();
	if (position >= expression.length())
		return end;
	if (isdigit(expression[position]))
	{
		value = getNumber();
		return number;
	}
	if (isOperation(expression[position]) || isBracket(expression[position]))
		return (Token)expression[position++];
	else
	{
		position += 4;
		return sqrt;
	}
}

void Calculator::Lexer::skipSpaces()
{
	while (expression[position] == ' ')
		position++;
}

double Calculator::Lexer::getNumber()
{
	double res = 0;
	int start = position;
	while (position < expression.length() && (isdigit(expression[position]) || expression[position] == '.'))
	{
		position++;
	}
	res = stod(expression.substr(start, position - start));
	return res;
}

Calculator::Lexer::Token Calculator::Lexer::getFunction(string name)
{
	if (name == "sqrt")
		return Calculator::Lexer::sqrt;
	return Calculator::Lexer::error;
}

Calculator::Lexer::Token Calculator::Lexer::getFunction()
{
	int start = position;
	while (position < expression.length() && expression[position] != ' ')
		position++;
	return getFunction(expression.substr(start, position - start));
}