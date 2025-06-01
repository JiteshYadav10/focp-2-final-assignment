#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

using namespace std;

//CUSTOM EXCEPTION CLASSES 

class UniversitySystemException : public exception {
protected:
    string message;
public:
    UniversitySystemException(string msg) : message(msg) {}
    virtual const char* what() const noexcept override {
        return message.c_str();
    }
};

class EnrollmentException : public UniversitySystemException {
public:
    EnrollmentException(string msg) : UniversitySystemException("Enrollment Error: " + msg) {}
};

class GradeException : public UniversitySystemException {
public:
    GradeException(string msg) : UniversitySystemException("Grade Error: " + msg) {}
};

class PaymentException : public UniversitySystemException {
public:
    PaymentException(string msg) : UniversitySystemException("Payment Error: " + msg) {}
};

//  PERSON AND DERIVED CLASSES 
class Person {
protected:
    string name;
    int age;
    string ID;
    string contactInfo;

public:
    Person(string name, int age, string ID, string contactInfo) {
        if (age <= 0 || age > 120) throw UniversitySystemException("Invalid age: " + to_string(age));
        if (ID.empty()) throw UniversitySystemException("ID cannot be empty.");
        if (contactInfo.find("@") == string::npos) throw UniversitySystemException("Invalid contact info format.");
        
        this->name = name;
        this->age = age;
        this->ID = ID;
        this->contactInfo = contactInfo;
    }

    virtual void displayDetails() const {
        cout << "Name: " << name << ", Age: " << age << ", ID: " << ID 
             << ", Contact: " << contactInfo << endl;
    }

    virtual double calculatePayment() const { return 0.0; }
};

class Student : public Person {
protected:
    string enrollmentDate;
    string program;
    float GPA;

public:
    Student(string name, int age, string ID, string contactInfo, string enrollmentDate, string program, float GPA)
        : Person(name, age, ID, contactInfo), enrollmentDate(enrollmentDate), program(program), GPA(GPA) {
        if (GPA < 0.0 || GPA > 4.0) throw UniversitySystemException("Invalid GPA: " + to_string(GPA));
    }

    void displayDetails() const override {
        Person::displayDetails();
        cout << "Enrollment Date: " << enrollmentDate 
             << ", Program: " << program << ", GPA: " << GPA << endl;
    }
};

class Professor : public Person {
protected:
    string department;
    int yearsOfService;

public:
    Professor(string name, int age, string ID, string contactInfo, string department, int yearsOfService)
        : Person(name, age, ID, contactInfo), department(department), yearsOfService(yearsOfService) {}

    virtual void displayDetails() const override {
        Person::displayDetails();
        cout << "Department: " << department << ", Years of Service: " << yearsOfService << endl;
    }

    virtual double calculatePayment() const override { return 60000.0 + yearsOfService * 1000; }
};

//  ENROLLMENT AND GRADEBOOK CLASSES 

class GradeBook {
private:
    vector<pair<string, float>> grades;

public:
    void addGrade(string studentID, float grade) {
        if (grade < 0.0 || grade > 100.0) throw GradeException("Invalid grade: " + to_string(grade));
        grades.push_back({studentID, grade});
    }
    
    float calculateAverageGrade() {
        if (grades.empty()) throw GradeException("No grades available to calculate average.");
        float sum = 0;
        for (const auto& entry : grades) {
            sum += entry.second;
        }
        return sum / grades.size();
    }
};

class EnrollmentManager {
private:
    vector<pair<string, string>> enrollments;
    int maxCapacity = 30;

public:
    void enrollStudent(string studentID, string courseCode) {
        if (enrollments.size() >= maxCapacity) throw EnrollmentException("Course " + courseCode + " is full.");
        enrollments.push_back({studentID, courseCode});
    }

    int getEnrollmentCount() { return enrollments.size(); }
};

//UNIVERSITY SYSTEM CLASS 

class UniversitySystem {
private:
    vector<Student> students;
    GradeBook gradeBook;
    EnrollmentManager enrollmentManager;

public:
    void enrollStudent(string studentID, string courseCode) {
        try {
            enrollmentManager.enrollStudent(studentID, courseCode);
            cout << "Student " << studentID << " enrolled in course " << courseCode << endl;
        } catch (const EnrollmentException& e) {
            cerr << e.what() << endl;
        }
    }

    void addGrade(string studentID, float grade) {
        try {
            gradeBook.addGrade(studentID, grade);
            cout << "Grade recorded for student " << studentID << endl;
        } catch (const GradeException& e) {
            cerr << e.what() << endl;
        }
    }

    void calculateAverageGrade() {
        try {
            cout << "Average Grade: " << gradeBook.calculateAverageGrade() << endl;
        } catch (const GradeException& e) {
            cerr << e.what() << endl;
        }
    }
};

int main() {
    try {
        UniversitySystem uniSystem;

        Student s1("Karan", 20, "S123", "karan@example.com", "2023-09-01", "Computer Science", 3.8);
        Student s2("Ram", 21, "S124", "ram@example.com", "2023-09-01", "Mathematics", 4.1); // Triggers GPA error

        uniSystem.enrollStudent("S123", "CS101");
        uniSystem.addGrade("S123", 95.5);
        uniSystem.calculateAverageGrade();

    } catch (const UniversitySystemException& e) {
        cerr << "System Error: " << e.what() << endl;
    } catch (const exception& e) {
        cerr << "General Error: " << e.what() << endl;
    }

    return 0;
}