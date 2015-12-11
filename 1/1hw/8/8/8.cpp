// 8.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include <iostream>

using namespace std;

long factorialRecursive(int n)
{
	if (n == 0)
		return 1;
	else
		return n * factorialRecursive(n - 1);
}

long factorialIterate(int n)
{
	int result = 1;
	for (int i = 2; i <= n; i++)
	{
		result *= i;
	}
	return result;
}

int main()
{
	setlocale(LC_ALL, "rus");
	cout << "��������� ������� ��������� ����� n" << endl;
	cout << "������� ����� n" << endl;
	int n = 0;
	cin >> n;
	cout << "����������� �������: " << factorialRecursive(n) << endl;
	cout << "����������� �������: " << factorialIterate(n) << endl;
	return 0;
}

