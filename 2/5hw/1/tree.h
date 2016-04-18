#pragma once

#include <cstdio>
#include <string>

using namespace std;

class Tree
{
public:
	Tree();
	Tree(const string &input);

	int calc() const;
	string toStdString() const;

private:
	class Node
	{
	public:
		Node *left = nullptr;
		Node *right = nullptr;

		virtual int calc() const = 0;
		virtual string toStdString() const = 0;
	};

	class Number : public Node
	{
	private:
		int value;

	public:
		Number(int value);

		int calc() const;
		string toStdString() const;
	};

	class Operation : public Node
	{
	private:
		char sign;

	public:
		Operation(char sign);

		int calc() const;
		string toStdString() const;
	};

	static void skipSpaces(const string &s, int &i);
	static int getNumber(const string &s, int &i);
	static Node *getNode(const string &input, int &i);
	Node *root;
};
