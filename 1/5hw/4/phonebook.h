#pragma once

struct Phonebook;

Phonebook *getPhonebook();

void addPhoneNumber(Phonebook *book, char *name, char *phone);

bool getPhone(Phonebook *book, char *name, char *phone);

bool getName(Phonebook *book, char *name, char *phone);

bool saveBookToFile(Phonebook *book);

void deletePhonebook(Phonebook *book);
