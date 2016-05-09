#pragma once

#include <QtTest/QtTest>
#include <QtCore/QObject>
#include "sharedptr.h"

class SharedPtrTest : public QObject
{
	Q_OBJECT

public:
	explicit SharedPtrTest(QObject *parent = 0):
	    QObject(parent)
	{}

private slots:
	void testReturnObjectAndPointerToObject()
	{
		SharedPtr<int> ptr1(new int(5));
		QCOMPARE(*ptr1, 5);
		QCOMPARE(*ptr1.getPointer(), 5);
		SharedPtr<int> ptr2(new int(10));
		QCOMPARE(*ptr2, 10);
		QCOMPARE(*ptr2.getPointer(), 10);
	}

	void testStartCountPointers()
	{
		SharedPtr<int> ptr1(new int(20));
		QCOMPARE(ptr1.getCount(), 1);
	}

	void testCopyConstructor()
	{
		SharedPtr<int> ptr1(new int(20));
		SharedPtr<int> ptr2(ptr1);
		QCOMPARE(ptr1.getPointer(), ptr2.getPointer());
		QCOMPARE(ptr1.getCount(), 2);
	}

	void testDestructor()
	{
		SharedPtr<int> ptr1(new int(15));
		auto ptr2 = new SharedPtr<int>(ptr1);
		delete ptr2;
		QCOMPARE(ptr1.getCount(), 1);
	}

	void testCopyOperator()
	{
		SharedPtr<int> ptr1(new int(11));
		auto ptr2 = ptr1;
		QCOMPARE(*ptr1, *ptr2);
		QCOMPARE(ptr1.getCount(), ptr2.getCount());
		QCOMPARE(ptr1.getCount(), 2);
	}

	void testCopyToPointerThatContainsPointer()
	{
		SharedPtr<int> ptr1(new int(10));
		SharedPtr<int> ptr2(new int(6));
		auto ptr3 = ptr2;
		QCOMPARE(ptr2.getCount(), 2);
		ptr3 = ptr1;
		QCOMPARE(ptr2.getCount(), 1);
		QCOMPARE(ptr1.getCount(), 2);
	}
};
