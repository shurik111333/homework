#include <iostream>
#include "SortedSet.h"
#include "ListArray.h"

using namespace std;

/**
 * @brief Create list and fill it numbers [0..size - 1].
 * @param size
 * @return Return pointer on created list.
 */
ListArray *getList(int size)
{
	ListArray *list = new ListArray(size);
	for (int i = 0; i < size; i++)
	{
		list->insert(i, i);
	}
	return list;
}

int main()
{
	SortedSet set;
	ListArray *list3 = getList(3);
	set.add(list3);
	ListArray *list8 = getList(8);
	set.add(list8);
	ListArray *list5 = getList(5);
	set.add(list5);
	ListArray *list2 = getList(2);
	set.add(list2);
	cout << "Min: " << set.min()->getCount() << endl;
	cout << "Max: " << set.max()->getCount() << endl;
	cout << "Set contains list5: " << (set.contains(list5) ? "true" : "false") << endl;
	set.remove(list2);
	cout << "Remove min. Current min: " << set.min()->getCount() << endl;
	set.remove(list8);
	cout << "Remove max. Current max: " << set.max()->getCount() << endl;
	cout << "Clear set." << endl;
	set.clear();
	cout << "Set is empty: " << (set.empty() ? "true" : "false") << endl;
	return 0;
}

