#include <iostream>
#include <cstring>

using namespace std;

struct BSTNode
{
    int value;
    bool isOperation;
    BSTNode *left;
    BSTNode *right;

    BSTNode(int value, bool isOperation)
    {
        this->value = value;
        this->isOperation = isOperation;
        left = nullptr;
        right = nullptr;
    }
};

struct BST
{
    BSTNode *root = nullptr;
};

BST *getNewBST()
{
    return new BST;
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

int getNumber(FILE *file)
{
    int result = 0;
    char c = getc(file);
    while (isdigit(c))
    {
        result = result * 10 + c - '0';
        c = getc(file);
    }
    ungetc(c, file);
    return result;
}

BSTNode *getNodeFromFile(FILE *file)
{
    skipSpaces(file);
    BSTNode *newNode = nullptr;
    char c = getc(file);
    if (c == '(')
    {
        skipSpaces(file);
        newNode = new BSTNode(getc(file), true);
        skipSpaces(file);
        newNode->left = getNodeFromFile(file);
        skipSpaces(file);
        newNode->right = getNodeFromFile(file);
        skipSpaces(file);
        getc(file);
    }
    else
    {
        ungetc(c, file);
        skipSpaces(file);
        newNode = new BSTNode(getNumber(file), false);
    }
    return newNode;
}

BST *getNewBST(FILE *fileToRead)
{
    BST *tree = getNewBST();
    tree->root = getNodeFromFile(fileToRead);
    return tree;
}

void writeTree(BSTNode *node)
{
    if (node == nullptr)
    {
        return;
    }
    if (!node->isOperation)
    {
        cout << node->value;
        return;
    }
    cout << "(";
    writeTree(node->left);
    cout << " " << (char)node->value << " ";
    writeTree(node->right);
    cout << ")";

}

void writeTree(BST *tree)
{
    writeTree(tree->root);
    cout << endl;
}

int calculate(int number1, int number2, char operation)
{
    switch(operation)
    {
    case '+':
    {
        return number1 + number2;
    }
    case '-':
    {
        return number1 - number2;
    }
    case '*':
    {
        return number1 * number2;
    }
    case '/':
    {
        return number1 / number2;
    }
    default:
    {
        return 0;
    }
    }
}

int calculateNode(BSTNode *node)
{
    if (node->isOperation)
        return calculate(calculateNode(node->left), calculateNode(node->right), (char)node->value);
    else
        return node->value;
}

int calculateTree(BST *tree)
{
    return calculateNode(tree->root);
}

void removeNode(BSTNode *&node)
{
    if (node == nullptr)
        return;
    if (!node->isOperation)
    {
        delete node;
        node = nullptr;
        return;
    }
    removeNode(node->left);
    removeNode(node->right);
    delete node;
    node = nullptr;
}

void removeTree(BST *tree)
{
    removeNode(tree->root);
    delete tree;
}
