#include <iostream>
#include <cstring>

using namespace std;

const int maxLen = 256;
const int p = 53;
const int module = 1000000000 + 7;

long long power(int a, int b)
{
    if (b == 0)
        return 1;
    if ((b & 1) == 0)
    {
        long long tmp = power(a, b / 2) % module;
        return tmp * tmp % module;
    }
    else
        return (a * power(a, b - 1)) % module;
}

long long *getHashSubstrings(char *string)
{
    int length = strlen(string);
    long long *hash = new long long[length];
    hash[0] = (unsigned char)string[0];
    for (int i = 1; i < length; i++)
    {
        hash[i] = ((hash[i - 1] * p) % module + (unsigned char)string[i]) % module;
    }
    return hash;
}

int getHash(char *string)
{
    int length = strlen(string);
    long long hash = (unsigned char)string[0];
    for (int i = 1; i < length; i++)
    {
        hash = ((hash * p) % module + (unsigned char)string[i]) % module;
    }
    return (int)hash;
}

int getHash(long long *hash, int l, int r)
{
    return l == 0 ? hash[r] : (hash[r] - (hash[l - 1] * power(p, r - l + 1) % module) + module) % module;
}

bool isEqualSubstring(char *str1, int start, char *str2)
{
    int length1 = strlen(str1);
    int length2 = strlen(str2);
    if (length1 - start + 1 < length2)
        return false;
    int index = 0;
    while (index < length2 && str1[index + start] == str2[index])
    {
        index++;
    }
    return index == length2;
}

int main()
{
    setlocale(LC_ALL, "rus");
    cout << "Программа ищет образец в строке алгоритмом Рабина-Карпа" << endl;
    cout << "Введите исходную строку" << endl;
    char string[maxLen] = {};
    cin >> string;
    cout << "Введите образец" << endl;
    char example[maxLen] = {};
    cin >> example;
    long long *hash = getHashSubstrings(string);
    int hashExample = getHash(example);
    int exampleLength = strlen(example);
    int stringLength = strlen(string);
    for (int i = 0; i <= stringLength - exampleLength + 1; i++)
    {
        if (getHash(hash, i, i + exampleLength - 1) == hashExample && isEqualSubstring(string, i, example))
        {
            cout << "Вхождение образца в строку в позиции " << i + 1 << endl;
        }
    }
    delete[] hash;
    return 0;
}

