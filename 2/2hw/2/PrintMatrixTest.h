#pragma once

#include <QtCore/QObject>
#include <QtTest/QtTest>
#include <QList>
#include "IPrint.h"

class PrintMatrixTest : public QObject
{
	Q_OBJECT

public:
	explicit PrintMatrixTest(QObject *parent = 0):
	    QObject(parent)
	{}

private:
	QList<int> output;
	Output printer;

	class Output : public IPrint
	{
		void print(int n)
		{
			output.append(n);
		}
	};
};
