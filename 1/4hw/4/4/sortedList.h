#pragma once

struct List;

List *getNewList();

void addValue(List *list, int value);

int deleteValue(List *list, int value);

int *getArray(List *list, int &length);

void deleteList(List *list);