// 4.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include <iostream>
#include "sortedList.h"

using namespace std;

void doAddValue(List *list)
{
	int value = 0;
	cin >> value;
	addValue(list, value);
	cout << "�������� ���� ������� ���������" << endl;
}

void doDeleteValue(List *list)
{
	int value = 0;
	cin >> value;
	if (deleteValue(list, value) == 0)
	{
		cout << "�������� ���� ������� �������" << endl;
	}
	else
	{
		cout << "�������� �� ���� ������� � ������" << endl;
	}
}

void doPrintList(List *list)
{
	int length = 0;
	int *elementsOfList = getArray(list, length);
	if (length == 0)
	{
		cout << "������ ����";
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
	cout << "������� �������" << endl;
	int command = 0;
	cin >> command;
	return command;
}

int main()
{
	setlocale(LC_ALL, "rus");
	cout << "��������� ��������� �������� � ������ � ������������� �������" << endl;
	cout << "�������:\n0 - �����\n1 <value> - �������� ��������\n2 <value> - ������� ��������\n3 - ������� ������" << endl;
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

