#pragma once

#include <QtCore/QObject>
#include <QtTest/QtTest>
#include <QList>
#include "IPrint.h"
#include "PrintMatrix.h"

class PrintMatrixTest : public QObject
{
	Q_OBJECT

public:
	explicit PrintMatrixTest(QObject *parent = 0):
	    QObject(parent)
	{}

private:
	QList<int> *output = printer.getOutput();
	const int maxSize = 11;
	int **matrix;

	class Output : public IPrint
	{
	public:
		void print(int n)
		{
			output.append(n);
		}

		QList<int> *getOutput()
		{
			return &output;
		}

	private:
		QList<int> output;
	};

	Output printer;

	void fillMatrix(int n)
	{
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				matrix[i][j] = i * n + j + 1;
	}

	void check(int answer[])
	{
		int i = 0;
		for (int out : *output)
		{
			QCOMPARE(out, answer[i++]);
		}
	}

private slots:
	void init()
	{
		matrix = new int*[maxSize];
		for (int i = 0; i < maxSize; i++)
			matrix[i] = new int[maxSize];
		output->clear();
	}

	void cleanup()
	{
		for (int i = 0; i < maxSize; i++)
			delete[] matrix[i];
		delete[] matrix;
	}

	void testMatrix1x1()
	{
		matrix[0][0] = 5;
		PrintMatrix::print(matrix, 1, &printer);
		QCOMPARE(output->size(), 1);
		QCOMPARE((*output)[0], 5);
	}

	void testMatrix3x3()
	{
		fillMatrix(3);
		PrintMatrix::print(matrix, 3, &printer);
		QCOMPARE(output->size(), 9);
		int answer[9] = {5, 2, 3, 6, 9, 8, 7, 4, 1};
		check(answer);
	}

	void testMatrix5x5()
	{
		fillMatrix(5);
		PrintMatrix::print(matrix, 5, &printer);
		QCOMPARE(output->size(), 25);
		int answer[25] = {13, 8, 9, 14, 19,
		                  18, 17, 12, 7, 2,
		                  3, 4, 5, 10, 15,
		                  20, 25, 24, 23, 22,
		                  21, 16, 11, 6, 1};
		check(answer);
	}
};
