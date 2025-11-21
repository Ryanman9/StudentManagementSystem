#include <iostream>
#include <fstream>
#include <string>
#include <limits>
using namespace std;

class Student
{
public:
    string roll;
    string course;
    string name;
    int age;
};

void addStudent()
{
    Student s;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter the name: ";
    getline(cin, s.name);

    cout << "Enter the age: ";
    cin >> s.age;

    cout << "Enter the roll number: ";
    cin >> s.roll;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter the course: ";
    getline(cin, s.course);

    ofstream file("student.txt", ios::app);
    if (!file)
    {
        cout << "Error opening file.\n";
        return;
    }

    file << s.roll << endl;
    file << s.name << endl;
    file << s.age << endl;
    file << s.course << endl;

    file.close();

    cout << "Student added successfully!" << endl;
}

void displayStudents()
{
    ifstream file("student.txt");

    if (!file.is_open())
    {
        cout << "No data found." << endl;
        return;
    }

    int age;
    string roll, name, course;

    cout << "\n==== Student List ====\n";
    cout << endl;

    while (true)
    {

        if (!getline(file, roll))
            break;
        getline(file, name);
        file >> age;
        file.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(file, course);

        cout << "Roll no : " << roll << endl;
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "Course: " << course << endl;
        cout << "------------------------------" << endl;
    }

    file.close();
}

void searchStudent()
{
    ifstream file("student.txt");

    if (!file.is_open())
    {
        cout << "No data found." << endl;
        return;
    }

    string searchbyRoll;
    cout << "Enter roll number to search: ";
    cin >> searchbyRoll;

    string roll, name, course;
    int age;
    bool found = false;

    while (true)
    {
        if (!getline(file, roll))
            break;
        getline(file, name);
        file >> age;
        file.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(file, course);

        if (roll == searchbyRoll)
        {
            cout << "\n==== Student Found ====\n";
            cout << "Roll no: " << roll << endl;
            cout << "Name: " << name << endl;
            cout << "Age: " << age << endl;
            cout << "Course: " << course << endl;
            cout << "----------------------------" << endl;

            found = true;
            break;
        }
    }

    if (!found)
    {
        cout << "\n No student found with roll number: " << searchbyRoll << endl;
    }

    file.close();
}

void deleteStudent()
{
    ifstream file("student.txt");
    ofstream temp("temp.txt");

    if (!file.is_open() || !temp.is_open())
    {
        cout << "Error opening file." << endl;
        return;
    }

    string deletebyRoll;
    cout << "Enter the roll number to delete: ";
    cin >> deletebyRoll;

    string roll, name, course;
    int age;
    bool found = false;

    while (true)
    {
        if (!getline(file, roll))
            break;
        getline(file, name);
        file >> age;
        file.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(file, course);

        if (roll == deletebyRoll)
        {

            found = true;
            continue;
        }

        temp << roll << endl;
        temp << name << endl;
        temp << age << endl;
        temp << course << endl;
    }

    file.close();
    temp.close();

    remove("student.txt");
    rename("temp.txt", "student.txt");

    if (found)
    {
        cout << "Student deleted successfull." << endl;
    }
    else
    {
        cout << "No student found with the roll number: " << deletebyRoll << endl;
    }
}

void updateStudent()
{
    ifstream file("student.txt");
    ofstream temp("temp.txt");

    if (!file.is_open() || !temp.is_open())
    {
        cout << "Error opening file." << endl;
        return;
    }

    string updatebyRoll;
    cout << "Enter the roll number to update: ";
    cin >> updatebyRoll;

    string roll, name, course;
    int age;

    bool found = false;

    while (true)
    {
        if (!getline(file, roll))
            break;
        getline(file, name);
        file >> age;
        file.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(file, course);

        if (roll == updatebyRoll)
        {
            found = true;
            cout << "\n=== Current Details ===" << endl;
            cout << "Roll: " << roll << endl;
            cout << "Name: " << name << endl;
            cout << "Age: " << age << endl;
            cout << "Course: " << course << endl;

            cout << "Enter new details" << endl;

            Student s;
            cout << "New name: " << endl;
            getline(cin, s.name);

            cout << "New age: " << endl;
            cin >> s.age;

            cout << "New roll: " << endl;
            cin >> s.roll;

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "New course: " << endl;
            getline(cin, s.course);

            temp << s.roll << endl;
            temp << s.name << endl;
            temp << s.age << endl;
            temp << s.course << endl;
        }
    }

    file.close();
    temp.close();

    remove("student.txt");
    rename("temp.txt", "student.txt");

    if (found)
    {
        cout << "Studnet updated succesfully." << endl;
    }
    else
    {
        cout << "No student found with roll number: " << updatebyRoll << endl;
    }
}

void countStudents()
{
    ifstream file("student.txt");

    if (!file.is_open())
    {
        cout << "No data found." << endl;
        return;
    }

    int count = 0;
    string roll, name, course;
    int age;

    while (true)
    {
        if (!getline(file, roll))
            break;
        getline(file, name);
        file >> age;
        file.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(file, course);

        count++;
    }

    file.close();

    cout << "\nTotal number of students: " << count << endl;
}

int main()
{
    int choice;

    do
    {
        cout << "==== Student Management System ====" << endl;
        cout << "1. Add student" << endl;
        cout << "2. Display student" << endl;
        cout << "3. Search Student" << endl;
        cout << "4. Delete student" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a number." << endl;
            continue;
        }

        switch (choice)
        {
        case 1:
            addStudent();
            break;

        case 2:
            displayStudents();
            break;

        case 3:
            searchStudent();
            break;

        case 4:
            deleteStudent();
            break;

        case 5:
            updateStudent();
            break;

        case 6:
            countStudents();
            break;

        case 7:
            cout << "Exiting the program..." << endl;
            break;

        default:
            cout << "Invalid choice!" << endl;
        }

    } while (choice != 7);

    return 0;
}