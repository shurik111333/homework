#pragma once

struct BST;

BST *getNewBST();

bool add(BST *tree, int value);

bool isExist(BST *tree, int value);

bool remove(BST *tree, int value);

bool printTree(BST *tree, int modifier);

void removeTree(BST *tree);
