#include <iostream>
#include "bst.h"

using namespace std;

int getValue()
{
    int value = 0;
    cin >> value;
    return value;
}

void doAdd(BST *tree)
{
    if (add(tree, getValue()))
    {
        cout << "�������� ������� ���������" << endl;
    }
    else
    {
        cout << "�������� ��� ������������ � ���������" << endl;
    }
}

void doRemove(BST *tree)
{
    if (remove(tree, getValue()))
    {
        cout << "�������� ������� �������" << endl;
    }
    else
    {
        cout << "�������� ����������� � ���������" << endl;
    }
}

void doSearch(BST *tree)
{
    if (isExist(tree, getValue()))
    {
        cout << "�������� ������������ � ���������" << endl;
    }
    else
    {
        cout << "�������� ����������� � ���������" << endl;
    }
}

void doPrintTree(BST *tree)
{
    cout << "�������:" << endl;
    cout << "0 - ������� ������ � ������ ������" << endl;
    cout << "1 - ������� �������� �� �����������" << endl;
    cout << "2 - ������� �������� �� ��������" << endl;
    int modifier = 0;
    cin >> modifier;
    printTree(tree, modifier);
}

void printCommands()
{
    cout << "0 - �����" << endl;
    cout << "1 <int_value> - �������� ��������" << endl;
    cout << "2 <int_value> - ������� ��������" << endl;
    cout << "3 <int_value> - �������� �������������� �������� ���������" << endl;
    cout << "4 - ����� ������" << endl;
}

int getCommand()
{
    int command = -1;
    while(command == -1)
    {
        cout << "������� ������� ��� -1 ��� ������ ������ �������" << endl;
        cin >> command;
        if (command == -1)
        {
            printCommands();
        }
    }
    return command;
}

int main()
{
    setlocale(LC_ALL, "rus");
    cout << "��� \"���������\" �� ������ ���-������. ��������� �������:" << endl;
    printCommands();
    BST *tree = getNewBST();
    for (int i = 1; i <= 10; i++)
    {
        add(tree, i);
    }
    bool isExit = false;
    while (!isExit)
    {
        int command = getCommand();
        switch (command)
        {
        case 0:
        {
            isExit = true;
            break;
        }
        case 1:
        {
            doAdd(tree);
            break;
        }
        case 2:
        {
            doRemove(tree);
            break;
        }
        case 3:
        {
            doSearch(tree);
            break;
        }
        case 4:
        {
            doPrintTree(tree);
            break;
        }
        }
    }
    removeTree(tree);
    return 0;
}
