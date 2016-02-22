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

void printList(IList<int> &list)
{
	for (int i = 0; i < list.length(); i++)
	{
		cout << list[i] << " ";
	}
	cout << endl;
	cout << "����� ������: " << list.length() << endl;
}

void testRemoveFromEmptyList(IList<int> &list)
{
	cout << "�������� �������� �� ������� ������: ";
	printResult(!list.remove(0));
}

void testFindInEmptyList(IList<int> &list)
{
	cout << "����� � ������ ������: ";
	printResult(list.findElementId(0) == -1);
}

void testAddFindRemoveElements(IList<int> &list)
{
	int test[] = {0, 3, 2, 7, 9, 1, 8};
	cout << "�������� ���������� � ������ ��������� �� �������: {" << test[0];
	int count = sizeof(test) / sizeof(test[0]);
	for (int i = 1; i < count; i++)
	{
		cout << ", " << test[i];
	}
	cout << "}" << endl;
	for (int i = 0; i < count; i++)
	{
		list.insert(test[i], i);
	}
	cout << "��� �������� ���������: ";
	printList(list);
	
	bool result = true;
	for (int i = 0; i < count; i++)
	{
		result &= (list[i] == test[i]) && (list[list.findElementId(test[i])] == test[i]);
	}
	cout << "�������� ������ �������� �� ������� ��� ��������: ";
	printResult(result);
	cout << "����� � �������� ��������������� ��������: ";
	printResult((list.findElementId(15) == -1) && !list.remove(15));
	cout << "�������� ������� ��������: ";
	printResult(list.remove(list[0]));
	printList(list);
	cout << "�������� �������� �� �������� ������: ";
	printResult(list.remove(list[list.length() / 2]));
	printList(list);
	cout << "�������� ���������� ��������: ";
	printResult(list.remove(list[list.length() - 1]));
	printList(list);
	cout << "�������� ���� ���������: ";
	result = true;
	while (list.length() > 0)
		result &= list.remove(list[0]);
	printResult(result);
	printList(list);
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
	cout << "������������ ListPointer:" << endl;
	ListPointer list;
	testStart(list);
	cout << endl;
	ListArray listArray;
	cout << "������������ ListArray:" << endl;
	testStart(listArray);
	return 0;
}

