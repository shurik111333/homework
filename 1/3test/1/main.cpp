#include <iostream>
#include <cstring>

using namespace std;

const int maxLen = 256;

int main()
{
	setlocale(LC_ALL, "rus");
	cout << "Введите довичную запись целого числа" << endl;
	char number[maxLen] = {};
	cin >> number;
	int len = strlen(number);
	int *powerOfTwo = new int[len];
	powerOfTwo[0] = 1;
	for (int i = 1; i < len; i++)
	{
		powerOfTwo[i] = powerOfTwo[i - 1] * 2;
	}
	int result = 0;
	for (int i = len - 1; i >= 0; i--)
	{
		if (number[i] == '1')
			result += powerOfTwo[len - i - 1];
	}
	delete[] powerOfTwo;
	cout << "Десятичная запись числа: " << result << endl;
	return 0;
}

