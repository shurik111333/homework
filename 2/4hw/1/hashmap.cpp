#include "hashmap.h"

HashMap::HashMap(IHash *hash, int size)
    : size(size), 
      countElements(0), 
      maxChainIndex(0), 
      emptySpaces(size), 
      averageLengthOfChain(0), 
      hash(hash)
{
	array = new QList<Element>*[size];
	for (int i = 0; i < size; i++)
	{
		array[i] = nullptr;
	}
}

void HashMap::insert(QString &key, int value)
{
	
}

void HashMap::remove(QString &key, int value)
{
	
}
