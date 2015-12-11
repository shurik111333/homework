// 3.cpp: определяет точку входа для консольного приложения.
//

#include <iostream>

using namespace std;

void reverseSegmentOfArray(int l, int r, int arr[])
{
	if (r <= l)
	{
		return;
	}
	for (int i = l; i <= (l + r) / 2; i++)
	{
		swap(arr[i], arr[r - i + l]);
	}
}

int main()
{
	setlocale(LC_ALL, "rus");
	cout << "Программа меняет местами первые n символов с последними m символами" << endl;
	cout << "Введите n и m" << endl;
	int n = 0;
	int m = 0;
	cin >> n >> m;
	cout << "Введите массив из " << n + m << " элементов" << endl;
	int *arr = new int[n + m];
	for (int i = 0; i < n + m; i++)
	{
		cin >> arr[i];
	}
	reverseSegmentOfArray(0, n - 1, arr);
	reverseSegmentOfArray(n, n + m - 1, arr);
	reverseSegmentOfArray(0, n + m - 1, arr);
	cout << "Результат: ";
	for (int i = 0; i < n + m; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
	return 0;
}

