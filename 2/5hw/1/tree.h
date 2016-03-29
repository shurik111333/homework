#pragma once

#include <cstdio>
#include <ostream>

class Node
{
private:
	Node *left;
	Node *right;

public:
	Node();
	Node(Node *left, Node *right);

	virtual int calc() const = 0;
	virtual void print(std::ostream &out) const = 0;
};

class Tree
{
public:
	Tree();
	Tree(FILE *file);

	int calc() const;
	void print(std::ostream &out) const;

private:
	Node *root;
};

class NodeNumber : public Node
{
private:
	int value;

public:
	NodeNumber(int value);

	int calc() const;
	void print(std::ostream &out) const;
};

class NodePlus : public Node
{
public:
	NodePlus(Node *left, Node *right);

	int calc() const;
	void print(std::ostream &out) const;
};

class NodeMinus : public Node
{
public:
	NodeMinus(Node *left, Node *right);

	int calc() const;
	void print(std::ostream &out) const;
};

class NodeMultiply : public Node
{
public:
	NodeMultiply(Node *left, Node *right);

	int calc() const;
	void print(std::ostream &out) const;
};

class NodeDivide : public Node
{
public:
	NodeDivide(Node *left, Node *right);

	int calc() const;
	void print(std::ostream &out) const;
};
