#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <stdexcept>
#include <algorithm>

using namespace std;

// Exception Hierarchy
class UniversitySystemException : public exception {
protected:
    string message;
public:
    UniversitySystemException(const string& msg) : message(msg) {}
    const char* what() const noexcept override { return message.c_str(); }
};

class EnrollmentException : public UniversitySystemException {
public:
    EnrollmentException(const string& msg) : UniversitySystemException("Enrollment Error: " + msg) {}
};

class GradeException : public UniversitySystemException {
public:
    GradeException(const string& msg) : UniversitySystemException("Grade Error: " + msg) {}
};

class PaymentException : public UniversitySystemException {
public:
    PaymentException(const string& msg) : UniversitySystemException("Payment Error: " + msg) {}
};

// Base Class
class Person {
protected:
    string name, ID, contact;
    int age;
public:
    Person(string n, int a, string i, string c) {
        setName(n); setAge(a); ID = i; contact = c;
    }
    virtual ~Person() {}

    void setName(const string& n) {
        if (n.empty()) throw invalid_argument("Name cannot be empty.");
        name = n;
    }

    void setAge(int a) {
        if (a <= 0 || a > 120) throw invalid_argument("Invalid age.");
        age = a;
    }

    virtual void displayDetails() const {
        cout << "Name: " << name << ", Age: " << age << ", ID: " << ID << ", Contact: " << contact << endl;
    }

    virtual double calculatePayment() const = 0;
};

// Student and Subclasses
class Student : public Person {
protected:
    string program;
    double GPA;
    string enrollmentDate;
public:
    Student(string n, int a, string i, string c, string ed, string pr, double gpa)
        : Person(n, a, i, c), enrollmentDate(ed), program(pr), GPA(gpa) {
        setGPA(gpa);
    }

    void setGPA(double gpa) {
        if (gpa < 0.0 || gpa > 4.0) throw invalid_argument("GPA must be 0.0 - 4.0.");
        GPA = gpa;
    }

    void displayDetails() const override {
        Person::displayDetails();
        cout << "Program: " << program << ", GPA: " << GPA << ", Enrolled: " << enrollmentDate << endl;
    }

    double calculatePayment() const override {
        return 1000.0;
    }
};

class GraduateStudent : public Student {
    string researchTopic, advisor, thesis;
public:
    GraduateStudent(string n, int a, string i, string c, string ed, string pr, double gpa,
                    string topic, string adv, string th)
        : Student(n, a, i, c, ed, pr, gpa), researchTopic(topic), advisor(adv), thesis(th) {}

    double calculatePayment() const override {
        return 500.0;
    }

    void displayDetails() const override {
        Student::displayDetails();
        cout << "Research: " << researchTopic << ", Advisor: " << advisor << ", Thesis: " << thesis << endl;
    }
};

// Professor and Subclasses
class Professor : public Person {
protected:
    string department, specialization, hireDate;
public:
    Professor(string n, int a, string i, string c, string d, string s, string h)
        : Person(n, a, i, c), department(d), specialization(s), hireDate(h) {}

    void displayDetails() const override {
        Person::displayDetails();
        cout << "Department: " << department << ", Specialization: " << specialization << ", Hired: " << hireDate << endl;
    }

    double calculatePayment() const override {
        return 4000.0;
    }
};

class FullProfessor : public Professor {
    int yearsOfService;
    double grants;
public:
    FullProfessor(string n, int a, string i, string c, string d, string s, string h, int y, double g)
        : Professor(n, a, i, c, d, s, h), yearsOfService(y), grants(g) {}

    double calculatePayment() const override {
        return 5000 + 200 * yearsOfService + 0.1 * grants;
    }

    void displayDetails() const override {
        Professor::displayDetails();
        cout << "Years of Service: " << yearsOfService << ", Research Grants: " << grants << endl;
    }
};

// Course and Department
class Course {
    string code, title, description;
    int credits;
    Professor* instructor;
public:
    Course(string c, string t, int cr, string d, Professor* prof = nullptr)
        : code(c), title(t), credits(cr), description(d), instructor(prof) {
        if (credits <= 0) throw invalid_argument("Credits must be positive.");
    }

    void assignProfessor(Professor* prof) {
        instructor = prof;
    }
};

class Department {
    string name, location;
    double budget;
    vector<Professor*> professors;
public:
    Department(string n, string l, double b) : name(n), location(l), budget(b) {}

    void addProfessor(Professor* p) {
        professors.push_back(p);
    }
};

// GradeBook
class GradeBook {
    map<string, double> grades;
public:
    void addGrade(const string& studentID, double grade) {
        if (grade < 0.0 || grade > 100.0) throw GradeException("Grade must be between 0 and 100.");
        grades[studentID] = grade;
    }

    double calculateAverageGrade() const {
        if (grades.empty()) return 0;
        double sum = 0;
        for (auto& [id, g] : grades) sum += g;
        return sum / grades.size();
    }

    vector<string> getFailingStudents() const {
        vector<string> failing;
        for (auto& [id, g] : grades)
            if (g < 50) failing.push_back(id);
        return failing;
    }
};

// Enrollment Manager
class EnrollmentManager {
    map<string, vector<Course*>> enrollment;
public:
    void enrollStudent(const string& studentID, Course* course) {
        if (enrollment[studentID].size() >= 5)
            throw EnrollmentException("Student cannot enroll in more than 5 courses.");
        enrollment[studentID].push_back(course);
    }

    void dropStudent(const string& studentID, Course* course) {
        auto& courses = enrollment[studentID];
        auto it = find(courses.begin(), courses.end(), course);
        if (it != courses.end()) {
            courses.erase(it);
        }
    }

    int getEnrollmentCount(const string& studentID) const {
        return enrollment.count(studentID) ? enrollment.at(studentID).size() : 0;
    }
};

// University System
class UniversitySystem {
    vector<Department*> departments;
    vector<Student*> students;
    vector<Professor*> professors;
    EnrollmentManager enrollmentManager;

public:
    void addDepartment(Department* d) { departments.push_back(d); }
    void addStudent(Student* s) { students.push_back(s); }
    void addProfessor(Professor* p) { professors.push_back(p); }

    void enrollStudent(const string& studentID, Course* c) {
        enrollmentManager.enrollStudent(studentID, c);
    }

    void showAllPeople() {
        for (auto* s : students) s->displayDetails();
        for (auto* p : professors) p->displayDetails();
    }
};

// Main Function
int main() {
    try {
        UniversitySystem uni;

        // Professors
        FullProfessor* prof1 = new FullProfessor("Dr. Smith", 50, "P001", "smith@uni.edu", "CS", "AI", "2010-08-01", 15, 30000);
        Professor* prof2 = new Professor("Dr. Allen", 45, "P002", "allen@uni.edu", "Math", "Algebra", "2015-01-10");
        uni.addProfessor(prof1);
        uni.addProfessor(prof2);

        // Students
        Student* stud1 = new Student("Alice", 20, "S001", "alice@uni.edu", "2023-01-10", "CS", 3.8);
        GraduateStudent* grad1 = new GraduateStudent("Bob", 25, "S002", "bob@uni.edu", "2022-09-01", "CS", 3.5, "ML", "Dr. Smith", "Deep Learning");
        uni.addStudent(stud1);
        uni.addStudent(grad1);

        // Courses
        Course* course1 = new Course("CS101", "Intro to CS", 3, "Basics of programming", prof1);

        // Enrollment
        uni.enrollStudent("S001", course1);
        uni.enrollStudent("S002", course1);

        // Display
        cout << "\n=== University People ===\n";
        uni.showAllPeople();

    } catch (const UniversitySystemException& ex) {
        cerr << "System Error: " << ex.what() << endl;
    } catch (const exception& ex) {
        cerr << "Error: " << ex.what() << endl;
    }

    return 0;
}
