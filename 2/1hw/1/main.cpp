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
	cout << "Length: " << list.length() << endl;
}

void testRemoveFromEmptyList(IList<int> &list)
{
	cout << "Removing from empty list: ";
	printResult(!list.remove(0));
}

void testFindInEmptyList(IList<int> &list)
{
	cout << "Searching in empty list: ";
	printResult(list.findElementId(0) == -1);
}

void testAddFindRemoveElements(IList<int> &list)
{
	int test[] = {0, 3, 2, 7, 9, 1, 8};
	cout << "Checking add and search elements with array: {" << test[0];
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
	cout << "All elements was added: ";
	printList(list);
	
	bool result = true;
	for (int i = 0; i < count; i++)
	{
		result &= (list[i] == test[i]) && (list[list.findElementId(test[i])] == test[i]);
	}
	cout << "Checking searching element by index and value: ";
	printResult(result);
	cout << "Searching and removing nonexistent element: ";
	printResult((list.findElementId(15) == -1) && !list.remove(15));
	cout << "Removing first element: ";
	printResult(list.remove(list[0]));
	printList(list);
	cout << "Removing element from the middle of list: ";
	printResult(list.remove(list[list.length() / 2]));
	printList(list);
	cout << "Removing last element: ";
	printResult(list.remove(list[list.length() - 1]));
	printList(list);
	cout << "Removing all elements: ";
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
	cout << "Testing ListPointer:" << endl;
	ListPointer list;
	testStart(list);
	cout << endl;
	ListArray listArray;
	cout << "Testing ListArray:" << endl;
	testStart(listArray);
	return 0;
}

