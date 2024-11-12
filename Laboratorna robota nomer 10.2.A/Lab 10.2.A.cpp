// Lab 10.2.A

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <Windows.h>

using namespace std;

struct Student 
{
    string lastName;
    int course;
    string specialty;
    int physicsGrade;
    int mathGrade;
    int informaticsGrade;
};

void printTable(const vector<Student>& students) 
{
    cout << "---------------------------------------------------------------------------\n";
    cout << "| № | Прізвище | Курс | Спеціальність | Фізики | Математика | Інформатика |\n";
    cout << "---------------------------------------------------------------------------\n";
    for (size_t i = 0; i < students.size(); ++i) 
    {
        cout << "| " << i + 1 << "  | " << students[i].lastName << " | "
            << students[i].course << "     | " << students[i].specialty << "    | "
            << students[i].physicsGrade << "       | "
            << students[i].mathGrade << "   | "
            << students[i].informaticsGrade << "   |\n";
    }
    cout << "----------------------------------------------------------------------------\n";
}

bool compareStudents(const Student& a, const Student& b) 
{
    if (a.course != b.course) return a.course < b.course;
    if (a.informaticsGrade != b.informaticsGrade) return a.informaticsGrade > b.informaticsGrade;
    return a.lastName > b.lastName; 
}

bool compareIndex(const Student& a, const Student& b) 
{
    if (a.course != b.course) return a.course < b.course;
    if (a.informaticsGrade != b.informaticsGrade) return a.informaticsGrade > b.informaticsGrade;
    return a.lastName < b.lastName; 
}

bool binarySearch(const vector<Student>& students, const string& lastName, int course, int informaticsGrade) 
{
    int left = 0;
    int right = students.size() - 1;
    while (left <= right) 
    {
        int mid = left + (right - left) / 2;
        if (students[mid].lastName == lastName && students[mid].course == course && students[mid].informaticsGrade == informaticsGrade)
            return true;
        if (students[mid].lastName < lastName || (students[mid].lastName == lastName && (students[mid].course < course || (students[mid].course == course && students[mid].informaticsGrade < informaticsGrade))))
            left = mid + 1;
        else
            right = mid - 1;
    }
    return false;
}

int main() 
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int n;
    cout << "ввести кількість студентів: ";
    cin >> n;
    cin.ignore();  

    vector<Student> students(n);

    for (int i = 0; i < n; ++i) 
    {
        cout << "Введіть інформайію про студента " << i + 1 << ":\n";
        cout << "Прізвище: ";
        getline(cin, students[i].lastName);
        cout << "Курс: ";
        cin >> students[i].course;
        cin.ignore(); 
        cout << "Спеціальність: ";
        getline(cin, students[i].specialty);
        cout << "Оцінка з Фізики: ";
        cin >> students[i].physicsGrade;
        cout << "Оцінка з Математики: ";
        cin >> students[i].mathGrade;
        cout << "Оцінка з Інформатики: ";
        cin >> students[i].informaticsGrade;
        cin.ignore(); 
    }

    // Меню
    int choice;
    do 
    {
        cout << "\nMenu:\n";
        cout << "1. Sort students\n";
        cout << "2. Create an index array\n";
        cout << "3. Search student\n";
        cout << "4. Exit\n";
        cout << "Виберіть опцію: ";
        cin >> choice;
        cin.ignore();  

        switch (choice) 
        {
        case 1: 
        {
            sort(students.begin(), students.end(), compareStudents);
            printTable(students);
            break;
        }
        case 2: 
        {
            vector<Student> index = students;
            sort(index.begin(), index.end(), compareIndex);
            printTable(index);
            break;
        }
        case 3: 
        {
            string lastName;
            int course, informaticsGrade;
            cout << "Введіть прізвище: ";
            getline(cin, lastName);
            cout << "Введіть курс: ";
            cin >> course;
            cout << "Введіть оцінку з Інформатики: ";
            cin >> informaticsGrade;
            cin.ignore();  

            bool found = binarySearch(students, lastName, course, informaticsGrade);
            if (found)
                cout << "Student found.\n";
            else
                cout << "Student not found.\n";
            break;
        }
        case 4:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 4);

    return 0;
}
