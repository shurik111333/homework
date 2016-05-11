#pragma once

#include <QtCore/QObject>
#include <QtTest/QtTest>
#include <map>
#include "bag.h"

class BagTest : public QObject
{
	Q_OBJECT

public:
	explicit BagTest(QObject *parent = 0):
	    QObject(parent)
	{}

private:
	Bag<int> set;
	std::map<int, int> stdSet;
	static const int maxCount = 10000;
	static const int range = 10000;

	void compare()
	{
		QCOMPARE(set.size(), (int)stdSet.size());
		for (auto x : stdSet)
			QCOMPARE(set.find(x.first), x.second);
	}

	void fill(Bag<int> &set, std::map<int, int> &stdSet, int count = maxCount)
	{
		for (int i = 0; i < count; i++)
		{
			int x = rand() % range - range / 2;
			stdSet[x]++;
			set.insert(x);
		}
	}

private slots:

	void init()
	{
		set.clear();
		stdSet.clear();
	}

	void testAddManyRandomElements()
	{
		fill(set, stdSet);
		compare();
		// Check that after Bag::exist() no one element was lost.
		compare();
	}

	void testRemoveElements()
	{
		fill(set, stdSet);
		for (int i = 0; i < maxCount / 2 && !stdSet.empty(); i++)
		{
			int x = rand();
			stdSet.erase(x);
			set.remove(x);
		}
		compare();
	}

	void testIntersec()
	{
		Bag<int> set1;
		Bag<int> set2;
		std::map<int, int> stdSet1;
		std::map<int, int> stdSet2;
		fill(set1, stdSet1);
		fill(set2, stdSet2);
		set = set1.intersect(set2);
		for (auto x : stdSet1)
		{
			if (stdSet2.find(x.first) != stdSet2.end())
				stdSet[x.first] = min(x.second, stdSet2[x.first]);
		}
		compare();
	}

	void testMerge()
	{
		Bag<int> set1;
		Bag<int> set2;
		std::map<int, int> stdSet2;
		fill(set1, stdSet);
		fill(set2, stdSet2);
		set = set1.merge(set2);
		for (auto x : stdSet2)
			stdSet[x.first] += x.second;
		compare();
	}
};
