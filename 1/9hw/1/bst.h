#pragma once

#include "myString.h"

struct BST;

BST *getNewBST();

BST **getNewBSTArray(int count);

String *getRoot(BST *tree);

int getSize(BST *tree);

int getCount(BST *tree, String *value);

bool addToBST(BST *tree, String *value);

void addToBST(BST *tree, String *value, int count);

bool isExist(BST *tree, String *value);

bool remove(BST *tree, String *value);

char *getTreeInString(BST *tree);

void removeTree(BST *tree);
