#include "myString.h"
#include <cstring>

int min(int a, int b);

char *String::initValue(const char *string)
{
    char *value = new char[length + 1];
    for (int i = 0; i < length; i++)
    {
        value[i] = string[i];
    }
    value[length] = '\0';
    return value;
}

String::String(const String *string)
    :length(string->length), value(initValue(string->value))
{}

String::String(const char *newString)
    :length(std::strlen(newString)), value(initValue(newString))
{}

String::String (const char *newString, int length)
    :length(length), value(initValue(newString))
{}

String::~String()
{
    delete[] this->value;
}

void String::skipEqual(const String &str1, const String &str2, int &index) const
{
    while (index < min(str1.length, str2.length) && str1.value[index] == str2.value[index])
    {
        index++;
    }
}

bool String::operator ==(const String &string) const
{
    int index = 0;
    skipEqual(*this, string, index);
    return (index == min(this->length, string.length) && this->length == string.length);
}

bool String::operator !=(const String &string) const
{
    return !(*this == string);
}

bool String::operator <(const String &string) const
{
    int index = 0;
    skipEqual(*this, string, index);
    return (index == min(this->length, string.length) && this->length < string.length) ||
           (index < min(this->length, string.length) && this->value[index] < string.value[index]);
}

bool String::operator >(const String &string) const
{
    return string < *this;
}

std::ostream &operator <<(std::ostream &out, const String &string)
{
    if (!isEmpty(&string))
        out << string.value;
    return out;
}

int length(char *string)
{
    int result = 0;
    while (string[result] != '\0')
    {
        result++;
    }
    return result;
}

int length(const String *string)
{
    return string == nullptr ? 0 : string->length;
}

const int p = 53;
const int module = 1000000000 + 7;

int getHash(const String *string)
{
    long long result = (unsigned char)string->value[0];
    for (int i = 1; i < length(string); i++)
    {
        result = (result * p + (unsigned char)string->value[i]) % module;
    }
    return result;
}

char getChar(String *string, int index)
{
    return index < length(string) ? string->value[index] : '\0';
}

String *clone(const String *string)
{
    return new String(string);
}

String *concat(String *string, const String *stringToConcat)
{
    int newLength = length(string) + length(stringToConcat);
    char *newString = new char[newLength + 1];
    for (int i = 0; i < length(string); i++)
    {
        newString[i] = string->value[i];
    }
    for (int i = 0; i < length(stringToConcat); i++)
    {
        newString[i + length(string)] = stringToConcat->value[i];
    }
    newString[newLength] = '\0';
    delete string;
    string = new String(newString, newLength);
    return string;
}

int min(int a, int b)
{
    return a < b ? a : b;
}

bool isEmpty(const String *string)
{
    return length(string) == 0;
}

String *substring(const String *string, int start, int length)
{
    int newLength = min(length, string->length - start);
    char *substr = new char[newLength + 1];
    for (int i = start; i < start + newLength; i++)
    {
        substr[i - start] = string->value[i];
    }
    substr[newLength] = '\0';
    return new String(substr, newLength);
}

char *stringToChar(const String *string)
{
    char *result = new char[length(string) + 1];
    for (int i = 0; i < length(string); i++)
    {
        result[i] = string->value[i];
    }
    result[length(string)] = '\0';
    return result;
}
