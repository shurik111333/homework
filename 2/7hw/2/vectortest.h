#pragma once

#include <QtCore/QObject>
#include <QtTest/QtTest>
#include <cstdlib>
#include <ctime>
#include "vector.h"

class VectorTest : public QObject
{
	Q_OBJECT

public:
	explicit VectorTest(QObject *parent = 0):
	    QObject(parent)
	{
		srand(time(0));
	}

private:
	void fillCoordinates(int *coords, int n)
	{
		for (int i = 0; i < n; i++)
			coords[i] = rand() % range - range / 2;
	}

	const int range = 200;

private slots:
	void testCreateNullVector()
	{
		Vector<5> v;
		QVERIFY(v.isNull());
	}

	void testCreateVectorWithEqualCoordinates()
	{
		for (int k = 0; k < 100; k++)
		{
			int x = rand();
			Vector<5> v1(x);
			for (int i = 0; i < 5; i++)
			{
				QCOMPARE(v1[i], x);
			}
		}
	}

	void testCreateVectorWithDifferentCoordinates()
	{
		int coords[6];
		for (int k = 0; k < 100; k++)
		{
			fillCoordinates(coords, 6);
			Vector<6> v1(coords);
			for (int i = 0; i < 6; i++)
			{
				QCOMPARE(v1[i], coords[i]);
			}
		}
	}

	void testAtFunction()
	{
		int coords[6];
		for (int k = 0; k < 100; k++)
		{
			fillCoordinates(coords, 6);
			Vector<6> v1(coords);
			for (int i = 0; i < 6; i++)
			{
				QCOMPARE(v1.at(i), coords[i]);
			}
		}
	}

	void testEqualOperator()
	{
		int coords1[6];
		int coords2[6];
		fillCoordinates(coords1, 6);
		fillCoordinates(coords2, 6);
		coords2[0] = coords1[0] + 1; //for exclude equal coordinates
		Vector<6> v1(coords1);
		Vector<6> v2(coords1);
		QVERIFY(v1 == v2);
		Vector<6> v3(coords2);
		QVERIFY(!(v1 == v3));
	}

	void testCopyConstructor()
	{
		int coords[6];
		fillCoordinates(coords, 6);
		Vector<6> v1(coords);
		Vector<6> v2(v1);
		QVERIFY(v1 == v2);
	}

	void testSubtractAndAdditionVectors()
	{
		int coords1[6];
		int coords2[6];
		for (int i = 0; i < 100; i++)
		{
			fillCoordinates(coords1, 6);
			fillCoordinates(coords2, 6);
			Vector<6> v1(coords1);
			Vector<6> v2(coords2);
			auto v3 = v1 - v2;
			auto v4 = v1 + v2;
			for (int j = 0; j < 6; j++)
			{
				QCOMPARE(v3[j], (coords1[j] - coords2[j]));
				QCOMPARE(v4[j], (coords1[j] + coords2[j]));
			}
		}
	}

	void testScalarProduct()
	{
		int coords1[6];
		int coords2[6];
		for (int i = 0; i < 100; i++)
		{
			fillCoordinates(coords1, 6);
			fillCoordinates(coords2, 6);
			Vector<6> v1(coords1);
			Vector<6> v2(coords2);
			int res = 0;
			for (int j = 0; j < 6; j++)
			{
				res += coords1[j] * coords2[j];
			}
			QCOMPARE(v1 * v2, res);
		}
	}
};
