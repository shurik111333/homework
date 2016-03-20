#include "mainWidget.h"
#include "hashmaptests.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	HashmapTest mapTest;
	QTest::qExec(&mapTest);

	QApplication a(argc, argv);
	Widget w;
	w.show();

	return a.exec();
}
