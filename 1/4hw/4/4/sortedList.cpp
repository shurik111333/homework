#include <limits.h>

struct ListNode
{
	int value;
	ListNode *next;
};

struct List
{
	ListNode *first;
	int length;
};

List *getNewList()
{
	ListNode *first = new ListNode{ INT_MIN, nullptr };
	ListNode *last = new ListNode{ INT_MAX, nullptr };
	first->next = last;
	List *newList = new List{ first, 0 };
	return newList;
}

void addValue(List *list, int value)
{
	ListNode *newNode = new ListNode{ value, nullptr };
	ListNode *currentNode = list->first;
	while (currentNode->next->value < newNode->value)
	{
		currentNode = currentNode->next;
	}
	newNode->next = currentNode->next;
	currentNode->next = newNode;
	list->length++;
}

int deleteValue(List *list, int value)
{
	ListNode *currentNode = list->first;
	while (currentNode->next != nullptr && currentNode->next->value != value)
	{
		currentNode = currentNode->next;
	}
	if (currentNode->next != nullptr)
	{
		ListNode *nodeForDelete = currentNode->next;
		currentNode->next = nodeForDelete->next;
		delete nodeForDelete;
		list->length--;
		return 0;
	}
	return -1;
}

int getLength(List *list)
{
	return list->length;
}

int *getArray(List *list, int &length)
{
	length = getLength(list);
	int *elements = new int[length];
	ListNode *currentNode = list->first->next;
	for (int i = 0; i < length; i++)
	{
		elements[i] = currentNode->value;
		currentNode = currentNode->next;
	}
	return elements;
}

void deleteList(List *list)
{
	ListNode *currentNode = list->first->next;
	while (currentNode->next != nullptr)
	{
		deleteValue(list, currentNode->value);
		currentNode = list->first->next;
	}
	delete list->first->next;
	delete list->first;
	delete list;
}