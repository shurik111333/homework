#include "hashmap.h"

const double HashMap::_maxLoadFactor = 3;

HashMap::HashMap(IHash *hash)
    : _size(_minSize),
      _countElements(0),
      _maxChainIndex(-1),
      _emptySpaces(_size),
      _averageLengthOfChain(0),
      _hash(hash)
{
	array = getNewMap(_size);
}

HashMap::~HashMap()
{
	delete _hash;
	removeMap(array, _size);
}

int HashMap::occupiedCount()
{
	return _size - _emptySpaces;
}

/**
 * @brief HashMap::updateAverageLength Update average length after add or before remove
 * @param index Index of changing chain
 * @param action 1 or -1 for add and remove respectively
 */

void HashMap::updateAverageLength(int index, int action)
{
	if (array[index]->size() == 1)
		_averageLengthOfChain = (_averageLengthOfChain * (occupiedCount() - action) + action) / (occupiedCount());
	else
		_averageLengthOfChain = _averageLengthOfChain + action * 1.0 / occupiedCount();
}

int HashMap::getMaxLength() const
{
	int result = 0;
	for (int i = 0; i < _size; i++)
	{
		if (result < array[i]->size())
			result = array[i]->size();
	}
	return result;
}

double HashMap::averageLength() const
{
	return _averageLengthOfChain;
}

int HashMap::countEmpty() const
{
	return _emptySpaces;
}

void HashMap::replace(const QString &key, int oldValue, int newValue)
{
	remove(key, oldValue);
	insert(key, newValue);
}

void HashMap::setHashFunction(IHash *newHash)
{
	QList<Element> elements;
	for (int i = 0; i < _size; i++)
	{
		elements.append(*array[i]);
		array[i]->clear();
	}
	_hash = newHash;
	for (auto el : elements)
	{
		insert(el.key, el.value);
	}
}

QList<HashMap::Element> **HashMap::getNewMap(int size)
{
	QList<Element> **res = new QList<Element>*[size];
	for (int i = 0; i < size; i++)
	{
		res[i] = new QList<Element>();
	}
	return res;
}

void HashMap::removeMap(QList<HashMap::Element> **&map, int size)
{
	for (int i = 0; i < size; i++)
	{
		delete map[i];
	}
	delete[] map;
}

void HashMap::increase()
{
	QList<Element> **oldMap = array;
	int oldSize = _size;
	_size *= _factorSize;
	array = getNewMap(_size);
	for (int i = 0; i < oldSize; i++)
	{
		for (Element el : *array[i])
		{
			insert(el.key, el.value);
		}
	}
	removeMap(oldMap, oldSize);
}

void HashMap::updateInformation(int index, HashMap::Action action)
{
	_countElements += (int)action;
	if (array[index]->size() == 1)
		_emptySpaces -= (int)action;
	updateAverageLength(index, (int)action);
}

void HashMap::insert(const QString &key, int value)
{
	int index = _hash->getHash(key) % _size;
	if (array[index]->contains({key, value}))
		throw QString("This pair of {key, value} already exist.");
	array[index]->append({key, value});
	updateInformation(index, Action::add);
}

void HashMap::remove(const QString &key, int value)
{
	int index = _hash->getHash(key) % _size;
	if (!array[index]->contains({key, value}))
		throw QString("This par of {key, value} are not exist.");
	updateInformation(index, Action::remove);
	array[index]->removeOne({key, value});
}

QList<int> *HashMap::find(const QString &key) const
{
	QList<int> *result = new QList<int>();
	int index = _hash->getHash(key) % _size;
	for (auto element : *array[index])
	{
		if (element.key == key)
			result->append(element.value);
	}
	return result;
}

int HashMap::count() const
{
	return _countElements;
}

int HashMap::size() const
{
	return _size;
}

double HashMap::loadFactor() const
{
	return 1.0 * count() / size();
}
