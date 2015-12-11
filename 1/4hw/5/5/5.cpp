// 5.cpp: определяет точку входа для консольного приложения.
//

#include <iostream>
#include "list.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "rus");
	cout << "Программа \"Считалочка\". По кругу стоят N человек. Начиная с первого человека, из круга выходит каждый K-й." << endl;
	cout << "По заданным N и K, программа вернет номер человека, который останется последним" << endl;
	cout << "Введите N и K" << endl;
	int numberOfSoldiers = 0;
	int numberOfDelete = 0;
	cin >> numberOfSoldiers >> numberOfDelete;
	List *soldiers = getNewList();
	for (int i = numberOfSoldiers; i > 0; i--)
	{
		addNode(soldiers, i);
	}
	setCurrentElementAtFirst(soldiers);
	for (int i = 1; i < numberOfSoldiers; i++)
	{
		for (int j = 1; j < numberOfDelete; j++)
		{
			goToNext(soldiers);
		}
		deleteNode(soldiers, getCurrentElement(soldiers));
	}
	cout << "Ответ: " << getCurrentElement(soldiers) << endl;
	deleteList(soldiers);
	return 0;
}