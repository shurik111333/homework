#include <iostream>
#include <cstring>

using namespace std;

const int maxLen = 256;

int main()
{
	setlocale(LC_ALL, "rus");
	cout << "Введите двоичную запись целого положительного числа" << endl;
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
	cout << "Десятичная запись числа: " << result << endl;
	return 0;
}

