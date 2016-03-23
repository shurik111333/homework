#pragma once

#include <QtCore/QObject>
#include <QtTest/QtTest>
#include "ListArray.h"
#include "SortedSet.h"

class SortedSetTest : public QObject
{
	Q_OBJECT

public:
	explicit SortedSetTest(QObject *parent = 0)
	    :QObject(parent)
	{}

private:
	SortedSet *set;

	ListArray *getList(int size)
	{
		ListArray *list = new ListArray(size);
		for (int i = 0; i < size; i++)
		{
			list->insert(i, i);
		}
		return list;
	}

private slots:
	void init()
	{
		set = new SortedSet();
	}

	void cleanup()
	{
		set->clear();
		delete set;
	}

	// SortedSet::empty() ----------------------------------

	void testEmptySet()
	{
		QVERIFY(set->empty());
	}

	void testAddFewElementsAndCheckEmpty()
	{
		for (int i = 1; i < 10; i++)
		{
			set->add(getList(i));
			QVERIFY(!set->empty());
		}
	}

	// SortedSet::remove() ---------------------------------

	void testRemoveFromEmptySet()
	{
		for (int i = 1; i < 5; i++)
		{
			ListArray *list = getList(i);
			QVERIFY(!set->remove(list));
			delete list;
		}
	}

	void testAddAndRemoveOneElement()
	{
		set->add(getList(5));
		ListArray *list = getList(5);
		QVERIFY(set->remove(list));
		delete list;
		QVERIFY(set->empty());
	}

	void testRemoveFewElements()
	{
		for (int i = 1; i < 10; i++)
		{
			set->add(getList(i));
		}
		for (int i = 9; i > 0; i--)
		{
			ListArray *list = getList(i);
			QVERIFY(set->remove(list));
			delete list;
			QCOMPARE(set->getCount(), i - 1);
		}
	}

	// SortedSet::clear() ----------------------------------

	void testSetClear()
	{
		for (int i = 1; i < 10; i++)
		{
			set->add(getList(i));
		}
		set->clear();
		QVERIFY(set->empty());
	}

	//SortedSet::min() --------------------------------

	void testGetMinWhenAddIncreasingSequence()
	{
		for (int i = 1; i < 10; i++)
		{
			set->add(getList(i));
		}
		for (int i = 1; i < 10; i++)
		{
			QCOMPARE(set->min()->getCount(), i);
			set->remove(set->min());
		}
	}

	void testGetMinWhenAddDecresingSequence()
	{
		for (int i = 9; i > 0; i--)
		{
			set->add(getList(i));
		}
		for (int i = 1; i < 10; i++)
		{
			QCOMPARE(set->min()->getCount(), i);
			set->remove(set->min());
		}
	}

	// SortedSet::max() --------------------------------

	void testGetMaxWhenAddDecresingSequence()
	{
		for (int i = 9; i > 0; i--)
		{
			set->add(getList(i));
		}
		for (int i = 1; i < 10; i++)
		{
			QCOMPARE(set->max()->getCount(), 10 - i);
			set->remove(set->max());
		}
	}

	void testGetMaxWhenAddIncreasingSequence()
	{
		for (int i = 1; i < 10; i++)
		{
			set->add(getList(i));
		}
		for (int i = 1; i < 10; i++)
		{
			QCOMPARE(set->max()->getCount(), 10 - i);
			set->remove(set->max());
		}
	}

	// SortedSet::contains() ----------------------------------------

	void testContainsAllAddElements()
	{
		for (int i = 1; i < 10; i++)
		{
			set->add(getList(i));
		}
		for (int i = 1; i < 10; i++)
		{
			ListArray *list = getList(i);
			QVERIFY(set->contains(list));
			delete list;
		}
	}

	// SortedSet::getCount() ----------------------------------------

	void testCountOfEmptySet()
	{
		QCOMPARE(set->getCount(), 0);
	}

	void testCountOfNonEmptyStack()
	{
		for (int i = 1; i < 10; i++)
		{
			set->add(getList(i));
			QCOMPARE(set->getCount(), i);
		}
	}

	// Equals elements ----------------------------------------------

	void testTwoEqualElements()
	{
		set->add(getList(5));
		QVERIFY(!set->add(getList(5)));
		QCOMPARE(set->getCount(), 1);
	}

	void testAddEqualElement()
	{
		set->add(getList(3));
		set->add(getList(6));
		QVERIFY(!set->add(getList(6)));
		QCOMPARE(set->getCount(), 2);
	}

	void testAddFewEqualElements()
	{
		set->add(getList(4));
		for (int i = 0; i < 5; i++)
		{
			QVERIFY(!set->add(getList(4)));
		}
		QCOMPARE(set->getCount(), 1);
	}
};
