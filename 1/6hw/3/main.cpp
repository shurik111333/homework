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
        cout << "Значение успешно добавлено" << endl;
    }
    else
    {
        cout << "Значение уже присутствует в множестве" << endl;
    }
}

void doRemove(BST *tree)
{
    if (remove(tree, getValue()))
    {
        cout << "Значение успешно удалено" << endl;
    }
    else
    {
        cout << "Значение отсутствует в множестве" << endl;
    }
}

void doSearch(BST *tree)
{
    if (isExist(tree, getValue()))
    {
        cout << "Значение присутствует в множестве" << endl;
    }
    else
    {
        cout << "Значение отсутствует в множестве" << endl;
    }
}

void doPrintTree(BST *tree)
{
    cout << "Введите:" << endl;
    cout << "0 - вывести дерево в прядке обхода" << endl;
    cout << "1 - вывести элементы по возрастанию" << endl;
    cout << "2 - вывести элементы по убыванию" << endl;
    int modifier = 0;
    cin >> modifier;
    printTree(tree, modifier);
}

void printCommands()
{
    cout << "0 - выход" << endl;
    cout << "1 <int_value> - добавить значение" << endl;
    cout << "2 <int_value> - удалить значение" << endl;
    cout << "3 <int_value> - проверка принадлежности значения множеству" << endl;
    cout << "4 - вывод дерева" << endl;
}

int getCommand()
{
    int command = -1;
    while(command == -1)
    {
        cout << "Введите команду или -1 для вывода списка комманд" << endl;
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
    cout << "АТД \"Множество\" на основе АВЛ-дерева. Доступные команды:" << endl;
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
