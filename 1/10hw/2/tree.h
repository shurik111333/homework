#pragma once

#include <ostream>

struct Tree;

Tree *getNewTree(char value, int priority);

int getPriority(const Tree *tree);

Tree *merge(Tree *treeLeft, Tree *treeRight);

char **getCodes(Tree *tree);

void writeTree(Tree *tree, std::ostream &out);

Tree *getTree(FILE *file);

void decode(Tree *tree, FILE *file, std::ostream &out);

void deleteTree(Tree *tree);
