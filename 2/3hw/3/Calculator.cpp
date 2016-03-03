#include "Calculator.h"
#include "StackArray.h"
#include <cmath>

double Calculator::calculate(string expression)
{
	StackArray<double> result;
	StackArray<Operator*> operators;
	Lexer expr(expression);
	double value = 0;
	Lexer::Token currentToken = expr.getNextToken(value);
	while (currentToken != Lexer::end)
	{
		switch (currentToken)
		{
			case Lexer::number:
			{
				result.push(value);
				break;
			}
			case Lexer::openBracket:
			{
				operators.push(new Bracket());
				break;
			}
			case Lexer::closeBracket:
			{
				while (!operators.isEmpty())
				{
					Operator *op = operators.pop();
					if (op->getPriority() == -1)
					{
						delete op;
						break;
					}
					op->interpret();
					delete op;
				}
				break;
			}
			default:
			{
				Operator *op = getOperator(currentToken, result);
				while (!operators.isEmpty() && (operators.getTop()->getPriority() > op->getPriority()
				       || (operators.getTop()->getPriority() == op->getPriority() && op->isLeftAssociative())))
				{
					operators.getTop()->interpret();
					delete operators.pop();
				}
				operators.push(op);
				break;
			}
		}
		currentToken = expr.getNextToken(value);
	}
	while (!operators.isEmpty())
	{
		operators.getTop()->interpret();
		delete operators.pop();
	}
	return result.isEmpty() ? 0 : result.pop();
}

Calculator::Operator *Calculator::getOperator(Lexer::Token token, IStack<double> &data)
{
	switch (token)
	{
		case Lexer::add:
			return new Add(&data);
		case Lexer::subtract:
			return new Subtract(&data);
		case Lexer::multiply:
			return new Multiply(&data);
		case Lexer::division:
			return new Division(&data);
		case Lexer::openBracket:
			return new Bracket();
		case Lexer::sqrt:
			return new Sqrt(&data);
		default:
			return nullptr;
	}
}

int Calculator::Operator::getPriority() const
{
	return priority;
}

bool Calculator::Operator::isLeftAssociative() const
{
	return leftAssociative;
}

Calculator::Add::Add(IStack<double> *data)
{
	this->data = data;
	priority = 1;
	leftAssociative = true;
}

void Calculator::Add::interpret()
{
	double num1 = data->pop();
	double num2 = data->pop();
	data->push(num2 + num1);
}

Calculator::Subtract::Subtract(IStack<double> *data)
{
	this->data = data;
	priority = 1;
	leftAssociative = true;
}

void Calculator::Subtract::interpret()
{
	double num1 = data->pop();
	double num2 = data->pop();
	data->push(num2 - num1);
}

Calculator::Multiply::Multiply(IStack<double> *data)
{
	this->data = data;
	priority = 2;
	leftAssociative = true;
}

void Calculator::Multiply::interpret()
{
	double num1 = data->pop();
	double num2 = data->pop();
	data->push(num2 * num1);
}

Calculator::Division::Division(IStack<double> *data)
{
	this->data = data;
	priority = 2;
	leftAssociative = true;
}

void Calculator::Division::interpret()
{
	double num1 = data->pop();
	double num2 = data->pop();
	data->push(num2 / num1);
}

Calculator::Bracket::Bracket()
{
	priority = -1;
	leftAssociative = false;
}

void Calculator::Bracket::interpret()
{}

Calculator::Sqrt::Sqrt(IStack<double> *data)
{
	this->data = data;
	priority = 3;
	leftAssociative = false;
}

void Calculator::Sqrt::interpret()
{
	double num = data->pop();
	data->push(sqrt(num));
}


