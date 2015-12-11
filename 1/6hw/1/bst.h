#pragma once

struct BST;

BST *getNewBST();

bool add(BST *tree, int value);

bool isExist(BST *tree, int value);

bool remove(BST *tree, int value);

void removeTree(BST *tree);

void writeTree(BST *tree, int modifier);
