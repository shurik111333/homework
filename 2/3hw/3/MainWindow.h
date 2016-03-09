#pragma once

#include <QMainWindow>
#include "IStack.h"

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT
	
public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();
	
public slots:
	void clearOutput();
	void backspace();
	void print(const QString &value);
	
private:
	Ui::MainWindow *ui;
	int balance;
	
	void removeLastSymbols(int n);
	void appendToResulOutput(QString str);
	void printOperation(const QString &value);
	void printFunction(const QString &value);
	void printNumber(const QString &value);
	void printPoint();
	void printOpenBracket();
	void printCloseBracket();
	void printResult();
	
	enum class State
	{
		start,
		digitInteger,
		digitPoint,
		digitFraction,
		operation,
		openBracket,
		closeBracket,
		function,
		result,
		error
	};
	
	struct Token
	{
		State state;
		int length;
		
		Token()
		    :state(State::start), length(0)
		{}
		
		Token(State state, int length)
		    :state(state), length(length)
		{}
	};
	
	IStack<Token> *tokens;
};

