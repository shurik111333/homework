#pragma once

struct List;

List *getNewList();

void addNode(List *list, int value);

void deleteNode(List *list, int value);

void deleteList(List *list);

void setCurrentElementAtFirst(List *list);

int getCurrentElement(List *list);

void goToNext(List *list);