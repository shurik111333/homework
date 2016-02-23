#include <iostream>
#include <cmath>
#include "IPrint.h"
#include "PrintConsole.h"
#include "PrintFile.h"

using namespace std;

/**
 * @brief Static class for print array NxN in a spiral.
 * Spiral split on the corners with equal sides,
 * then each corner split on two sides, which is easy to print
 */
class PrintMatrix
{
public:
	/**
	 * @brief Print array in a spiral with IPrint interface
	 * @param inputArray
	 * @param n
	 * @param printer
	 */
	static void print(int **inputArray, int n, IPrint *printer)
	{
		init(inputArray, n, printer);
		start();
	}
	
private:

	static double pi;
	static int currentLine;
	static int currentRow;
	static double angle;
	static int step;
	static int n;
	static int **inputArray;
	static IPrint *printer;
	
	static void init(int **array, int n, IPrint *printer)
	{
		currentLine = n / 2;
		currentRow = n / 2;
		step = 1;
		angle = pi;
		inputArray = array;
		PrintMatrix::n = n;
		PrintMatrix::printer = printer;
	}
	
	static void start()
	{
		printer->print(inputArray[currentLine][currentRow]);
		while (currentRow > 0)
		{
			writeCurrentStep();
			step++;
		}
		for (int i = n - 2; i >= 0; i--)
		{
			printer->print(inputArray[i][0]);
		}
	}
	
	/**
	 * @brief Print side of the corner
	 */
	static void goToNextTurn()
	{
		for (int i = 0; i < step; i++)
		{
			currentLine += (int)cos(angle);
			currentRow += (int)sin(angle);
			printer->print(inputArray[currentLine][currentRow]);
		}
	}
	
	/**
	 * @brief Print current corner with equal sides in spiral
	 */
	static void writeCurrentStep()
	{
		goToNextTurn();
		angle -= pi / 2;
		goToNextTurn();
		angle -= pi / 2;
	}
	
	
};

double PrintMatrix::pi = acos(-1);
int PrintMatrix::currentLine = 0;
int PrintMatrix::currentRow = 0;
int PrintMatrix::step = 0;
double PrintMatrix::angle = 0;
int **PrintMatrix::inputArray = nullptr;
int PrintMatrix::PrintMatrix::n = 0;
IPrint *PrintMatrix::PrintMatrix::printer = nullptr;

const int maxLen = 256;

IPrint *getPrintMethod()
{
	int type = 0;
	while (type != 1 && type != 2)
	{
		cout << "Выберите способ вывода:" << endl;
		cout << "1 - вывод в консоль" << endl;
		cout << "2 - вывод в файл" << endl;
		cin >> type;
	}
	if (type == 1)
		return new PrintConsole();
	cout << "Введите имя файла" << endl;
	char fileName[maxLen] = {};
	cin >> fileName;
	return new PrintFile(fileName);
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
	IPrint *printer = getPrintMethod();
	PrintMatrix::print(inputArray, n, printer);
	delete printer;
	for (int i = 0; i < n; i++)
	{
		delete[] inputArray[i];
	}
	delete[] inputArray;
	cout << endl;
	return 0;
}