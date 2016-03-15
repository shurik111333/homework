#pragma once

#include "ihash.h"
#include "polyhash.h"
#include <QList>
#include <QString>

class HashMap
{
public:
	HashMap(IHash *hash = new PolyHash());

	void insert(const QString &key, int value);
	void remove(const QString &key, int value);
	QList<int> *find(const QString &key) const;
	int count() const;
	int size() const;
	double loadFactor() const;
	int getMaxLength() const;
	double averageLength() const;
	int countEmpty() const;
	void replace(const QString &key, int oldValue, int newValue);

private:
	static const int _minSize = 10;
	int _size;
	int _countElements;
	int _maxChainIndex;
	int _emptySpaces;
	double _averageLengthOfChain;
	IHash *_hash;

	struct Element
	{
		QString key;
		int value;

		bool operator == (const Element &e)
		{
			return key == e.key && value == e.value;
		}
	};

	enum class Action
	{
		add = 1,
		remove = -1
	};

	QList<Element> **array;
	void increase();
	int occupiedCount();
	void updateAverageLength(int index, int action);
	void updateInformation(int index, Action action);
};
