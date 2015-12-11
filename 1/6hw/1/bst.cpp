#include <iostream>

using namespace std;

struct BSTNode
{
    int value;
    BSTNode *left;
    BSTNode *right;
};

struct BST
{
    BSTNode *root = nullptr;
};

BST *getNewBST()
{
    return new BST;
}

BSTNode **find(BSTNode *&node, int value)
{
    if (node == nullptr || node->value == value)
    {
        return &node;
    }
    if (node->value > value)
    {
        return find(node->left, value);
    }
    else
    {
        return find(node->right, value);
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

void deleteNode(BSTNode *&node)
{
    if (!(node->left || node->right))
    {
        delete node;
        node = nullptr;
        return;
    }
    if (node->left == nullptr)
    {
        BSTNode *tmp = node->right;
        delete node;
        node = tmp;
        return;
    }
    if (node->right == nullptr)
    {
        BSTNode *tmp = node->left;
        delete node;
        node = tmp;
        return;
    }
    BSTNode **tmp = getNextNode(node);
    node->value = (*tmp)->value;
    deleteNode(*tmp);
}

bool remove(BST *tree, int value)
{
    BSTNode **node = find(tree->root, value);
    if (!(*node))
    {
        return false;
    }
    deleteNode(*node);
    return true;
}

bool add(BST *tree, int value)
{
    BSTNode **node = find(tree->root, value);
    if (*node)
    {
        return false;
    }
    *node = new BSTNode{value, nullptr, nullptr};
    return true;
}

bool isExist(BST *tree, int value)
{
    return ((*find(tree->root, value)) != nullptr);
}

void writeTreeInAscendingOrder(BSTNode *node)
{
    if (node == nullptr)
    {
        return;
    }
    writeTreeInAscendingOrder(node->left);
    cout << node->value << " ";
    writeTreeInAscendingOrder(node->right);
}

void writeTreeInDescendingOrder(BSTNode *node)
{
    if (node == nullptr)
    {
        return;
    }
    writeTreeInDescendingOrder(node->right);
    cout << node->value << " ";
    writeTreeInDescendingOrder(node->left);
}

void writeTree(BSTNode *node)
{
    if (node == nullptr)
    {
        cout << "null ";
        return;
    }
    cout << "( " << node->value << " ";
    writeTree(node->left);
    writeTree(node->right);
    cout << ") ";

}

void writeTree(BST *tree, int modifier)
{
    switch (modifier)
    {
    case 0:
    {
        writeTree(tree->root);
        break;
    }
    case 1:
    {
        writeTreeInAscendingOrder(tree->root);
        break;
    }
    case -1:
        writeTreeInDescendingOrder(tree->root);
        break;
    }
    cout << endl;
}

void removeTree(BST *tree)
{
    while (tree->root)
    {
        deleteNode(tree->root);
    }
    delete tree;
}
