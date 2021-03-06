#pragma once

#include "ihash.h"
#include "polyhash.h"
#include <QList>
#include <QString>
#include <QSharedPointer>

class HashMap
{
public:
	HashMap(QSharedPointer<IHash> hash = QSharedPointer<IHash>(new PolyHash()));
	~HashMap();

	void insert(const QString &key, int value);
	void remove(const QString &key, int value);
	int find(const QString &key) const;
	int count() const;
	int size() const;
	double loadFactor() const;
	int getMaxLength() const;
	double averageLength() const;
	int countEmpty() const;
	void setHashFunction(QSharedPointer<IHash> newHash);
	void clear();

private:
	static const int _minSize = 10;
	int _size;
	int _countElements;
	int _maxChainIndex;
	int _emptySpaces;
	QSharedPointer<IHash> _hash;
	static const double _maxLoadFactor;
	static const int _factorSize = 2;
	static const QString notFound;
	static const QString alreadyExist;

	struct Element
	{
		QString key;
		int value;

		bool operator == (const Element &e)
		{
			return key == e.key;
		}
	};

	enum class Action
	{
		add = 1,
		remove = -1
	};

	QList<Element> **array;
	static QList<Element> **getNewMap(int size);
	static void removeMap(QList<Element> **&map, int size);
	void increase();
	int occupiedCount();
	void updateInformation(int index, Action action);
};
