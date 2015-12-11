// 3.cpp: определяет точку входа для консольного приложения.
//

#include <fstream>

using namespace std;

int main()
{
	ifstream fin("partition.in");
	ofstream fout("partition.out");
	//setlocale(LC_ALL, "rus");
	//cout << "Программа выводит разложение числа n на слагаемые" << endl;
	//cout << "Введите n" << endl;
	int n = 0;
	fin >> n;
	int *currentPartition = new int[n + 1];
	for (int i = 0; i < n; i++)
	{
		currentPartition[i] = 1;
		fout << 1 << " ";
		//printf("%d ", 1);
	}
	fout << "\n";
	//printf("\n");
	int indexOfChangingElement = 0;
	int currentLength = n;
	while (currentPartition[0] < n)
	{
		while (indexOfChangingElement > 0 && currentPartition[indexOfChangingElement] == currentPartition[indexOfChangingElement - 1])
		{
			indexOfChangingElement--;
		}
		int currSum = 0;
		for (int i = 0; i < indexOfChangingElement; i++)
		{
			currSum += currentPartition[i];
			fout << currentPartition[i] << " ";
			//printf("%d ", currentPartition[i]);
		}
		fout << ++currentPartition[indexOfChangingElement] << " ";
		currentLength = indexOfChangingElement + 1 + n - currSum - currentPartition[indexOfChangingElement];
		for (int i = indexOfChangingElement + 1; i < currentLength; i++)
		{
			currentPartition[i] = 1;
			fout << 1 << " ";
			//printf("%d ", 1);
		}
		indexOfChangingElement++;
		if (indexOfChangingElement > currentLength - 2)
		{
			indexOfChangingElement = currentLength - 2;
		}
		fout << "\n";
		//printf("\n");
	}
	delete[] currentPartition;
	return 0;
}
