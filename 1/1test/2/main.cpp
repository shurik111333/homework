#include <iostream>
#include <cstdio>
#include <cstring>
#include "stack.h"

using namespace std;

const int maxLen = 255;

bool isOpenBracket(char bracket)
{
    return (bracket == '(' || bracket == '[' || bracket == '{');
}

bool isCloseBracket(char bracket)
{
    return (bracket == ')' || bracket == ']' || bracket == '}');
}

bool isEqualTypeOfBrackets(char bracket1, char bracket2)
{
    if (bracket1 == bracket2)
    {
        return true;
    }
    if (isCloseBracket(bracket1))
    {
        swap(bracket1, bracket2);
    }
    switch (bracket1)
    {
        case '(':
        {
            return (bracket2 == ')');
        }
        case '[':
        {
            return (bracket2 == ']');
        }
        case '{':
        {
            return (bracket2 == '}');
        }
        default:
        {
            return false;
        }
    }
}

bool isCorrectText(char *inputText)
{
    Stack *brackets = getNewStack();
    int textLength = strlen(inputText);
    for (int i = 0; i < textLength; i++)
    {
        if (isOpenBracket(inputText[i]))
        {
            push(brackets, inputText[i]);
            continue;
        }
        if (isCloseBracket(inputText[i]))
        {
            if (!isEmpty(brackets))
            {
                if (isEqualTypeOfBrackets(getTop(brackets), inputText[i]))
                {
                    pop(brackets);
                }
                else
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
        }
    }
    bool isCorrectText = isEmpty(brackets);
    deleteStack(brackets);
    return isCorrectText;
}

int main()
{
    setlocale(LC_ALL, "rus");
    cout << "¬ведите текст" << endl;
    char inputText[maxLen] = {};
    fgets(inputText, maxLen, stdin);
    cout << "¬веденный текст ";
    if (isCorrectText(inputText))
    {
        cout << "корректен";
    }
    else
    {
        cout << "не корректен";
    }
    cout << endl;
    return 0;
}

