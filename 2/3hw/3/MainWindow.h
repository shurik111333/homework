#pragma once

#include <QMainWindow>

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
	void clear();
	
	void print(const QString &value);
	
private:
	Ui::MainWindow *ui;
	int balance;
	
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
	State currentState;
};

