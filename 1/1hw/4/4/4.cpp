// 4.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include <iostream>


int main()
{
	setlocale(LC_ALL, "rus");
	int countSum[28] = {};
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			for (int k = 0; k < 10; k++)
			{
				countSum[i + j + k]++;
			}
		}
	}
	int result = 0;
	for (int i = 0; i < 28; i++)
	{
		result += countSum[i] * countSum[i];
	}
	std :: cout << "���������� ���������� ������� ����� 6 ����� " << result << "\n";
	return 0;
}