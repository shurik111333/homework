#include <iostream>
#include "myString.h"
#include "bst.h"

using namespace std;

struct BSTNode
{
    String *value;
    int height;
    int count;
    BSTNode *left;
    BSTNode *right;

    BSTNode(String *value)
    {
        this->value = value;
        height = 1;
        count = 1;
        left = nullptr;
        right = nullptr;
    }
};

struct BST
{
    int size = 0;
    int totalLength = 0;
    BSTNode *root = nullptr;
};

enum Action
{
    addAction,
    removeNodeAction,
    removeAllAction,
    getCountAction,
    findAction
};

BST *getNewBST()
{
    return new BST;
}

BST **getNewBSTArray(int count)
{
   BST **result = new BST*[count];
   for (int i = 0; i < count; i++)
   {
       result[i] = getNewBST();
   }
   return result;
}

String *getRoot(BST *tree)
{
    return tree->root ? tree->root->value : nullptr;
}

int getHeight(BSTNode *node)
{
    return node ? node->height : 0;
}

int max(int a, int b)
{
    return a > b ? a : b;
}

void updateHeight(BSTNode *node)
{
    if (node == nullptr)
        return;
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
}
int getBalance(BSTNode *node)
{
    return getHeight(node->left) - getHeight(node->right);
}

void leftRotation(BSTNode *&node)
{
    BSTNode *oldRight = node->right;
    node->right = oldRight->left;
    oldRight->left = node;
    node = oldRight;
    updateHeight(node->left);
    updateHeight(node);
}

void rightRotation(BSTNode *&node)
{
    BSTNode *oldLeft = node->left;
    node->left = oldLeft->right;
    oldLeft->right = node;
    node = oldLeft;
    updateHeight(node->right);
    updateHeight(node);
}

void balance(BSTNode *&node)
{
    if (node == nullptr)
        return;

    updateHeight(node);
    if (getBalance(node) == 2)
    {
        if (getBalance(node->left) < 0)
        {
            leftRotation(node->left);
        }
        rightRotation(node);
    }
    if (getBalance(node) == -2)
     {
         if (getBalance(node->right) > 0)
         {
             rightRotation(node->right);
         }
         leftRotation(node);
     }
}

BSTNode **getMin(BSTNode *&node)
{
    return (node->left == nullptr) ? &node : getMin(node->left);
}

BSTNode **getNextNode(BSTNode *&node)
{
    return getMin(node->right);
}

int find(BSTNode *&node, String *value, Action action);

bool removeNode(BSTNode *&node, bool isDeleteValue = true)
{
    if (node == nullptr)
        return false;

    if (isDeleteValue)
        delete node->value;
    if (!(node->left || node->right))
    {
        delete node;
        node = nullptr;
        return true;
    }
    if (node->left == nullptr)
    {
        BSTNode *tmp = node->right;
        delete node;
        node = tmp;
        return true;
    }
    if (node->right == nullptr)
    {
        BSTNode *tmp = node->left;
        delete node;
        node = tmp;
        return true;
    }
    BSTNode **tmp = getNextNode(node);
    node->value = (*tmp)->value;
    node->count = (*tmp)->count;
    find(node->right, (*tmp)->value, removeNodeAction);
    return true;
}

int addNode(BSTNode *&node, String *value)
{
    if (node != nullptr)
        node->count++;
    else
        node = new BSTNode(value);
    return node->count - 1;
}

int getCount(BSTNode *node)
{
    return node == nullptr ? 0 : node->count;
}

int doAction(BSTNode *&node, String *value, Action action)
{
    switch (action)
    {
    case addAction:
    {
        return addNode(node, value);
    }
    case removeNodeAction:
    {
        return removeNode(node, false);
    }
    case removeAllAction:
    {
        return removeNode(node);
    }
    case getCountAction:
    {
        return getCount(node);
    }
    case findAction:
    {
        return (int)node;
    }
    default:
    {
        return -1;
    }
    }
}

int find(BSTNode *&node, String *value, Action action = findAction)
{
    int result = 0;
    if (node == nullptr || *(node->value) == *value)
    {
        result = doAction(node, value, action);
    }
    else
    {
        if (*(node->value) > *value)
        {
            result = find(node->left, value, action);
        }
        else
        {
            result = find(node->right, value, action);
        }
    }
    balance(node);
    return result;
}

int getSize(BST *tree)
{
    return tree ? tree->size : 0;
}

int getCount(BST *tree, String *value)
{
    return find(tree->root, value, getCountAction);
}

bool remove(BST *tree, String *value)
{
    if (find(tree->root, value, removeNodeAction))
    {
        tree->size--;
        return true;
    }
    return false;
}

bool addToBST(BST *tree, String *value)
{
    if (!find(tree->root, value, addAction))
    {
        tree->size++;
        tree->totalLength += length(value);
        return true;
    }
    return false;
}

void setCount(BSTNode *node, int count)
{
    node->count = count;
}

void addToBST(BST *tree, String *value, int count)
{
    if (count > 0)
    {
        addToBST(tree, value);
        BSTNode *node = (BSTNode*)find(tree->root, value);
        setCount(node, node->count + count - 1);
    }
}

bool isExist(BST *tree, String *value)
{
    return find(tree->root, value);
}

void printTreeInAscendingOrder(BSTNode *node)
{
    if (node == nullptr)
    {
        return;
    }
    printTreeInAscendingOrder(node->left);
    cout << node->value << " ";
    printTreeInAscendingOrder(node->right);
}

void getTreeInString(BSTNode *node, char *string, int &index)
{
    if (node == nullptr)
        return;

    getTreeInString(node->left, string, index);
    for (int i = 0; i < length(node->value); i++)
    {
        string[index] = getChar(node->value, i);
        index++;
    }
    string[index++] = '\n';
    getTreeInString(node->right, string, index);
}

char *getTreeInString(BST *tree)
{
    char *result = new char[tree->totalLength + tree->size + 1];
    int index = 0;
    getTreeInString(tree->root, result, index);
    result[index] = '\0';
    return result;
}

void removeTree(BST *tree)
{
    while (tree->root)
    {
        find(tree->root, tree->root->value, removeAllAction);
    }
    delete tree;
}
