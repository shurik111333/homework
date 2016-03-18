#include "hashmap.h"

const double HashMap::_maxLoadFactor = 3;
const QString HashMap::notFound = "Key was not found.";
const QString HashMap::alreadyExist = "This key already exist.";

HashMap::HashMap(QSharedPointer<IHash> hash)
    : _size(_minSize),
      _countElements(0),
      _maxChainIndex(-1),
      _emptySpaces(_size),
      _hash(hash)
{
	array = getNewMap(_size);
}

HashMap::~HashMap()
{
	removeMap(array, _size);
}

int HashMap::occupiedCount()
{
	return _size - _emptySpaces;
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
	double res = 0;
	for (int i = 0; i < _size; i++)
	{
		res += array[i]->count();
	}
	return res == 0 ? 0 :res / (size() - countEmpty());
}

int HashMap::countEmpty() const
{
	return _emptySpaces;
}

void HashMap::setHashFunction(QSharedPointer<IHash> newHash)
{
	QList<Element> elements;
	for (int i = 0; i < _size; i++)
	{
		elements.append(*array[i]);
	}
	clear();
	_hash = newHash;
	for (auto el : elements)
	{
		insert(el.key, el.value);
	}
}

void HashMap::clear()
{
	for (int i = 0; i < _size; i++)
	{
		array[i]->clear();
	}
	_countElements = 0;
	_maxChainIndex = -1;
	_emptySpaces = _size;
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
	clear();
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
}

void HashMap::insert(const QString &key, int value)
{
	int index = _hash.data()->getHash(key) % _size;
	if (array[index]->contains({key, value}))
		throw alreadyExist;
	array[index]->append({key, value});
	updateInformation(index, Action::add);
}

void HashMap::remove(const QString &key, int value)
{
	int index = _hash.data()->getHash(key) % _size;
	if (!array[index]->contains({key, value}))
		throw notFound;
	updateInformation(index, Action::remove);
	array[index]->removeOne({key, value});
}

int HashMap::find(const QString &key) const
{
	int index = _hash.data()->getHash(key) % _size;
	for (auto element : *array[index])
	{
		if (element.key == key)
		{
			return element.value;
		}
	}
	throw notFound;
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
