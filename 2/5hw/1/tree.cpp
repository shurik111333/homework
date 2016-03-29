#include <cctype>
#include "tree.h"

using namespace std;

Tree::Tree()
    :root(nullptr)
{}

Tree::Tree(FILE *file)
{
	root = getNodeFromFile(file);
}

int Tree::calc() const
{
	return root->calc();
}

void Tree::print(ostream &out) const
{
	root->print(out);
}

bool isSpace(char symbol)
{
	return (symbol == ' ' || symbol == '\t' || symbol == '\n');
}

void skipSpaces(FILE *file)
{
	char c = getc(file);
	while (!feof(file) && isSpace(c))
	{
		c = getc(file);
	}
	ungetc(c, file);
}

int getNumber(FILE *file)
{
	int result = 0;
	char c = getc(file);
	while (isdigit(c))
	{
		result = result * 10 + c - '0';
		c = getc(file);
	}
	ungetc(c, file);
	return result;
}

Node *getNode(char c, Node *left, Node *right)
{
	switch (c)
	{
		case '+':
			return new NodePlus(left, right);
		case '-':
			return new NodeMinus(left, right);
		case '*':
			return new NodeMultiply(left, right);
		case '/':
			return new NodeDivide(left, right);
		default:
			return nullptr;
	}
}

Node *getNodeFromFile(FILE *file)
{
	skipSpaces(file);
	Node *newNode = nullptr;
	char c = getc(file);
	if (c == '(')
	{
		skipSpaces(file);
		char sign = getc(file);
		skipSpaces(file);
		Node *left = getNodeFromFile(file);
		skipSpaces(file);
		Node *right = getNodeFromFile(file);
		newNode = getNode(sign, left, right);
		skipSpaces(file);
		getc(file);
	}
	else
	{
		ungetc(c, file);
		skipSpaces(file);
		newNode = new NodeNumber(getNumber(file));
	}
	return newNode;
}

// Nodes ------------------------------------------------

Node *getNodeFromFile(FILE *file);

Node::Node()
    :left(nullptr), right(nullptr)
{}

Node::Node(Node *left, Node *right):
    left(left),
    right(right)
{}


NodeNumber::NodeNumber(int value):
    value(value)
{}

int NodeNumber::calc() const
{
	return value;
}

void NodeNumber::print(ostream &out) const
{
	out << value;
}

NodePlus::NodePlus(Node *left, Node *right):
    Node(left, right)
{}

int NodePlus::calc() const
{
	return left->calc() + right->calc();
}

void NodePlus::print(std::ostream &out) const
{
	out << "(";
	left->print(out);
	out << " + ";
	right->print(out);
	out << ")";
}

NodeMinus::NodeMinus(Node *left, Node *right):
    Node(left, right)
{}

int NodeMinus::calc() const
{
	return left->calc() - right->calc();
}

void NodeMinus::print(std::ostream &out) const
{
	out << "(";
	left->print(out);
	out << " - ";
	right->print(out);
	out << ")";
}

NodeMultiply::NodeMultiply(Node *left, Node *right):
    Node(left, right)
{}

int NodeMultiply::calc() const
{
	return left->calc() * right->calc();
}

void NodeMultiply::print(std::ostream &out) const
{
	out << "(";
	left->print(out);
	out << " * ";
	right->print(out);
	out << ")";
}

NodeDivide::NodeDivide(Node *left, Node *right):
    Node(left, right)
{}

int NodeDivide::calc() const
{
	return left->calc() / right->calc();
}

void NodeDivide::print(std::ostream &out) const
{
	out << "(";
	left->print(out);
	out << " / ";
	right->print(out);
	out << ")";
}
