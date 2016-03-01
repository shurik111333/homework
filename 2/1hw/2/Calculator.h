#pragma once

#include <string>
#include "IStack.h"

using namespace std;

class Calculator
{
public:
	class Operator
	{
	public:
		IStack<double> *data;
		
		virtual int getPriority() const = 0;
		virtual void interpret() = 0;
		
		virtual ~Operator()
		{}
	};
	
	static double calculate(string expression, IStack<double> &result, IStack<Operator*> &operators);
	
private:
	class Add : public Operator
	{
	public:
		Add(IStack<double> *data);
		
		int getPriority() const;
		void interpret();
	};
	
	class Subtract : public Operator
	{
	public:
		Subtract(IStack<double> *data);
		
		int getPriority() const;
		void interpret();
	};
	
	class Multiply : public Operator
	{
	public:
		Multiply(IStack<double> *data);
		
		int getPriority() const;
		void interpret();
	};
	
	class Division : public Operator
	{
	public:
		Division(IStack<double> *data);
		
		int getPriority() const;
		void interpret();
	};
	
	class Bracket : public Operator
	{
	public:
		int getPriority() const;
		void interpret();
	};
	
	class Lexer
	{
	public:
		enum Token
		{
			number,
			add = '+',
			subtract = '-',
			multiply = '*',
			division = '/',
			openBracket = '(',
			closeBracket = ')',
			end = -1
		};
		
		Lexer(string expression);
		Token getNextToken(int &value);
		
	private:
		string expression;
		int position;
		
		void skipSpaces();
		int getNumber();
	};
	
	static Operator *getOperator(Lexer::Token token, IStack<double> &data);
};
