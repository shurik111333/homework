#include <iostream>
#include <cstring>

using namespace std;

const int maxLen = 256;

int main()
{
	setlocale(LC_ALL, "rus");
	cout << "������� �������� ������ ������ �������������� �����" << endl;
	char number[maxLen] = {};
	cin >> number;
	int len = strlen(number);
	int result = 0;
	int currentPower = 1;
	for (int i = len - 1; i >= 0; i--)
	{
		result += (number[i] - '0') * currentPower;
		currentPower <<= 1;
	}
	cout << "���������� ������ �����: " << result << endl;
	return 0;
}

