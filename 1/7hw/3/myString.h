#pragma once

#include <ostream>

struct String
{
private:
    void skipEqual(const String &str1, const String &str2, int &index) const;

    char *initValue(const char *string);

public:
    const int length;
    const char *const value;

    String(const String *string);

    String(const char *newString);

    String(const char *newString, int length);

    ~String();

    bool operator ==(const String &string) const;

    bool operator !=(const String &string) const;

    bool operator <(const String &string) const;

    bool operator >(const String &string) const;

    friend std::ostream &operator <<(std::ostream &out, const String &string);
};

int length(const String *string);

int getHash(const String *string);

char getChar(String *string, int index);

String *clone(const String *string);

String *concat(String *string, const String *stringToConcat);

bool isEmpty(const String *string);

String *substring(const String *string, int start, int length);

char *stringToChar(const String *string);
