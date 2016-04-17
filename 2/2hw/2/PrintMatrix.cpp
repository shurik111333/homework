#include <cmath>
#include "PrintMatrix.h"

double PrintMatrix::pi = acos(-1);
int PrintMatrix::currentLine = 0;
int PrintMatrix::currentRow = 0;
int PrintMatrix::step = 0;
double PrintMatrix::angle = 0;
int **PrintMatrix::inputArray = nullptr;
int PrintMatrix::PrintMatrix::n = 0;
IPrint *PrintMatrix::PrintMatrix::printer = nullptr;

void PrintMatrix::print(int **inputArray, int n, IPrint *printer)
{
	init(inputArray, n, printer);
	start();
}

void PrintMatrix::init(int **array, int n, IPrint *printer)
{
	currentLine = n / 2;
	currentRow = n / 2;
	step = 1;
	angle = pi;
	inputArray = array;
	PrintMatrix::n = n;
	PrintMatrix::printer = printer;
}

void PrintMatrix::start()
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

void PrintMatrix::goToNextTurn()
{
	for (int i = 0; i < step; i++)
	{
		currentLine += (int)cos(angle);
		currentRow += (int)sin(angle);
		printer->print(inputArray[currentLine][currentRow]);
	}
}

void PrintMatrix::writeCurrentStep()
{
	goToNextTurn();
	angle -= pi / 2;
	goToNextTurn();
	angle -= pi / 2;
}
