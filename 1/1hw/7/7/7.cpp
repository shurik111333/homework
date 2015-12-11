// 7.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include <iostream>

using namespace std;

void createEratosthene(int n, bool isComposite[])
{
	for (int i = 0; i <= n; i++)
	{
		isComposite[i] = false;
	}
	for (int i = 2; i <= n; i++)
	{
		if (!isComposite[i])
		{
			int j = i * 2;
			while (j <= n)
			{
				isComposite[j] = true;
				j += i;
			}
		}
	}
}

int main()
{
	setlocale(LC_ALL, "rus");
	cout << "��������� ������� ��� ������� �����, �� ����������� ��������� ����� n" << endl;
	cout << "������� ����� n" << endl;
	int n = 0;
	cin >> n;
	bool *isComposite = new bool[n + 1];
	createEratosthene(n, isComposite);
	for (int i = 2; i <= n; i++)
	{
		if (!isComposite[i])
		{
			cout << i << endl;
		}
	}
	return 0;
}