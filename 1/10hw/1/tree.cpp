#include <limits.h>
#include <iostream>
#include <cstring>
#include "tree.h"

struct TreeNode
{
    char value;
    bool isLetter;
    int height;
    int code;
    TreeNode *left;
    TreeNode *right;

    TreeNode(char value = '\0', bool isLetter = false)
        :value(value), isLetter(isLetter), height(1), code(0), left(nullptr), right(nullptr)
    {}
};

struct Tree
{
    int priority;
    TreeNode *root;
};

Tree *getNewTree(char value, int priority)
{
    return new Tree{priority, new TreeNode(value, true)};
}

int getPriority(const Tree *tree)
{
    return tree == nullptr ? 0 : tree->priority;
}

int max(int a, int b)
{
    return a > b ? a : b;
}

Tree *merge(Tree *treeLeft, Tree *treeRight)
{
    Tree *tree = new Tree{treeLeft->priority + treeRight->priority, new TreeNode('\0', false)};
    tree->root->left = treeLeft->root;
    tree->root->right = treeRight->root;
    tree->root->right->code = 1;
    tree->root->height = max(tree->root->left->height, tree->root->right->height) + 1;
    delete treeLeft;
    delete treeRight;
    return tree;
}

void getCodes(TreeNode *node, char **codes, char *currentCode, int length)
{
    currentCode[length++] = node->code + '0';
    if (node->isLetter)
    {
        currentCode[length] = '\0';
        codes[node->value - CHAR_MIN] = new char[length + 1];
        strcpy(codes[node->value - CHAR_MIN], currentCode);
        return;
    }
    getCodes(node->left, codes, currentCode, length);
    getCodes(node->right, codes, currentCode, length);
}

char **getCodes(Tree *tree)
{
    char **codes = new char*[CHAR_MAX - CHAR_MIN + 1];
    for (int i = 0; i < CHAR_MAX - CHAR_MIN + 1; i++)
    {
        codes[i] = nullptr;
    }
    char *currentCode = new char[tree->root->height];
    int length = 0;
    getCodes(tree->root->left, codes, currentCode, length);
    getCodes(tree->root->right, codes, currentCode, length);
    delete[] currentCode;
    return codes;
}

void writeValue(char value, std::ostream &out)
{
    out << '\"';
    if (value == '\n')
        out << "\\n";
    else
        out << value;
    out << "\" ";
}

void writeTree(TreeNode *node, std::ostream &out)
{
    if (node == nullptr)
    {
        return;
    }
    out << node->code << " ";
    if (node->isLetter)
    {
        writeValue(node->value, out);
        return;
    }
    out << '(';
    writeTree(node->left, out);
    writeTree(node->right, out);
    out << ')';

}

void writeTree(Tree *tree, std::ostream &out)
{
    writeTree(tree->root, out);
}

bool isSpace(char symbol)
{
    return (symbol == ' ' || symbol == '\t' || symbol == '\n');
}

void skipSpaces(FILE *file)
{
    char c = getc(file);
    while (!feof(file) && isSpace(c))
    {
        c = getc(file);
    }
    ungetc(c, file);
}

int height(TreeNode *node)
{
    return node == nullptr ? 0 : node->height;
}

char getValue(FILE *file)
{
    char c = getc(file);
    if (c != '\\')
        return c;
    char next = getc(file);
    if (next == '"')
    {
        ungetc(next, file);
        return c;
    }
    return '\n';
}

TreeNode *getNode(FILE *file)
{
    TreeNode *node = new TreeNode();
    skipSpaces(file);
    char c = getc(file);
    node->code = c - '0';
    skipSpaces(file);
    c = getc(file);
    if (c == '(')
    {
        node->left = getNode(file);
        node->right = getNode(file);
        node->height = max(height(node->right), height(node->left));
        skipSpaces(file);
        getc(file);
    }
    else
    {
        node->isLetter = true;
        node->value = getValue(file);
        node->left = nullptr;
        node->right = nullptr;
        getc(file);
    }
    return node;
}

Tree *getTree(FILE *file)
{
    return new Tree{0, getNode(file)};
}

void decode(Tree *tree, FILE *file, std::ostream &out)
{
    char c = getc(file);
    TreeNode *currentNode = tree->root;
    while (c == '0' || c == '1')
    {
        if (c == '0')
            currentNode = currentNode->left;
        else
            currentNode = currentNode->right;
        if (currentNode->isLetter)
        {
            out << currentNode->value;
            currentNode = tree->root;
        }
        c = getc(file);
    }
    ungetc(c, file);
}

void deleteTree(TreeNode *node)
{
    if (node->left)
        deleteTree(node->left);
    if (node->right)
        deleteTree(node->right);
    delete node;
}

void deleteTree(Tree *tree)
{
    deleteTree(tree->root);
    delete tree;
}
