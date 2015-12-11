// 6.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

const int sequenceLength = 4;
const int minDigit = 0;
const int maxDigit = 9;
const int radix = 10;

int *getRandomSequence()
{
	int *resultSequence = new int[sequenceLength];
	bool isUsed[maxDigit + 1] = {};
	srand((unsigned int)time(0));
	for (int i = 0; i < sequenceLength; i++)
	{
		int numberSteps = rand() % (maxDigit + 1);
		int currentDigit = 1;
		while (isUsed[currentDigit])
		{
			currentDigit++;
		}
		while (numberSteps > 0 || isUsed[currentDigit])
		{
			if (!isUsed[currentDigit])
			{
				numberSteps--;
			}
			currentDigit++;
			if (currentDigit > maxDigit)
			{
				currentDigit = 1;
			}
		}
		resultSequence[i] = currentDigit;
		isUsed[currentDigit] = true;
	}
	return resultSequence;
}

int main()
{
	setlocale(LC_ALL, "rus");
	cout << "���� \"���� � ������\"" << endl;
	int *secretNumber = getRandomSequence();
	cout << "����� ��������!" << endl;
	//cout << secretNumber[0] << secretNumber[1] << secretNumber[2] << secretNumber[3] << endl;
	bool isUsed[maxDigit + 1] = {};
	int indexOfDigit[maxDigit + 1] = {};
	for (int i = 0; i < sequenceLength; i++)
	{
		isUsed[secretNumber[i]] = true;
		indexOfDigit[secretNumber[i]] = i + 1;
	}
	int attempt = 0;
	while (true)
	{
		attempt++;
		cout << "������� " << attempt << endl;
		int currentNumber = 0;
		cin >> currentNumber;
		int cows = 0;
		int bulls = 0;
		for (int i = sequenceLength; i > 0; i--)
		{
			int currenDigit = currentNumber % radix;
			currentNumber /= radix;
			if (isUsed[currenDigit])
			{
				if (indexOfDigit[currenDigit] == i)
				{
					bulls++;
				}
				else
				{
					cows++;
				}
			}
		}
		if (bulls == sequenceLength)
		{
			cout << "�� ������� �����!" << endl;
			break;
		}
		cout << "�����: " << cows << ", �����: " << bulls << endl;
	}
	delete[] secretNumber;
	return 0;
}

