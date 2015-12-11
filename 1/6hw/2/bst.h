#pragma once

struct BST;

BST *getNewBST(FILE *fileToRead);

int calculateTree(BST *tree);

void writeTree(BST *tree);

void removeTree(BST *tree);
