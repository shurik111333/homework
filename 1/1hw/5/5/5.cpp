// 5.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include <iostream>
#include <string.h>

using namespace std;

int main()
{
	setlocale(LC_ALL, "rus");
	cout << "��������� ��������� ������������ ��������� ������������������ � ������" << endl;
	cout << "������� ������" << endl;
	char *inputString = new char[];
	scanf("%s", inputString);
	int balance = 0;
	for (int i = 0; i < strlen(inputString); i++)
	{
		if (inputString[i] == '(')
		{
			balance++;
		}
		if (inputString[i] == ')')
		{
			balance--;
		}
		if (balance < 0)
		{
			break;
		}
	}
	cout << "��������� ������������������ �������� ";
	if (balance != 0)
	{
		cout << "��";
	}
	cout << "����������" << endl;
	return 0;
}