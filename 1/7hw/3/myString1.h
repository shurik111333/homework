#pragma once

struct String
{
private:
    char *value;
    int length;

    String (char *newString, int length);

public:
};

String *getNewString(char *newString, int length);

int length(String *string);

String *clone(String *string);

char getChar(String *string, int index);

int getHash(String *string);

void concat(String *string, String *stringToConcat);

int compare(String *string1, String *string2);

bool isEmpty(String *string);

String *substring(String *string, int start, int length);

char *stringToChar(String *string);

void deleteString(String *string);
