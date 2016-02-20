#include "Calculator.h"

double Calculator::calculate(string expression)
{
	StackArray<double> result;
	StackArray<Operator*> operators;
	Lexer expr(expression);
	int value = 0;
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
						break;
					op->interpret();
					delete op;
				}
				break;
			}
			default:
			{
				Operator *op = getOperator(currentToken, result);
				while (!operators.isEmpty() && operators.getTop()->getPriority() >= op->getPriority())
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
		default:
			return nullptr;
	}
}

Calculator::Add::Add(IStack<double> *data)
{
	this->data = data;
}

Calculator::Subtract::Subtract(IStack<double> *data)
{
	this->data = data;
}

Calculator::Multiply::Multiply(IStack<double> *data)
{
	this->data = data;
}

Calculator::Division::Division(IStack<double> *data)
{
	this->data = data;
}

int Calculator::Add::getPriority() const
{
	return 1;
}

int Calculator::Subtract::getPriority() const
{
	return 1;
}

int Calculator::Multiply::getPriority() const
{
	return 2;
}

int Calculator::Division::getPriority() const
{
	return 2;
}

int Calculator::Bracket::getPriority() const
{
	return -1;
}

void Calculator::Add::interpret()
{
	double num1 = data->pop();
	double num2 = data->pop();
	data->push(num2 + num1);
}

void Calculator::Subtract::interpret()
{
	double num1 = data->pop();
	double num2 = data->pop();
	data->push(num2 - num1);
}

void Calculator::Multiply::interpret()
{
	double num1 = data->pop();
	double num2 = data->pop();
	data->push(num2 * num1);
}

void Calculator::Division::interpret()
{
	double num1 = data->pop();
	double num2 = data->pop();
	data->push(num2 / num1);
}

void Calculator::Bracket::interpret()
{}
