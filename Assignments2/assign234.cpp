#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <stdexcept>
#include <algorithm>

using namespace std;

// Exception Hierarchy
class UniversitySystemException : public exception 
{
    protected:
        string message;
    public:
        UniversitySystemException(const string& msg) : message(msg) {}
        const char* what() const noexcept override { return message.c_str(); }
};

class EnrollmentException : public UniversitySystemException 
{
    public:
    EnrollmentException(const string& msg) : UniversitySystemException("Enrollment Error: " + msg) {}
};

class GradeException : public UniversitySystemException 
{
    public:
    GradeException(const string& msg) : UniversitySystemException("Grade Error: " + msg) {}
};

class PaymentException : public UniversitySystemException 
{
    public:
    PaymentException(const string& msg) : UniversitySystemException("Payment Error: " + msg) {}
};


//Base class
class Person    
{
    protected:
        string name, ID, contact;
        int age;
    public:
        Person(string n, int a, string i, string c)
        {
            setName(n);
            setAge(a);
            ID = i;
            contact = c;
        }
    virtual ~Person() {}

    void setName(const string& n)
    {
        if (n.empty()) 
            throw invalid_argument("Name cannot be empty.");
        name = n;
    }

    void setAge(int a)
    {
        if (a<=0||a>120)
            throw invalid_argument("Invalid age.");
        age = a;
    }

    virtual void displayDetails() const
    {
        cout<<"Name : "<< name <<", Age : "<< age <<", ID : "<< ID <<", Contact : "<< contact << endl;
    }

    virtual double calculatePayment() const = 0;
};

class Student : public Person 
{
    protected:
        string program;
        double GPA;
        string enrollmentDate;
    public:
        Student(string n, int a, string i, string c, string ed, string pr, double gpa) : Person(n, a, i, c), enrollmentDate(ed), program(pr), GPA(gpa) 
        {
            setGPA(gpa);
        }

    void setGPA(double gpa) 
    {
        if (gpa < 0.0 || gpa > 4.0) throw invalid_argument("GPA must be 0.0 - 4.0.");
        GPA = gpa;
    }

    void displayDetails() const override 
    {
        Person::displayDetails();
        cout << "Program: " << program << ", GPA: " << GPA << ", Enrolled: " << enrollmentDate << endl;
    }

    double calculatePayment() const override 
    {
        return 1000.0;
    }
};

class GraduateStudent : public Student 
{
    string researchTopic, advisor, thesis;
    public:
        GraduateStudent(string n, int a, string i, string c, string ed, string pr, double gpa,string topic, string adv, string th) : Student(n, a, i, c, ed, pr, gpa), researchTopic(topic), advisor(adv), thesis(th) {}

        double calculatePayment() const override 
        {
            return 500.0;
        }

        void displayDetails() const override 
        {
            Student::displayDetails();
            cout << "Research: " << researchTopic << ", Advisor: " << advisor << ", Thesis: " << thesis << endl;
        }
};

// Professor and Subclasses
class Professor : public Person 
{
    protected:
        string department, specialization, hireDate;
    public:
        Professor(string n, int a, string i, string c, string d, string s, string h) : Person(n, a, i, c), department(d), specialization(s), hireDate(h) {}

        void displayDetails() const override 
        {
            Person::displayDetails();
            cout << "Department: " << department << ", Specialization: " << specialization << ", Hired: " << hireDate << endl;
        }

        double calculatePayment() const override 
        {
            return 4000.0;
        }
};

class FullProfessor : public Professor 
{
    int yearsOfService;
    double grants;
    public:
        FullProfessor(string n, int a, string i, string c, string d, string s, string h, int y, double g) : Professor(n, a, i, c, d, s, h), yearsOfService(y), grants(g) {}

        double calculatePayment() const override 
        {
            return 5000 + 200 * yearsOfService + 0.1 * grants;
        }

        void displayDetails() const override 
        {
            Professor::displayDetails();
            cout << "Years of Service: " << yearsOfService << ", Research Grants: " << grants << endl;
        }
};

// Course and Department
class Course 
{
    string code, title, description;
    int credits;
    Professor* instructor;
    public:
        Course(string c, string t, int cr, string d, Professor* prof = nullptr) : code(c), title(t), credits(cr), description(d), instructor(prof) 
        {
            if (credits <= 0) throw invalid_argument("Credits must be positive.");
        }

        void assignProfessor(Professor* prof) 
        {
            instructor = prof;
        }
};

class Department 
{
    string name, location;
    double budget;
    vector<Professor*> professors;
    public:
        Department(string n, string l, double b) : name(n), location(l), budget(b) {}

        void addProfessor(Professor* p) 
        {
            professors.push_back(p);
        }
};

// GradeBook
class GradeBook 
{
    map<string, double> grades;
    public:
        void addGrade(const string& studentID, double grade) 
        {
            if (grade < 0.0 || grade > 100.0) 
                throw GradeException("Grade must be between 0 and 100.");
            grades[studentID] = grade;
        }

        double calculateAverageGrade() const 
        {
            if (grades.empty()) return 0;
            double sum = 0;
            for (auto& [id, g] : grades) sum += g;
            return sum / grades.size();
        }

        vector<string> getFailingStudents() const 
        {
            vector<string> failing;
            for (auto& [id, g] : grades)
                if (g < 50) failing.push_back(id);
            return failing;
        }
};

// Enrollment Manager
class EnrollmentManager 
{
    map<string, vector<Course*>> enrollment;
    public:
        void enrollStudent(const string& studentID, Course* course) 
        {
            if (enrollment[studentID].size() >= 5)
                throw EnrollmentException("Student cannot enroll in more than 5 courses.");
            enrollment[studentID].push_back(course);
        }

        void dropStudent(const string& studentID, Course* course) 
        {
            auto& courses = enrollment[studentID];
            auto it = find(courses.begin(), courses.end(), course);
            if (it != courses.end()) 
            {
                courses.erase(it);
            }
        }

        int getEnrollmentCount(const string& studentID) const 
        {
            return enrollment.count(studentID) ? enrollment.at(studentID).size() : 0;
        }
};

// University System
class UniversitySystem 
{
    vector<Department*> departments;
    vector<Student*> students;
    vector<Professor*> professors;
    EnrollmentManager enrollmentManager;

    public:
        void addDepartment(Department* d) { departments.push_back(d); }
        void addStudent(Student* s) { students.push_back(s); }
        void addProfessor(Professor* p) { professors.push_back(p); }

        void enrollStudent(const string& studentID, Course* c) 
        {
            enrollmentManager.enrollStudent(studentID, c);
        }

        void showAllPeople() 
        {
            cout << "\n--- Students ---\n";
            for (auto* s : students)
            s->displayDetails();

            cout << "\n--- Professors ---\n";
            for (auto* p : professors)
            p->displayDetails();
    }


// Main Function
int main() {
    UniversitySystem uni;

    while (true) {
        cout << "\n--- University Management System ---\n";
        cout << "1. Add Professor\n";
        cout << "2. Add Student\n";
        cout << "3. Add Course\n";
        cout << "4. Enroll Student in Course\n";
        cout << "5. Show All People\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;
        cin.ignore(); // flush newline

        try {
            if (choice == 1) {
                string name, id, contact, dept, spec, hireDate;
                int age, years;
                double grants;

                cout << "Enter name: "; getline(cin, name);
                cout << "Enter age: "; cin >> age; cin.ignore();
                cout << "Enter ID: "; getline(cin, id);
                cout << "Enter contact: "; getline(cin, contact);
                cout << "Enter department: "; getline(cin, dept);
                cout << "Enter specialization: "; getline(cin, spec);
                cout << "Enter hire date: "; getline(cin, hireDate);
                cout << "Enter years of service: "; cin >> years;
                cout << "Enter grants: "; cin >> grants; cin.ignore();

                auto* prof = new FullProfessor(name, age, id, contact, dept, spec, hireDate, years, grants);
                uni.addProfessor(prof);
                cout << "Professor added.\n";

            } else if (choice == 2) {
                int type;
                cout << "1. Undergraduate Student\n2. Graduate Student\nChoose type: ";
                cin >> type; cin.ignore();

                string name, id, contact, program, date;
                int age;
                double gpa;

                cout << "Enter name: "; getline(cin, name);
                cout << "Enter age: "; cin >> age; cin.ignore();
                cout << "Enter ID: "; getline(cin, id);
                cout << "Enter contact: "; getline(cin, contact);
                cout << "Enter enrollment date: "; getline(cin, date);
                cout << "Enter program: "; getline(cin, program);
                cout << "Enter GPA: "; cin >> gpa; cin.ignore();

                if (type == 1) {
                    auto* stud = new Student(name, age, id, contact, date, program, gpa);
                    uni.addStudent(stud);
                    cout << "Student added.\n";
                } else {
                    string topic, advisor, thesis;
                    cout << "Enter research topic: "; getline(cin, topic);
                    cout << "Enter advisor: "; getline(cin, advisor);
                    cout << "Enter thesis title: "; getline(cin, thesis);
                    auto* grad = new GraduateStudent(name, age, id, contact, date, program, gpa, topic, advisor, thesis);
                    uni.addStudent(grad);
                    cout << "Graduate student added.\n";
                }

            } else if (choice == 3) {
                string code, title, desc;
                int credits;

                cout << "Enter course code: "; getline(cin, code);
                cout << "Enter title: "; getline(cin, title);
                cout << "Enter credits: "; cin >> credits; cin.ignore();
                cout << "Enter description: "; getline(cin, desc);

                // For simplicity, we won't assign a professor here.
                Course* c = new Course(code, title, credits, desc);
                cout << "Course created (not yet assigned to professor).\n";

            } else if (choice == 4) {
                string studentID, courseCode;
                cout << "Enter student ID: "; getline(cin, studentID);
                cout << "Enter course code (this should match an existing course in your code): "; getline(cin, courseCode);

                // WARNING: in real code, you should look up course by code.
                // For now, we'll simulate with a static course for simplicity.
                Course* tempCourse = new Course(courseCode, "TempTitle", 3, "TempDesc");

                uni.enrollStudent(studentID, tempCourse);
                cout << "Student enrolled in course.\n";

            } else if (choice == 5) {
                uni.showAllPeople();

            } else if (choice == 6) {
                cout << "Exiting...\n";
                break;

            } else {
                cout << "Invalid choice. Try again.\n";
            }
        }
        catch (const UniversitySystemException& ex) {
            cerr << "System Error: " << ex.what() << endl;
        }
        catch (const exception& ex) {
            cerr << "Standard Error: " << ex.what() << endl;
        }
    }

    return 0;
}
