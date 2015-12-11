#include <iostream>

using namespace std;

int main()
{
    setlocale(LC_ALL, "rus");
    cout << "¬ведите номер числа фиббоначи" << endl;
    int n = 0;
    cin >> n;
    cout << n << "-е число фиббоначи: ";
    if (n < 3)
    {
        cout << 1 << endl;
        return 0;
    }
    int num1 = 1;
    int num2 = 1;
    int num3 = num1 + num2;
    for (int i = 4; i <= n; i++)
    {
        int tmp = num3 + num2;
        num1 = num2;
        num2 = num3;
        num3 = tmp;
    }
    cout << num3 << endl;
    return 0;
}

