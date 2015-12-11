#include <iostream>

using namespace std;

struct BSTNode
{
    int value;
    int height;
    BSTNode *left;
    BSTNode *right;

    BSTNode(int value)
    {
        this->value = value;
        height = 1;
        left = nullptr;
        right = nullptr;
    }
};

struct BST
{
    BSTNode *root;
};

enum Action
{
    nothing,
    addAction,
    removeAction
};

enum PrintTreeType
{
    defaultOrder,
    ascendingOrder,
    descendingOrder
};

BST *getNewBST()
{
    return new BST{nullptr};
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

bool find(BSTNode *&node, int value, Action action);

void removeNode(BSTNode *&node)
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
    find(node->right, (*tmp)->value, removeAction);
}

void addNode(BSTNode *&node, int value)
{
    if (node != nullptr)
        return;
    node = new BSTNode(value);
}

void doAction(BSTNode *&node, int value, Action action)
{
    switch (action)
    {
    case addAction:
    {
        addNode(node, value);
        break;
    }
    case removeAction:
    {
        removeNode(node);
        break;
    }
    default:
    {
        return;
    }
    }
}

bool find(BSTNode *&node, int value, Action action = nothing)
{
    bool result = false;
    if (node == nullptr || node->value == value)
    {
        result = node;
        doAction(node, value, action);
    }
    else
    {
        if (node->value > value)
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

bool remove(BST *tree, int value)
{
    return find(tree->root, value, removeAction);
}

bool add(BST *tree, int value)
{
    return !find(tree->root, value, addAction);
}

bool isExist(BST *tree, int value)
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

void printTreeInDescendingOrder(BSTNode *node)
{
    if (node == nullptr)
    {
        return;
    }
    printTreeInDescendingOrder(node->right);
    cout << node->value << " ";
    printTreeInDescendingOrder(node->left);
}

void printTree(BSTNode *node)
{
    if (node == nullptr)
    {
        cout << "null ";
        return;
    }
    cout << "( " << node->value << " ";
    printTree(node->left);
    printTree(node->right);
    cout << ") ";

}

void printTree(BST *tree, int modifier)
{
    switch ((PrintTreeType)modifier)
    {
    case defaultOrder:
    {
        printTree(tree->root);
        break;
    }
    case ascendingOrder:
    {
        printTreeInAscendingOrder(tree->root);
        break;
    }
    case descendingOrder:
        printTreeInDescendingOrder(tree->root);
        break;
    }
    cout << endl;
}

void removeTree(BST *tree)
{
    while (tree->root)
    {
        find(tree->root, tree->root->value, removeAction);
    }
    delete tree;
}
