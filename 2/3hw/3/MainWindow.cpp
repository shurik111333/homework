#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QSignalMapper>
#include "Calculator.h"
#include <QChar>
#include <cctype>
#include <QStringList>
#include <QGridLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    currentState(State::start),
    balance(0)
{
	ui->setupUi(this);
	ui->result->setText("0");
	QSignalMapper *forPrint = new QSignalMapper(this);
	for (QPushButton *button : this->findChildren<QPushButton*>())
	{
		if (button->text() == "clear")
			continue;
		QObject::connect(button, &QPushButton::pressed,
		                 forPrint, static_cast<void(QSignalMapper::*)()>(&QSignalMapper::map));
		forPrint->setMapping(button, button->text());
	}
	QObject::connect(forPrint, static_cast<void(QSignalMapper::*)(const QString&)>(&QSignalMapper::mapped),
	        this, &MainWindow::print);
	QObject::connect(ui->buttonClear, &QPushButton::pressed,
	                 this, &MainWindow::clear);
}

bool isFunction(const QString &str)
{
	return (str == "sqrt");
}

QString operatorWithSpaces(const QString &value)
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

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::clear()
{
	ui->result->setText("0");
	currentState = State::start;
	balance = 0;
}

void MainWindow::printOperation(const QString &value)
{
	switch (currentState)
	{
		case State::error:
			return;
		case State::function:
			ui->result->insert("(");
		case State::openBracket:
		case State::digitPoint:
			ui->result->insert("0");
		case State::start:
		case State::digitInteger:
		case State::digitFraction:
		case State::closeBracket:
			ui->result->insert(" " + value + " ");
			break;
		case State::operation:
		{
			QString expr = ui->result->text();
			expr.remove(expr.length() - 3, 3);
			ui->result->setText(expr.append(operatorWithSpaces(value)));
			break;
		}
		case State::result:
		{
			QString result = ui->result->text().split(' ').last();
			ui->result->setText("");
			if (result[0] == '-')
			{
				ui->result->insert("0 - ");
				result.remove(0, 1);
			}
			ui->result->insert(result.append(operatorWithSpaces(value)));
			break;
		}
	}
	currentState = State::operation;
}

void MainWindow::printFunction(const QString &value)
{
	switch (currentState)
	{
		case State::start:
		case State::error:
		case State::result:
			ui->result->setText(value + " ");
			break;
		case State::operation:
		case State::openBracket:
		case State::function:
			ui->result->insert(operatorWithSpaces(value));
			break;
		default:
			return;
	}
	currentState = State::function;
}

void MainWindow::printNumber(const QString &value)
{
	switch (currentState)
	{
		case State::start:
		case State::error:
		case State::result:
			ui->result->setText(value);
			currentState = State::digitInteger;
			break;
		default:
			if (currentState == State::digitPoint || currentState == State::digitFraction)
				currentState = State::digitFraction;
			else
				currentState = State::digitInteger;
			ui->result->insert(value);
			break;
	}
}

void MainWindow::printPoint()
{
	switch (currentState)
	{
		case State::closeBracket:
		case State::digitFraction:
		case State::digitPoint:
			return;
		case State::error:
		case State::result:
			ui->result->setText("");
		case State::operation:
		case State::function:
		case State::openBracket:
			ui->result->insert("0");
		default:
			ui->result->insert(".");
			break;
	}
	currentState = State::digitPoint;
}

void MainWindow::printOpenBracket()
{
	switch (currentState)
	{
		case State::closeBracket:
		case State::digitFraction:
		case State::digitInteger:
		case State::digitPoint:
			return;
		case State::error:
		case State::result:
		case State::start:
			ui->result->setText("");
		default:
			ui->result->insert("(");
			balance++;
			break;
	}
	currentState = State::openBracket;
}

void MainWindow::printCloseBracket()
{
	if (balance == 0)
		return;
	switch (currentState)
	{
		case State::digitPoint:
			ui->result->insert("0");
		case State::closeBracket:
		case State::digitFraction:
		case State::digitInteger:
			ui->result->insert(")");
			balance--;
			break;
		default:
			return;
	}
	currentState = State::closeBracket;
}

void MainWindow::printResult()
{
	switch (currentState)
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
				ui->result->insert(")");
			balance = 0;
			double result = Calculator::calculate(ui->result->text().toStdString());
			ui->result->insert(" = " + QString::number(result));
			break;
	}
	currentState = State::result;
}
