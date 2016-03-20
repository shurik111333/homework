#pragma once

#include "IPrint.h"

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
	static void print(int **inputArray, int n, IPrint *printer);

private:

	static double pi;
	static int currentLine;
	static int currentRow;
	static double angle;
	static int step;
	static int n;
	static int **inputArray;
	static IPrint *printer;

	static void init(int **array, int n, IPrint *printer);

	static void start();

	/**
	 * @brief Print side of the corner
	 */
	static void goToNextTurn();

	/**
	 * @brief Print current corner with equal sides in spiral
	 */
	static void writeCurrentStep();
};
