#include <cstring>
#include <cctype>
#include "lexer.h"

//private----------------------------------------//

enum State
{
    startState,
    integerState,
    pointState,
    decimalState,
    exponentSymbolState,
    exponentSignState,
    exponentState
};

bool isSpace(const char symbol)
{
    return (symbol == ' ' || symbol == '\t' || symbol == '\n');
}

void Lexer::skipSpaces()
{
    while (isSpace(this->string[index]))
    {
        index++;
    }
}

bool Lexer::isSign(const char symbol)
{
    return (symbol =='+' || symbol == '-' || symbol == '*' || symbol == '/');
}

const bool isFinishState[] = {false, true, false, true, false, false, true};
const char point = '.', exp = 'E';

bool Lexer::isNumber()
{
    bool isInNumber = true;
    int newIndex = index - 1;
    State state = startState;
    while (isInNumber)
    {
        char c = this->string[++newIndex];
        switch (state)
        {
        case startState:
        {
            if (isdigit(c))
            {
                state = integerState;
                break;
            }
            isInNumber = false;
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
            isInNumber = false;
            break;
        }
        case pointState:
        {
            if (isdigit(c))
                state = decimalState;
            else
                isInNumber = false;
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
            isInNumber = false;
            break;
        }
        case exponentSymbolState:
        {
            if (c == '+' || c == '-')
            {
                state = exponentSignState;
                break;
            }
            if (isdigit(c))
            {
                state = exponentState;
                break;
            }
            isInNumber = false;
            break;
        }
        case exponentSignState:
        {
            if (isdigit(c))
                state = exponentState;
            else
                isInNumber = false;
            break;
        }
        case exponentState:
        {
            if (!isdigit(c))
                isInNumber = false;
            break;
        }
        }
    }
    if (isFinishState[state])
        index = newIndex;
    return isFinishState[state];
}

//public-----------------------------------------//

Lexer::Lexer()
    :length(0), index(0), string(nullptr)
{}

Lexer::Lexer(const char *string)
{
    length = strlen(string);
    this->string = new char[length + 1];
    strcpy(this->string, string);
    this->string[length] = '\0';
    index = 0;
}

Lexer::~Lexer()
{
    delete[] string;
}

Lexer::Token Lexer::next()
{
    skipSpaces();
    if (index >= length)
        return empty;
    if (isNumber())
        return Lexer::number;
    if (isSign(this->string[index++]))
        return (Token)this->string[index - 1];
    else
        return Lexer::error;
}

Lexer::Token Lexer::lookAhead()
{
    int oldIndex = index;
    Token result = this->next();
    index = oldIndex;
    return result;
}

bool Lexer::isSign(Token token)
{
    return (token == plus || token == minus || token == multiply || token == divide);
}
