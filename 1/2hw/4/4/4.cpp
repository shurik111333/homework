// 4.cpp: определ€ет точку входа дл€ консольного приложени€.
//

#include <iostream>

using namespace std;

int gcd(int a, int b)
{
	if (b == 0)
	{
		return a;
	}
	else
	{
		return gcd(b, a % b);
	}
}

int main()
{
	setlocale(LC_ALL, "rus");
	cout << "ѕрограмма выводит все несократимые дроби в промежутке (0, 1) со знаменателем, не превосход€щим n" << endl;
	cout << "¬ведите n" << endl;
	int maxDenominator  = 0;
	cin >> maxDenominator ;
	int currentGcd = 1;
	for (int numerator = 1; numerator < maxDenominator / 2; numerator++)
	{
		currentGcd = gcd(numerator, maxDenominator);
		cout << numerator / currentGcd << "/" << maxDenominator / currentGcd << endl;
		int denominator = maxDenominator - 1;
		while ((double)numerator / denominator < (double)(numerator + 1) / maxDenominator)
		{
			currentGcd = gcd(numerator, denominator);
			cout << numerator / currentGcd << "/" << denominator / currentGcd << endl;
			denominator--;
		}
	}
	currentGcd = gcd(maxDenominator / 2, maxDenominator);
	cout << (maxDenominator / 2) / currentGcd << "/" << maxDenominator / currentGcd << endl;
	for (int numerator = maxDenominator / 2 - 1 + maxDenominator % 2; numerator > 0; numerator--)
	{
		currentGcd = 1;
		int denominator = numerator + 1;
		while ((double)numerator / denominator >= (double)(numerator + 1) / maxDenominator)
		{
			denominator++;
		}
		while ((double)numerator / denominator > (double)numerator / maxDenominator)
		{
			int currentNumerator = denominator - numerator;
			currentGcd = gcd(currentNumerator, denominator);
			cout << currentNumerator / currentGcd << "/" << denominator / currentGcd << endl;
			denominator++;
		}
		currentGcd = gcd(maxDenominator - numerator, maxDenominator);
		cout << (maxDenominator - numerator) / currentGcd << "/" << maxDenominator / currentGcd << endl;
	}
	system("pause");
	return 0;
}