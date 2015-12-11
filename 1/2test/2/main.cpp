#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

const int countDay[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
const int maxMonth = 12;
const int dateLength = 10;
const int maxLen = 256;

struct Date
{
    int day;
    int month;
    int year;

    Date(int day, int month, int year)
    {
        this->day = day;
        this->month = month;
        this->year = year;
    }

    Date(char *text)
    {
        this->day = (text[0] - '0') * 10 + text[1] - '0';
        this->month = (text[3] - '0') * 10 + text[4] - '0';
        this->year = 0;
        for (int i = 6; i < dateLength; i++)
        {
            this->year = this->year * 10 + text[i] - '0';
        }
    }

    bool operator < (Date &date)
    {
        return (this->year < date.year || (this->year == date.year && this->month < date.month) ||
                (this->year == date.year && this->month == date.month && this->day < date.day));
    }
};

bool isDate(char text[])
{
    int len = strlen(text);
    if (len != dateLength)
        return false;
    bool result = true;
    for (int i = 0; i < 6; i++)
    {
        if ((i + 1) % 3 == 0)
            result &= text[i] == '.';
        else
            result &= isdigit(text[i]);
    }
    for (int i = 6; i < len; i++)
    {
        result &= isdigit(text[i]);
    }
    return result;
}

bool isCorrectDate(Date *date)
{
    return (date->month > 0 && date->month <= maxMonth && date->day > 0 && date->day <= countDay[date->month]);
}

Date *getDate(char text[])
{
    if (!isDate(text))
        return nullptr;
    Date *date = new Date(text);
    if (!isCorrectDate(date))
    {
        delete date;
        return nullptr;
    }
    return date;
}

Date *getNextDate(ifstream &fin)
{
    char currentText[maxLen] = {};
    Date *nextDate = getDate(currentText);
    while (!fin.eof() && nextDate == nullptr)
    {
        fin >> currentText;
        nextDate = getDate(currentText);
    }
    return nextDate;
}

int main()
{
    setlocale(LC_ALL, "rus");
    cout << "Введите имя файла" << endl;
    char file[maxLen] = {};
    cin >> file;
    ifstream fin(file);
    Date *minDate = getNextDate(fin);
    Date *nextDate = getNextDate(fin);
    while (nextDate)
    {
        if (*nextDate < *minDate)
        {
            delete minDate;
            minDate = nextDate;
        }
        else
        {
            delete nextDate;
        }
        nextDate = getNextDate(fin);
    }
    fin.close();
    if (minDate == nullptr)
        cout << "В файле отсутствуют даты" << endl;
    else
        cout << "Наименьшая дата: " << minDate->day << "." << minDate->month << "." << minDate->year << endl;
    delete minDate;
    return 0;
}

