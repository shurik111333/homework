// 4.cpp: определяет точку входа для консольного приложения.
//

#include <iostream>
#include "sortedList.h"

using namespace std;

void doAddValue(List *list)
{
	int value = 0;
	cin >> value;
	addValue(list, value);
	cout << "Значение было успешно добавлено" << endl;
}

void doDeleteValue(List *list)
{
	int value = 0;
	cin >> value;
	if (deleteValue(list, value) == 0)
	{
		cout << "Значение было успешно удалено" << endl;
	}
	else
	{
		cout << "Значение не было найдено в списке" << endl;
	}
}

void doPrintList(List *list)
{
	int length = 0;
	int *elementsOfList = getArray(list, length);
	if (length == 0)
	{
		cout << "Список пуст";
	}
	else
	{
		for (int i = 0; i < length; i++)
		{
			cout << elementsOfList[i] << " ";
		}
	}
	delete[] elementsOfList;
	cout << endl;
}

int getCommand()
{
	cout << "Введите команду" << endl;
	int command = 0;
	cin >> command;
	return command;
}

int main()
{
	setlocale(LC_ALL, "rus");
	cout << "Программа реализует создание и работу с сортированным списком" << endl;
	cout << "Команды:\n0 - выход\n1 <value> - добавить значение\n2 <value> - удалить значение\n3 - вывести список" << endl;
	List *list = getNewList();
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
				doAddValue(list);
				break;
			}
			case 2:
			{
				doDeleteValue(list);
				break;
			}
			case 3:
			{
				doPrintList(list);
				break;
			}
		}
	}
	deleteList(list);
	return 0;
}

