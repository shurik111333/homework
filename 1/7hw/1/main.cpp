#include <iostream>
#include <cstring>

using namespace std;

const int numberFairStudents = 3;
const int versionsOfFairSTudents[numberFairStudents + 1] = {0, 1, 2, 3};
const int numberVersions = 3;

int getVersion(int studentId, int students[])
{
    if (students[studentId] <= numberVersions)
        return students[studentId];
    else
    {
        students[studentId] = getVersion(students[studentId], students);
        return students[studentId];
    }
}

int main()
{
    setlocale(LC_ALL, "rus");
    cout << "Введите количество студентов" << endl;
    int count = 0;
    cin >> count;
    int *students = new int[count + 1];
    memset(students, 0, sizeof(int) * (count + 1));
    for (int i = 1; i <= numberFairStudents; i++)
    {
        students[i] = versionsOfFairSTudents[i];
    }
    cout << "Введите количество пар студентов" << endl;
    int numberPairs = 0;
    cin >> numberPairs;
    cout << "Введите пары студентов" << endl;
    for (int i = 0; i < numberPairs; i++)
    {
        int student1 = 0, student2 = 0;
        cin >> student1 >> student2;
        students[student1] = student2;
    }
    for (int i = 1; i <= count; i++)
    {
        cout << "Студент " << i << ": ";
        int version = getVersion(i, students);
        if (version == 0)
        {
            cout << "отчислить" << endl;
        }
        else
        {
            cout << "вариант " << version << endl;
        }
    }
    delete[] students;
    return 0;
}

