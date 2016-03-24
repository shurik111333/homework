#include "MainWindow.h"
#include "calculatortest.h"
#include <QApplication>
#include <QtTest/QtTest>

int main(int argc, char *argv[])
{
	CalculatorTest test;
	QTest::qExec(&test);

	QApplication a(argc, argv);
	MainWindow w;
	w.show();
	return a.exec();
	return 0;
}
