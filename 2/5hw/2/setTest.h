#pragma once

#include <QtCore/QObject>
#include <QtTest/QtTest>
#include <set>
#include "set.h"

class SetTest : public QObject
{
	Q_OBJECT

public:
	explicit SetTest(QObject *parent = 0):
	    QObject(parent)
	{}

private:
	Set<int> set;
	std::set<int> stdSet;
	static const int maxCount = 30000;

	void compare()
	{
		QVERIFY(stdSet.size() == set.size());
		for (int x : stdSet)
			QVERIFY(set.exist(x));
	}

	void fill(Set<int> &set, std::set<int> &stdSet, int count = maxCount)
	{
		for (int i = 0; i < count; i++)
		{
			int x = rand();
			stdSet.insert(x);
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
		// Check that after Set::exist() no one element was lost.
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
		Set<int> set1;
		Set<int> set2;
		std::set<int> stdSet1;
		std::set<int> stdSet2;
		fill(set1, stdSet1);
		fill(set2, stdSet2);
		set1.intersec(set2, set);
		for (int x : stdSet1)
			if (stdSet2.find(x) != stdSet2.end())
				stdSet.insert(x);
		compare();
	}

	void testMerge()
	{
		Set<int> set1;
		Set<int> set2;
		std::set<int> stdSet2;
		fill(set1, stdSet);
		fill(set2, stdSet2);
		set1.merge(set2, set);
		for (int x : stdSet2)
			stdSet.insert(x);
		compare();
	}
};
