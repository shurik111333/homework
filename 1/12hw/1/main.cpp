#include <iostream>
#include <cstdio>
#include "lexer.h"

using namespace std;

const int maxLen = 256;

/*
  E -> +T | -T | T
  T -> idF
  F -> +T | -T | *T | /T | e
*/

bool T(Lexer &lexer);

bool F(Lexer &lexer)
{
    Lexer::Token nextToken = lexer.lookAhead();
    if (nextToken == Lexer::empty)
        return true;
    if (Lexer::isSign(nextToken))
    {
        lexer.next();
        return T(lexer);
    }
    else
        return false;
}

bool T(Lexer &lexer)
{
    if (lexer.lookAhead() == Lexer::number)
    {
        lexer.next();
        return F(lexer);
    }
    else
        return false;
}

bool E(Lexer &lexer)
{
    Lexer::Token nextToken = lexer.lookAhead();
    if (nextToken == Lexer::plus || nextToken == Lexer::minus)
    {
        lexer.next();
        return T(lexer);
    }
    if (nextToken == Lexer::number)
        return T(lexer);
    return false;
}

bool isExit(char string[])
{
    return (string[0] == 'Q' && string[1] == '\n');
}

int main()
{
    setlocale(LC_ALL, "rus");
    cout << "Программа проверяет корректность арифметического выражения" << endl;
    while (true)
    {
        cout << "Введите выражение или \"Q\" для выхода" << endl;
        char expression[maxLen] = {};
        fgets(expression, maxLen - 1, stdin);
        if (isExit(expression))
            break;
        Lexer lexer(expression);
        cout << "Выражение является ";
        if (!E(lexer))
            cout << "не";
        cout << "корректным" << endl;
    }
    return 0;
}

