#pragma once

#include "ihash.h"
#include "polyhash.h"
#include <QList>
#include <QString>

class HashMap
{
public:
	HashMap(IHash *hash = new PolyHash(), int size = minSize);
	
	void insert(QString &key, int value);
	
	void remove(QString &key, int value);
	
private:
	static const int minSize = 10;
	int size;
	int countElements;
	int maxChainIndex;
	int emptySpaces;
	double averageLengthOfChain;
	IHash *hash;
	
	struct Element
	{
		QString key;
		int value;
	};
	
	QList<Element> **array;
};
