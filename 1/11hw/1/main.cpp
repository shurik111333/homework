#include <iostream>
#include <cstring>
#include <cctype>

using namespace std;

const int maxLen = 256;
const bool isFinishState[] = {false, false, true, false, true, false, false, true};
const char point = '.', exp = 'E';

enum State
{
    startState,
    numberSignState,
    integerState,
    pointState,
    decimalState,
    exponentSymbolState,
    exponentSignState,
    exponentState
};

bool isSign(char c)
{
    return (c == '+' || c == '-');
}

bool isCorrect(char number[])
{
    int len = strlen(number);
    State state = startState;
    for (int i = 0; i < len; i++)
    {
        char c = number[i];
        switch (state)
        {
        case startState:
        {
            if (isSign(c))
            {
                state = numberSignState;
                break;
            }
            if (isdigit(c))
            {
                state = integerState;
                break;
            }
            return false;
        }
        case numberSignState:
        {
            if (isdigit(c))
                state = integerState;
            else
                return false;
            break;
        }
        case integerState:
        {
            if (isdigit(c))
                break;
            if (c == point)
            {
                state = pointState;
                break;
            }
            if (c == exp)
            {
                state = exponentSymbolState;
                break;
            }
            return false;
        }
        case pointState:
        {
            if (isdigit(c))
                state = decimalState;
            else
                return false;
            break;
        }
        case decimalState:
        {
            if (isdigit(c))
                break;
            if (c == exp)
            {
                state = exponentSymbolState;
                break;
            }
            return false;
        }
        case exponentSymbolState:
        {
            if (isSign(c))
            {
                state = exponentSignState;
                break;
            }
            if (isdigit(c))
            {
                state = exponentState;
                break;
            }
            return false;
        }
        case exponentSignState:
        {
            if (isdigit(c))
                state = exponentState;
            else
                return false;
            break;
        }
        case exponentState:
        {
            if (!isdigit(c))
                return false;
            break;
        }
        }
    }
    return isFinishState[state];
}

int main()
{
    setlocale(LC_ALL, "rus");
    cout << "¬ведите число с плавающей точкой" << endl;
    char input[maxLen] = {};
    cin >> input;
    cout << "¬веденное число ";
    if (!isCorrect(input))
    {
        cout << "не";
    }
    cout << "корректно" << endl;
    return 0;
}

