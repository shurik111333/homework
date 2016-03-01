#pragma once

#include "IList.h"

class ListPointer : public IList<int>
{
public:
	ListPointer();
	~ListPointer();
	
	void insert(int value, int index);
	bool remove(int value);
	int findElementId(int value) const;
	int operator [](const int index) const;
	int length() const;
	
private:
	class ListElement
	{
	public:
		ListElement(int value, ListElement *prev, ListElement *next);
		
		int getValue() const;
		void setNext(ListElement *next);
		ListElement *getNext() const;
		void setPrev(ListElement *prev);
		ListElement *getPrev() const;
		
	private:
		int value;
		ListElement *next;
		ListElement *prev;
	};
	
	ListElement *getElementById(int index) const;
	bool isTail(ListElement *element) const;
	
	int count;
	ListElement *head;
	ListElement *tail;
};