#pragma once

class Lexer
{
public:

    enum Token
    {
        empty,
        number,
        plus = '+',
        minus = '-',
        multiply = '*',
        divide = '/',
        error
    };

    Lexer();

    Lexer(const char *string);

    ~Lexer();

    Token next();

    Token lookAhead();

    static bool isSign(Token token);

private:

    int length;
    int index;
    char *string;

    static bool isSign(const char symbol);

    void skipSpaces();

    bool isNumber();

};
