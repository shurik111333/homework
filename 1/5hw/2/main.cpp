#include <iostream>
#include <iomanip>

using namespace std;

const int maxBitCount = 64;
const int lenExponent = 11;
const int lenMantissa = maxBitCount - lenExponent - 1;
const int accuracy = 16;

int main()
{
    setlocale(LC_ALL, "rus");
    cout << "¬ведите число с плавающей точкой" << endl;
    double inputNumber = 0;
    cin >> inputNumber;
    long double mantissa = 0;
    long long order = 0;
    unsigned long long *pointerToDouble = (unsigned long long *)&inputNumber;
    unsigned long long orderPower = 1;
    long long mantissPower = 1;
    char sign = '+';
    for (int i = 1; i <= lenMantissa; i++)
    {
        mantissPower <<= 1;
    }
    for (int i = 0; i < maxBitCount; i++)
    {
        if (i < lenMantissa && (*pointerToDouble & 1) == 1)
        {
            mantissa += 1.0 / mantissPower;
        }
        if (i < lenMantissa + lenExponent && i >= lenMantissa)
        {
            if ((*pointerToDouble & 1) == 1)
                order |= orderPower;
            orderPower <<= 1;
        }
        if (i == maxBitCount - 1 && (*pointerToDouble & 1) == 1)
        {
            sign = '-';
        }
        *pointerToDouble >>= 1;
        mantissPower >>= 1;
    }
    cout << sign << setprecision(accuracy) << mantissa + 1 << "*2^(" << order - (1 << (lenExponent - 1)) + 1 << ')' << endl;
    return 0;
}

