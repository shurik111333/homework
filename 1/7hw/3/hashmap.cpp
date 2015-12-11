#include "bst.h"
#include "myString.h"
#include <algorithm>

struct Hashmap
{
    BST **array;
    int size;
    int countElements;
    int maxChainIndex;
    int emptySpaces;
    double averageLengthOfChain;

    Hashmap(int size)
    {
        array = getNewBSTArray(size);
        this->size = size;
        emptySpaces = size;
        countElements = 0;
        maxChainIndex = 0;
        averageLengthOfChain = 0;
    }
};

const double maxLoadFactor = 3;
const int factorSize = 3;
const int maxSize = 100000;

int getOccupiedCount(Hashmap *map)
{
    return map->size - map->emptySpaces;
}

double getLoadFactor(Hashmap *map)
{
    return 1.0 * map->countElements / map->size;
}

Hashmap *getNewHashmap(int size)
{
    return new Hashmap(size);
}

int getMapSize(Hashmap *map)
{
    return map ? map->size : 0;
}

int newSize(Hashmap *map)
{
    return map->size * factorSize;
}

void addToMap(Hashmap *&map, String *string, int count);

void increaseMap(Hashmap *&map)
{
    Hashmap *newMap = new Hashmap(std::min(newSize(map), maxSize));
    for (int i = 0; i < map->size; i++)
    {
        String *currentValue = getRoot(map->array[i]);
        while (currentValue)
        {
            int count = getCount(map->array[i], currentValue);
            int hash = getHash(currentValue);
            hash %= newMap->size;
            addToMap(newMap, currentValue, count);
            remove(map->array[i], currentValue);
            currentValue = getRoot(map->array[i]);
        }
        removeTree(map->array[i]);
    }
    map = newMap;
}

int getMaxLength(Hashmap *map)
{
    int maxLength = -1;
    for (int i = 0; i < map->size; i++)
    {
        if (getSize(map->array[i]) > maxLength)
            maxLength = getSize(map->array[i]);
    }
    return maxLength;
}

double getAverageLengthOfChain(Hashmap *map)
{
    return map->averageLengthOfChain;
}

int getTotalNumberOfWords(Hashmap *map)
{
    return map->countElements;
}

int getNumberOfEmpty(Hashmap *map)
{
    return map->emptySpaces;
}

char *getMaxChain(Hashmap *map, int &count)
{
    count = getSize(map->array[map->maxChainIndex]);
    return getTreeInString(map->array[map->maxChainIndex]);
}

void updateMaxLengthOfChain(Hashmap *map, int hash)
{
    if (getSize(map->array[hash]) > getSize(map->array[map->maxChainIndex]))
        map->maxChainIndex = hash;
}

void updateAverageLengthOfChain(Hashmap *map, int hash)
{
    if (getSize(map->array[hash]) == 1)
        map->averageLengthOfChain = (map->averageLengthOfChain * (getOccupiedCount(map) - 1) + 1) / (getOccupiedCount(map));
    else
        map->averageLengthOfChain = map->averageLengthOfChain + 1.0 / getOccupiedCount(map);
}

bool addToMap(Hashmap *&map, String *string)
{
    int hash = getHash(string);
    hash %= map->size;
    if (getSize(map->array[hash]) == 0)
        map->emptySpaces--;
    if (addToBST(map->array[hash], string))
    {
        map->countElements++;
        updateAverageLengthOfChain(map, hash);
        updateMaxLengthOfChain(map, hash);
        if (getLoadFactor(map) > maxLoadFactor && map->size < maxSize)
            increaseMap(map);
        return true;
    }
    return false;
}

void addToMap(Hashmap *&map, String *string, int count)
{
    if (count > 0)
    {
        addToMap(map, string);
        int hash = getHash(string);
        hash %= map->size;
        addToBST(map->array[hash], string, count - 1);
    }
}

bool findInMap(Hashmap *map, String *string)
{
    unsigned long long hash = getHash(string);
    hash %= map->size;
    return isExist(map->array[hash], string);
}

void removeMap(Hashmap *map)
{
    for (int i = 0; i < map->size; i++)
    {
        removeTree(map->array[i]);
    }
    delete[] map->array;
    delete map;
}
