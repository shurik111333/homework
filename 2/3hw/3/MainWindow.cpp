#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Calculator.h"
#include "StackArray.h"
#include <QSignalMapper>
#include <QChar>
#include <cctype>
#include <QStringList>
#include <QGridLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    balance(0),
    tokens(new StackArray<Token>())
{
	ui->setupUi(this);
	clearOutput();
	QSignalMapper *forPrint = new QSignalMapper(this);
	for (QPushButton *button : this->findChildren<QPushButton*>())
	{
		if (button->text() == "clear" || button->text() == "<-")
			continue;
		QObject::connect(button, &QPushButton::pressed,
		                 forPrint, static_cast<void(QSignalMapper::*)()>(&QSignalMapper::map));
		forPrint->setMapping(button, button->text());
	}
	QObject::connect(forPrint, static_cast<void(QSignalMapper::*)(const QString&)>(&QSignalMapper::mapped),
	                 this, &MainWindow::print);
	QObject::connect(ui->buttonClear, &QPushButton::pressed,
	                 this, &MainWindow::clearOutput);
	QObject::connect(ui->buttonBackspace, &QPushButton::pressed,
	                 this, &MainWindow::backspace);
}

bool isFunction(const QString &str)
{
	return (str == "sqrt");
}

QString operatorForPrint(const QString &value)
{
	return QString(" " + value + " ");
}

void MainWindow::print(const QString &value)
{
	switch (value[0].toLatin1())
	{
		case '+':
		case '-':
		case '*':
		case '/':
			printOperation(value);
			break;
		case '(':
			printOpenBracket();
			break;
		case ')':
			printCloseBracket();
			break;
		case '.':
			printPoint();
			break;
		case '=':
			printResult();
			break;
		default:
			if (isFunction(value))
			{
				printFunction(value);
				break;
			}
			printNumber(value);
			break;
	}
}

void MainWindow::removeLastSymbols(int n)
{
	for (int i = 0; i < n; i++)
	{
		ui->result->setCursorPosition(ui->result->text().length());
		ui->result->backspace();
	}
}

void MainWindow::appendToResulOutput(QString str)
{
	ui->result->setCursorPosition(ui->result->text().length());
	ui->result->insert(str);
}

MainWindow::~MainWindow()
{
	delete ui;
	delete tokens;
}

void MainWindow::clearOutput()
{
	ui->result->setText("0");
	tokens->clear();
	//currentState = State::start;
	tokens->push(Token(State::start, 0));
	balance = 0;
}

void MainWindow::backspace()
{
	if (tokens->getTop().state == State::start)
		return;
	removeLastSymbols(tokens->getTop().length);
	tokens->pop();
	if (tokens->getTop().state == State::start)
		clearOutput();
	
}

void MainWindow::printOperation(const QString &value)
{
	int len = 0;
	switch (tokens->getTop().state)
	{
		case State::error:
		case State::openBracket:
			return;
		case State::function:
			appendToResulOutput("(");
			len++;
			balance++;
		case State::digitPoint:
			appendToResulOutput("0");
			len++;
		case State::start:
		case State::digitInteger:
		case State::digitFraction:
		case State::closeBracket:
			appendToResulOutput(" " + value + " ");
			len += value.length() + 2;
			break;
		case State::operation:
			{
				removeLastSymbols(3);
				QString forPrint = operatorForPrint(value);
				appendToResulOutput(forPrint);
				len += forPrint.length();
				break;
			}
		case State::result:
			{
				QString result = ui->result->text().split(' ').last();
				/*ui->result->setText("");
				if (result[0] == '-')
				{
					ui->result->insert("0 - ");
					result.remove(0, 1);
				}*/
				clearOutput();
				ui->result->setText(result.append(operatorForPrint(value)));
				len = ui->result->text().length();
				break;
			}
	}
	//currentState = State::operation;
	tokens->push(Token(State::operation, len));
}

void MainWindow::printFunction(const QString &value)
{
	int len = 0;
	switch (tokens->getTop().state)
	{
		case State::start:
		case State::error:
		case State::result:
			clearOutput();
			ui->result->setText(value + " ");
			len = ui->result->text().length();
			break;
		case State::operation:
		case State::openBracket:
		case State::function:
			{
				QString forPrint = operatorForPrint(value);
				appendToResulOutput(forPrint);
				len = forPrint.length();
				break;
			}
		default:
			return;
	}
	//currentState = State::function;
	tokens->push(Token(State::function, len));
}

void MainWindow::printNumber(const QString &value)
{
	int len = value.length();
	switch (tokens->getTop().state)
	{
		case State::start:
		case State::error:
		case State::result:
			clearOutput();
			ui->result->setText(value);
			//currentState = State::digitInteger;
			tokens->push(Token(State::digitInteger, len));
			break;
		default:
			appendToResulOutput(value);
			if (tokens->getTop().state == State::digitPoint || tokens->getTop().state == State::digitFraction)
				//currentState = State::digitFraction;
				tokens->push(Token(State::digitFraction, len));
			else
				//currentState = State::digitInteger;
				tokens->push(Token(State::digitInteger, len));
			break;
	}
}

void MainWindow::printPoint()
{
	int len = 0;
	switch (tokens->getTop().state)
	{
		case State::closeBracket:
		case State::digitFraction:
		case State::digitPoint:
			return;
		case State::error:
		case State::result:
			clearOutput();
			ui->result->setText("");
		case State::operation:
		case State::function:
		case State::openBracket:
			appendToResulOutput("0");
			len++;
		default:
			appendToResulOutput(".");
			len++;
			break;
	}
	//currentState = State::digitPoint;
	tokens->push(Token(State::digitPoint, len));
}

void MainWindow::printOpenBracket()
{
	int len = 0;
	switch (tokens->getTop().state)
	{
		case State::closeBracket:
		case State::digitFraction:
		case State::digitInteger:
		case State::digitPoint:
			return;
		case State::error:
		case State::result:
		case State::start:
			clearOutput();
			ui->result->setText("");
		default:
			appendToResulOutput("(");
			len++;
			balance++;
			break;
	}
	//currentState = State::openBracket;
	tokens->push(Token(State::openBracket, len));
}

void MainWindow::printCloseBracket()
{
	if (balance == 0)
		return;
	int len = 0;
	switch (tokens->getTop().state)
	{
		case State::digitPoint:
			appendToResulOutput("0");
			len++;
		case State::closeBracket:
		case State::digitFraction:
		case State::digitInteger:
			appendToResulOutput(")");
			len++;
			balance--;
			break;
		default:
			return;
	}
	//currentState = State::closeBracket;
	tokens->push(Token(State::closeBracket, len));
}

void MainWindow::printResult()
{
	int len = 0;
	State state;
	switch (tokens->getTop().state)
	{
		case State::error:
		case State::function:
		case State::openBracket:
		case State::operation:
		case State::result:
		case State::start:
			return;
		default:
			for (int i = 0; i < balance; i++)
			{
				appendToResulOutput(")");
				tokens->push(Token(State::closeBracket, 1));
			}
			balance = 0;
			QString forPrint;
			try
			{
				double result = Calculator::calculate(ui->result->text().toStdString());
				forPrint = QString::number(result);
				state = State::result;
			}
			catch (QString message)
			{
				forPrint = message;
				state = State::error;
			}
			appendToResulOutput(" = " + forPrint);
			len += forPrint.length() + 3;
			tokens->push(Token(state, len));
			break;
	}
}
