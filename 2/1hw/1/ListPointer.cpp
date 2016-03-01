#include "ListPointer.h"
#include <limits.h>

ListPointer::ListPointer()
{
	count = 0;
	tail = new ListElement(INT_MAX, nullptr, nullptr);
	head = new ListElement(INT_MAX, nullptr, tail);
	tail->setPrev(head);
}

ListPointer::~ListPointer()
{
	while (head != nullptr)
	{
		ListElement *next = head->getNext();
		delete head;
		head = next;
	}
}

void ListPointer::insert(int value, int index)
{
	ListElement *node = getElementById(index);
	ListElement *newNode = new ListElement(value, node->getPrev(), node);
	node->getPrev()->setNext(newNode);
	node->setPrev(newNode);
	count++;
}

bool ListPointer::isTail(ListElement *element) const
{
	return element->getNext() == nullptr;
}

bool ListPointer::remove(int value)
{
	ListElement *current = head;
	while (!isTail(current->getNext()) && current->getNext()->getValue() != value)
	{
		current = current->getNext();
	}
	if (!isTail(current->getNext()))
	{
		ListElement *node = current->getNext();
		current->setNext(node->getNext());
		delete node;
		count--;
		return true;
	}
	return false;
}

int ListPointer::findElementId(int value) const
{
	ListElement *current = head->getNext();
	int index = 0;
	while (!isTail(current) && current->getValue() != value)
	{
		index++;
		current = current->getNext();
	}
	return !isTail(current) ? index : -1;
}

int ListPointer::operator [](const int index) const
{
	return getElementById(index)->getValue();
}

ListPointer::ListElement *ListPointer::getElementById(int index) const
{
	ListElement *current = head->getNext();
	for (int i = 0; !isTail(current) && i < index; i++)
	{
		current = current->getNext();
	}
	return current;
}

int ListPointer::length() const
{
	return count;
}

//ListPointer::ListElement-------------------------------------------------------

ListPointer::ListElement::ListElement(int value, ListElement *prev, ListElement *next)
{
	this->value = value;
	this->next = next;
	this->prev = prev;
}

ListPointer::ListElement *ListPointer::ListElement::getNext() const
{
	return next;
}

void ListPointer::ListElement::setNext(ListElement *next)
{
	this->next = next;
}

ListPointer::ListElement *ListPointer::ListElement::getPrev() const
{
	return prev;
}

void ListPointer::ListElement::setPrev(ListElement *prev)
{
	this->prev = prev;
}

int ListPointer::ListElement::getValue() const
{
	return value;
}