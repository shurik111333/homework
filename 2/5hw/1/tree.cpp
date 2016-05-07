#include <cctype>
#include <stdexcept>
#include "tree.h"

using namespace std;

Tree::Tree()
    :root(nullptr)
{}

Tree::Tree(const string &input)
{
	int i = 0;
	root = getNode(input, i);
}

int Tree::calc() const
{
	return root->calc();
}

string Tree::toStdString() const
{
	return root->toStdString();
}

// private ------------------------------------------------

void Tree::skipSpaces(const string &s, int &i)
{
	while (s[i] == ' ')
		i++;
}

int Tree::getNumber(const string &s, int &i)
{
	skipSpaces(s, i);
	int res = 0;
	bool negative = false;
	if (s[i] == '-')
	{
		negative = true;
		i++;
	}
	while (isdigit(s[i]))
	{
		res = res * 10 + s[i] - '0';
		i++;
	}
	return negative ? -res : res;
}

Tree::Node *Tree::getNode(const string &s, int &i)
{
	skipSpaces(s, i);
	Node *res = nullptr;
	if (s[i] == '(')
	{
		skipSpaces(s, ++i);
		res = new Operation(s[i]);
		res->left = getNode(s, ++i);
		res->right = getNode(s, i);
		skipSpaces(s, i);
		i++;
	}
	else
		res = new Number(getNumber(s, i));
	return res;
}

// Nodes ----------------------------------------------

Tree::Number::Number(int value):
    value(value)
{}

int Tree::Number::calc() const
{
	return value;
}

string Tree::Number::toStdString() const
{
	return to_string(value);
}

Tree::Operation::Operation(char sign):
    sign(sign)
{}

int Tree::Operation::calc() const
{
	int num1 = left->calc();
	int num2 = right->calc();
	switch (sign)
	{
		case '+':
			return num1 + num2;
		case '-':
			return num1 - num2;
		case '*':
			return num1 * num2;
		case '/':
			if (num2 == 0)
				throw overflow_error("Divide by zero exception");
			return num1 / num2;
		default:
			return 0;
	}
}

string Tree::Operation::toStdString() const
{
	return "(" + left->toStdString() + " " + string(1, sign) + " " + right->toStdString() + ")";
}
