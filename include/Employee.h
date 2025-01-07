/*

Author: Yoann Deguire - December 2024

Description:
Employee Class Signature
------------
*/
#include <iostream>
#include <string>

using namespace std;

#ifndef EMPLOYEE_H
#define EMPLOYEE_H

class Employee {
protected:
/*
 Private properties
*/
    string lastName, firstName;
    int salary;
    int age;

public:
/*
 Public methods of the Employee class
*/

    /*
        Class constructor
        - Default constructor
        - Constructor with property assignment
        - Copy constructor
    */
    Employee();
    Employee(string lastName, string firstName, int salary, int age);
    Employee(const Employee& otherEmployee);

    /*
        Getter methods
    */
    const string getLastName();
    const string getLastName() const;
    const string getFirstName();
    const string getFirstName() const;
    const int getSalary();
    const int getSalary() const;
    const int getAge();
    const int getAge() const;

    /*
        Setter methods
    */
    void setLastName(string lastName);
    void setFirstName(string firstName);

    /*
        Operator overloading
    */
    bool operator==(Employee& otherEmployee);
    bool operator!=(Employee& otherEmployee);
    bool operator<(const Employee& otherEmployee);
    
    Employee& operator=(const Employee& otherEmployee);
    string& operator+=(string& result);
    friend ostream& operator<<(ostream&, const Employee&);

    // Destructor
    ~Employee();
};
#endif
