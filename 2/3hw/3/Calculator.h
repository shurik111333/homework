#pragma once

#include <string>
#include <QLineEdit>
#include "MainWindow.h"
#include "IStack.h"

using namespace std;

class Calculator
{
public:
	static double calculate(string expression);
	
private:
	class Operator
	{
	public:
		int getPriority() const;
		bool isLeftAssociative() const;
		virtual void interpret() = 0;
		
		virtual ~Operator()
		{}
	protected:
		IStack<double> *data;
		int priority;
		bool leftAssociative;
	};
	
	class Add : public Operator
	{
	public:
		Add(IStack<double> *data);
		void interpret();
	};
	
	class Subtract : public Operator
	{
	public:
		Subtract(IStack<double> *data);
		void interpret();
	};
	
	class Multiply : public Operator
	{
	public:
		Multiply(IStack<double> *data);
		void interpret();
	};
	
	class Division : public Operator
	{
	public:
		Division(IStack<double> *data);
		void interpret();
	};
	
	class Bracket : public Operator
	{
	public:
		Bracket();
		void interpret();
	};
	
	class Sqrt : public Operator
	{
	public:
		Sqrt(IStack<double> *data);
		void interpret();
	};
	
	class Lexer
	{
	public:
		enum Token
		{
			number,
			sqrt,
			add = '+',
			subtract = '-',
			multiply = '*',
			division = '/',
			openBracket = '(',
			closeBracket = ')',
			end = -1,
			error
		};
		
		Lexer(string expression);
		Token getNextToken(double &value);
		
	private:
		string expression;
		int position;
		
		void skipSpaces();
		double getNumber();
		Token getFunction(string name);
		Token getFunction();
	};
	
	static Operator *getOperator(Lexer::Token token, IStack<double> &data);
};
