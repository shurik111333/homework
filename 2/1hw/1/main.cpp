#include <iostream>
#include "ListPointer.h"
#include "ListArray.h"
#include "IList.h"

using namespace std;

void printResult(bool result)
{
	if (result)
		cout << "OK";
	else
		cout << "FAIL";
	cout << endl;
}

void testRemoveFromEmptyList(IList<int> &list)
{
	cout << "Удаление элемента из пустого списка: ";
	printResult(!list.remove(0));
}

void testFindInEmptyList(IList<int> &list)
{
	cout << "Поиск в пустом списке: ";
	printResult(list.findElementId(0) == -1);
}

void testAddFindRemoveElements(IList<int> &list)
{
	cout << "Проверка добавления и поиска элементов: ";
	int test[] = {0, 3, 2, 7, 9, 1, 8};
	int count = sizeof(test) / sizeof(test[0]);
	for (int i = 0; i < count; i++)
	{
		list.insert(test[i], i);
	}
	bool result = true;
	for (int i = 0; i < count; i++)
	{
		result &= (list[i] == test[i]) && (list[list.findElementId(test[i])] == test[i]);
	}
	printResult(result);
	
	cout << "Проверка удаления элементов: ";
	result = true;
	result &= list.remove(test[0]);
	result &= (list.findElementId(test[1]) == 0);
	result &= list.remove(test[count - 1]);
	result &= list[count - 3] == test[count - 2];
	result &= list.remove(test[count / 2]);
	result &= (list.findElementId(test[1]) == 0) && (list[count - 4] == test[count - 2]);
	for (int i = 1; i < count - 1; i++)
	{
		if (i != count / 2)
			result &= list.remove(test[i]);
	}
	list.insert(1, 0);
	result &= list.findElementId(2) == -1;
	list.remove(1);
	printResult(result);
}

void testStart(IList<int> &list)
{
	testRemoveFromEmptyList(list);
	testFindInEmptyList(list);
	testAddFindRemoveElements(list);
}

int main()
{
	setlocale(LC_ALL, "rus");
	cout << "Тестирование ListPointer:" << endl;
	ListPointer list;
	testStart(list);
	
	ListArray listArray;
	cout << "Тестирование ListArray:" << endl;
	testStart(listArray);
	return 0;
}

