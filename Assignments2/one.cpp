#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Student {
    string name;
    string rollno;
    double cgpa;
    vector<string> courses;

public:
    // Default constructor
    Student() {
        name = "Unknown";
        rollno = "Unknown";
        cgpa = 0.0;
    }

    // Parameterized constructor
    Student(string name, string rollno, double cgpa, vector<string> courses = {}) {
        this->name = name;
        this->rollno = rollno;
        setCGPA(cgpa);  // validate CGPA
        this->courses = courses;
    }

    // Copy constructor
    Student(const Student &s) {
        name = s.name;
        rollno = s.rollno;
        cgpa = s.cgpa;
        courses = s.courses;
    }

    ~Student() {}

    void addCourse(string course) {
        for (const auto& c : courses) {
            if (c == course) {
                cout << "Course '"<<course<<"' already added.\n";
                return;
            }
        }
        courses.push_back(course);
        cout << "Course '"<<course<<"' added successfully.\n";
    }

    void setCGPA(double newCgpa) {
        if (newCgpa >= 0.0 && newCgpa <= 10.0) {
            cgpa = newCgpa;
        } else {
            cout << "Invalid CGPA. Must be between 0.0 and 10.0.\n";
        }
    }

    void displayInfo() const {
        cout << "Name: " << name << endl;
        cout << "Roll Number: " << rollno << endl;
        cout << "CGPA: " << cgpa << endl;
        cout << "Courses Enrolled: ";
        if (courses.empty()) {
            cout << "None";
        } else {
            for (const auto& course : courses) {
                cout << course << " ";
            }
        }
        cout << endl;
    }

    string getRollNumber() const {
        return rollno;
    }
};

class StudentManagementSystem {
    vector<Student> students;

public:
    void addStudent(const Student& s) {
        students.push_back(s);
        cout << "Student added successfully.\n";
    }

    void searchStudent(const string& rollno) const {
        for (const auto& student : students) {
            if (student.getRollNumber() == rollno) {
                cout << "\nStudent Found:\n";
                student.displayInfo();
                return;
            }
        }
        cout << "Student with Roll No " << rollno << " not found.\n";
    }

    void displayAllStudents() const {
        if (students.empty()) {
            cout << "No students in the system.\n";
            return;
        }
        for (const auto& student : students) {
            cout << "\n-----------------------------\n";
            student.displayInfo();
        }
    }
};

int main() {
    StudentManagementSystem sms;

    // Creating students with string roll numbers
    Student s1("Alice", "101", 8.5);
    s1.addCourse("Math");
    s1.addCourse("Physics");

    Student s2("Bob", "102", 7.8);
    s2.addCourse("Chemistry");

    Student s3 = s1; // using copy constructor

    // Adding students to the system
    sms.addStudent(s1);
    sms.addStudent(s2);
    sms.addStudent(s3);

    // Display all students
    cout << "\nAll Student Records:\n";
    sms.displayAllStudents();

    // Searching for a student
    cout << "\nSearching for Roll No 102:\n";
    sms.searchStudent("102");

    // Updating CGPA of s2 AFTER adding to system won't reflect unless re-added
    cout << "\nUpdating CGPA of s2 to 9.2:\n";
    s2.setCGPA(9.2);

    // To reflect the update, you must re-add or use references/pointers
    sms.addStudent(s2);  // optional: avoids pointer logic for now

    cout << "\nAfter CGPA Update:\n";
    sms.searchStudent("102");

    return 0;
}
