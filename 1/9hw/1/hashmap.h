#pragma once

#include "myString.h"

struct Hashmap;

Hashmap *getNewHashmap();

Hashmap *getNewHashmap(int size);

bool addToMap(Hashmap *&map, String *string);

bool findInMap(Hashmap *map, String *string);

int getMaxLength(Hashmap *map);

int getMapSize(Hashmap *map);

char *getMaxChain(Hashmap *map, int &count);

double getLoadFactor(Hashmap *map);

int getNumberOfEmpty(Hashmap *map);

double getAverageLengthOfChain(Hashmap *map);

int getTotalNumberOfWords(Hashmap *map);

void removeMap(Hashmap *map);
