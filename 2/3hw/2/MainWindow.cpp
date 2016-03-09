#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QString>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	QObject::connect(ui->firstArgument, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
	                 this, &MainWindow::calculate);
	QObject::connect(ui->secondArgument, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
	                 this, &MainWindow::calculate);
	QObject::connect(ui->operation, &QComboBox::currentTextChanged,
	                 this, &MainWindow::calculate);
	calculate();
}

void MainWindow::calculate()
{
	char operation = ui->operation->currentText()[0].toLatin1();
	int result = 0;
	bool isCorrect = true;
	int number1 = ui->firstArgument->value();
	int number2 = ui->secondArgument->value();
	switch (operation)
	{
		case '+':
			result = number1 + number2;
			break;
		case '-':
			result = number1 - number2;
			break;
		case '*':
			result = number1 * number2;
			break;
		case '/':
			if (number2 == 0)
				isCorrect = false;
			else
				result = number1 / number2;
			
	}
	if (isCorrect)
		ui->result->setText(QString::number(result));
	else
		ui->result->setText(QString("Error"));
}

MainWindow::~MainWindow()
{
	delete ui;
}
