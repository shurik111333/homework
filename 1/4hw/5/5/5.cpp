// 5.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include <iostream>
#include "list.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "rus");
	cout << "��������� \"����������\". �� ����� ����� N �������. ������� � ������� ��������, �� ����� ������� ������ K-�." << endl;
	cout << "�� �������� N � K, ��������� ������ ����� ��������, ������� ��������� ���������" << endl;
	cout << "������� N � K" << endl;
	int numberOfSoldiers = 0;
	int numberOfDelete = 0;
	cin >> numberOfSoldiers >> numberOfDelete;
	List *soldiers = getNewList();
	for (int i = numberOfSoldiers; i > 0; i--)
	{
		addNode(soldiers, i);
	}
	setCurrentElementAtFirst(soldiers);
	for (int i = 1; i < numberOfSoldiers; i++)
	{
		for (int j = 1; j < numberOfDelete; j++)
		{
			goToNext(soldiers);
		}
		deleteNode(soldiers, getCurrentElement(soldiers));
	}
	cout << "�����: " << getCurrentElement(soldiers) << endl;
	deleteList(soldiers);
	return 0;
}