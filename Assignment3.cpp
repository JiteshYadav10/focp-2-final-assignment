#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Base class Person
class Person {
protected:
    string name;
    int age;
    string ID;
    string contactInfo;

public:
    Person(string name, int age, string ID, string contactInfo)
        : name(name), age(age), ID(ID), contactInfo(contactInfo) {}

    virtual void displayDetails() const {
        cout << "Name: " << name << ", Age: " << age << ", ID: " << ID 
             << ", Contact: " << contactInfo << endl;
    }

    virtual double calculatePayment() const { return 0.0; }

    virtual ~Person() {}
};

// Derived class Student
class Student : public Person {
protected:
    string enrollmentDate;
    string program;
    float GPA;

public:
    Student(string name, int age, string ID, string contactInfo, 
            string enrollmentDate, string program, float GPA)
        : Person(name, age, ID, contactInfo), enrollmentDate(enrollmentDate), 
          program(program), GPA(GPA) {}

    virtual void displayDetails() const override {
        Person::displayDetails();
        cout << "Enrollment Date: " << enrollmentDate 
             << ", Program: " << program << ", GPA: " << GPA << endl;
    }

    double calculatePayment() const override { return 5000.0; }
};

// Derived classes UndergraduateStudent and GraduateStudent
class UndergraduateStudent : public Student {
private:
    string major, minor, graduationDate;

public:
    UndergraduateStudent(string name, int age, string ID, string contactInfo, 
                         string enrollmentDate, string program, float GPA,
                         string major, string minor, string graduationDate)
        : Student(name, age, ID, contactInfo, enrollmentDate, program, GPA),
          major(major), minor(minor), graduationDate(graduationDate) {}

    void displayDetails() const override {
        Student::displayDetails();
        cout << "Major: " << major << ", Minor: " << minor 
             << ", Expected Graduation Date: " << graduationDate << endl;
    }
};

class GraduateStudent : public Student {
private:
    string researchTopic, advisor, thesisTitle;

public:
    GraduateStudent(string name, int age, string ID, string contactInfo, 
                    string enrollmentDate, string program, float GPA,
                    string researchTopic, string advisor, string thesisTitle)
        : Student(name, age, ID, contactInfo, enrollmentDate, program, GPA),
          researchTopic(researchTopic), advisor(advisor), thesisTitle(thesisTitle) {}

    void displayDetails() const override {
        Student::displayDetails();
        cout << "Research Topic: " << researchTopic 
             << ", Advisor: " << advisor << ", Thesis Title: " << thesisTitle << endl;
    }
};

// Derived class Professor
class Professor : public Person {
protected:
    string department;
    string specialization;
    int yearsOfService;

public:
    Professor(string name, int age, string ID, string contactInfo, 
              string department, string specialization, int yearsOfService)
        : Person(name, age, ID, contactInfo), department(department), 
          specialization(specialization), yearsOfService(yearsOfService) {}

    virtual void displayDetails() const override {
        Person::displayDetails();
        cout << "Department: " << department 
             << ", Specialization: " << specialization 
             << ", Years of Service: " << yearsOfService << endl;
    }

    virtual double calculatePayment() const override { return 60000.0 + yearsOfService * 1000; }
};

// Derived classes AssistantProfessor, AssociateProfessor, FullProfessor
class AssistantProfessor : public Professor {
public:
    AssistantProfessor(string name, int age, string ID, string contactInfo, 
                       string department, string specialization, int yearsOfService)
        : Professor(name, age, ID, contactInfo, department, specialization, yearsOfService) {}

    double calculatePayment() const override { return 70000.0 + yearsOfService * 1500; }
};

class AssociateProfessor : public Professor {
public:
    AssociateProfessor(string name, int age, string ID, string contactInfo, 
                       string department, string specialization, int yearsOfService)
        : Professor(name, age, ID, contactInfo, department, specialization, yearsOfService) {}

    double calculatePayment() const override { return 90000.0 + yearsOfService * 2000; }
};

class FullProfessor : public Professor {
public:
    FullProfessor(string name, int age, string ID, string contactInfo, 
                  string department, string specialization, int yearsOfService)
        : Professor(name, age, ID, contactInfo, department, specialization, yearsOfService) {}

    double calculatePayment() const override { return 120000.0 + yearsOfService * 3000; }
};

// University Class containing Departments
class Department {
private:
    string name;
    vector<Professor*> professors;

public:
    Department(string name) : name(name) {}

    void addProfessor(Professor* professor) {
        professors.push_back(professor);
    }

    void displayProfessors() const {
        cout << "Department: " << name << endl;
        for (const auto& prof : professors) {
            prof->displayDetails();
        }
    }
};

// University Class
class University {
private:
    vector<Department> departments;

public:
    void addDepartment(Department department) {
        departments.push_back(department);
    }

    void displayDepartments() const {
        for (const auto& dept : departments) {
            dept.displayProfessors();
        }
    }
};

int main() {
    University uni;
    Department csDept("Computer Science");

    AssistantProfessor ap("Rohit", 20, "P789", "rohit@uni.edu", "CS", "AI", 5);
    csDept.addProfessor(&ap);

    uni.addDepartment(csDept);
    uni.displayDepartments();

    return 0;
}