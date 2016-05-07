#pragma once

#include <cstdio>
#include <string>

using namespace std;

/**
 * @brief The Tree class Represents tree of arithmetic expression
 */
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

		/**
		 * @brief calc Recursively calculate expression in tree.
		 * Throw std::overflow_exception for division by zero
		 * @return result of exression, that represented by current node.
		 */
		virtual int calc() const = 0;
		/**
		 * @brief toStdString Recursively convert tree with root in current node to infix notation
		 * @return string of infix notation
		 */
		virtual string toStdString() const = 0;
	};

	/**
	 * @brief The Number class Represents number node. Always leaf.
	 */
	class Number : public Node
	{
	private:
		int value;

	public:
		Number(int value);

		int calc() const;
		string toStdString() const;
	};

	/**
	 * @brief The Operation class Represents operation node. Always have child.
	 */
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
	/**
	 * @brief getNode Recursively parsing string to tree
	 * @param s string to parse
	 * @param i current index in s
	 * @return Root of tree
	 */
	static Node *getNode(const string &s, int &i);
	Node *root;
};
