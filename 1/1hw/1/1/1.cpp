// 1.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include <iostream>

using namespace std;

int main()
{
	setlocale(LC_ALL, "rus");
	cout << "��������� ������� �������� ��������� \"x^4 + x^3 + x^2 + x + 1\"\n";
	cout << "������� ����� x\n";
	int x = 0;
	cin >> x;
	int x2 = x * x;
	int result = (x2 + 1) * (x2 + x) + 1;
	cout << "�����: " << result << endl;
	return 0;
}