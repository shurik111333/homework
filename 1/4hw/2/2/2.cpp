// 2.cpp: определяет точку входа для консольного приложения.
//

#include <iostream>
#include <cmath>

using namespace std;

const double pi = acos(-1);

void goToNextTurn(int &currentLine, int &currentRow, double &angle, int step, int **inputArray)
{
	for (int i = 0; i < step; i++)
	{
		currentLine += (int)cos(angle);
		currentRow += (int)sin(angle);
		cout << inputArray[currentLine][currentRow] << " ";
	}
}

void writeCurrentStep(int &currentLine, int &currentRow, double &angle, int step, int **inputArray)
{
	goToNextTurn(currentLine, currentRow, angle, step, inputArray);
	angle -= pi / 2;
	goToNextTurn(currentLine, currentRow, angle, step, inputArray);
	angle -= pi / 2;
}

int main()
{
	setlocale(LC_ALL, "rus");
	cout << "Программа выводит элементы массива NxN в порядке обхода по спирали" << endl;
	cout << "Введите нечетное числа N - размер массива" << endl;
	int n = 0;
	cin >> n;
	cout << "Введите массив" << endl;
	int **inputArray = new int*[n];
	for (int i = 0; i < n; i++)
	{
		inputArray[i] = new int[n];
		for (int j = 0; j < n; j++)
		{
			cin >> inputArray[i][j];
		}
	}
	int currentLine = n / 2;
	int currentRow = n / 2;
	int currentStep = 1;
	double currentAngle = pi;
	cout << inputArray[currentLine][currentRow] << " ";
	while (currentRow > 0)
	{
		writeCurrentStep(currentLine, currentRow, currentAngle, currentStep, inputArray);
		currentStep++;
	}
	for (int i = n - 2; i >= 0; i--)
	{
		cout << inputArray[i][0] << " ";
	}
	for (int i = 0; i < n; i++)
	{
		delete[] inputArray[i];
	}
	delete[] inputArray;
	cout << endl;
	return 0;
}