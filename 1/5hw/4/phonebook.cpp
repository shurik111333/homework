#include <cstring>
#include <cstdio>

using namespace std;

const char *defaultPhoneBaseFile = "base.txt";
const char delimiter = ';';
const int maxLen = 256;

struct PhonebookNode
{
    char *name;
    char *phone;
    PhonebookNode *next;
};

struct Phonebook
{
    PhonebookNode *first;

};

const char *def = "st";

void addPhoneNumber(Phonebook *book, char *name, char *phone)
{
    char *newName = name;
    char *newPhone = phone;
    PhonebookNode *newNode = new PhonebookNode {newName, newPhone, book->first};
    book->first = newNode;
}

Phonebook *getPhonebook()
{
    FILE *base = fopen(defaultPhoneBaseFile, "r");
    Phonebook *newBook = new Phonebook {nullptr};
    if (base != nullptr)
    {
        char *currentName = new char[maxLen];
        char *currentPhone = new char[maxLen];
        char *newLine = new char[maxLen];
        while (fgets(newLine, maxLen - 1, base) != nullptr)
        {
            currentName = strtok(newLine, &delimiter);
            currentPhone = strtok(NULL, &delimiter);
            addPhoneNumber(newBook, currentName, currentPhone);
        }
        fclose(base);
        delete[] newLine;
        delete[] currentName;
        delete[] currentPhone;
    }
    return newBook;
}

bool getPhone(Phonebook *book, char *name, char *phone)
{
    PhonebookNode *currentNode = book->first;
    while (currentNode != nullptr && strcmp(name, currentNode->name) != 0)
    {
        currentNode = currentNode->next;
    }
    if (currentNode != nullptr)
    {
        strcpy(phone, currentNode->phone);
        return true;
    }
    return false;
}

bool getName(Phonebook *book, char *name, char *phone)
{
    PhonebookNode *currentNode = book->first;
    while (currentNode != nullptr && strcmp(phone, currentNode->phone) != 0)
    {
        currentNode = currentNode->next;
    }
    if (currentNode != nullptr)
    {
        strcpy(name, currentNode->name);
        return true;
    }
    return false;
}

bool saveBookToFile(Phonebook *book)
{
    FILE *base = fopen(defaultPhoneBaseFile, "w");
    if (base == nullptr)
    {
        return false;
    }
    PhonebookNode *currentNode = book->first;
    while (currentNode != nullptr)
    {
        fputs(currentNode->name, base);
        fputs(&delimiter, base);
        fputs(currentNode->phone, base);
        fputs(&delimiter, base);
        fputs("\n", base);
        currentNode = currentNode->next;
    }
    fclose(base);
    return true;
}

void deleteName(Phonebook *book, char *name)
{
    PhonebookNode *previousNode = nullptr;
    PhonebookNode *currentNode = book->first;
    while (currentNode != nullptr && strcmp(name, currentNode->name) != 0)
    {
        previousNode = currentNode;
        currentNode = currentNode->next;
    }
    if (currentNode != nullptr)
    {
        if (previousNode == nullptr)
        {
            book->first = currentNode->next;
        }
        else
        {
            previousNode->next = currentNode->next;
        }
        delete currentNode;
    }
}

void deletePhonebook(Phonebook *book)
{
    while (book->first != nullptr)
    {
        deleteName(book, book->first->name);
    }
    delete book;
}
