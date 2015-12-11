struct ListNode
{
	int value;
	ListNode *next;
};

struct List
{
	ListNode *first;
	ListNode *last;
	ListNode *currentNode;
	int length;
};

List *getNewList()
{
	List *newList = new List{ nullptr, nullptr, nullptr, 0 };
	return newList;
}

bool isEmpty(List *list)
{
	return (list->length == 0);
}

void addNode(List *list, int value)
{
	ListNode *newNode = new ListNode{ value, nullptr };
	if (isEmpty(list))
	{
		list->first = newNode;
		list->last = newNode;
		newNode->next = newNode;
	}
	else
	{
		newNode->next = list->first;
		list->first = newNode;
		list->last->next = newNode;
	}
	list->length++;
}

void setCurrentElementAtFirst(List *list)
{
	list->currentNode = list->first;
}

int getCurrentElement(List *list)
{
	if (list->currentNode == nullptr)
		return -1;
	return list->currentNode->value;
}

void goToNext(List *list)
{
	if (list->currentNode != nullptr)
	{
		list->currentNode = list->currentNode->next;
	}
}

void deleteNode(List *list, int value)
{
	if (list->first == nullptr)
		return;
	ListNode *currentNode = list->first->next;
	ListNode *previousNode = list->first;
	while (currentNode->value != value && currentNode->next != list->first->next)
	{
		previousNode = currentNode;
		currentNode = currentNode->next;
	}
	if (currentNode->value == value)
	{
		if (currentNode == previousNode)
		{
			delete currentNode;
			list->first = nullptr;
			list->last = nullptr;
			list->currentNode = nullptr;
			list->length = 0;
			return;
		}
		if (currentNode == list->first)
		{
			list->first = currentNode->next;
		}
		if (currentNode == list->last)
		{
			list->last = previousNode;
		}
		if (list->currentNode == currentNode)
		{
			list->currentNode = currentNode->next;
		}
		previousNode->next = currentNode->next;
		delete currentNode;
		list->length--;
	}
}

void deleteList(List *list)
{
	ListNode *currentNode = nullptr;
	while (list->first != nullptr)
	{
		currentNode = list->first->next;
		deleteNode(list, currentNode->value);
	}
	delete list->first;
	delete list->last;
	delete list;
}