#include <QApplication>
#include "mainWidget.h"
#include "tictactoetest.h"

int main(int argc, char *argv[])
{
	TicTacToeTest test;
	QTest::qExec(&test);

	QApplication a(argc, argv);
	MainWidget w;
	w.show();

	return a.exec();
}
