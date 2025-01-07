/*

Author: Yoann Deguire - December 2024

Description:

Employee Class

------------
*/
#include <iostream>
#include <string>
#include <format>
#include "Employee.h"

using namespace std;
/*
 Employee class methods
*/

/*
    Class constructor
    - Default constructor
    - Constructor with property assignment
    - Copy constructor
*/
Employee::Employee()
    : lastName(""), firstName(""), salary(0), age(0) {}

Employee::Employee(string lastName, string firstName, int salary, int age)
    : lastName(lastName), firstName(firstName), salary(salary), age(age) {}

Employee::Employee(const Employee& otherEmployee) 
    : lastName(otherEmployee.lastName), firstName(otherEmployee.firstName), salary(otherEmployee.salary), age(otherEmployee.age) {}

Employee& Employee::operator=(const Employee& otherEmployee) {
    if (this != &otherEmployee) {
        lastName = otherEmployee.lastName;
        firstName = otherEmployee.firstName;
        salary = otherEmployee.salary;
        age = otherEmployee.age;
    }
    return *this;
}


/*
    Getter
*/
const string Employee::getLastName() {
    return this->lastName;
}

const string Employee::getLastName() const {
    return this->lastName;
}

const string Employee::getFirstName() {
    return this->firstName;
}

const string Employee::getFirstName() const {
    return this->firstName;
}

const int Employee::getSalary() {
    return this->salary;
}

const int Employee::getSalary() const {
    return this->salary;
}

const int Employee::getAge() {
    return this->age;
}

const int Employee::getAge() const {
    return this->age;
}


/*
    Setter
*/
    void Employee::setLastName(string lastName) {
        this->lastName = lastName;
    }

    void Employee::setFirstName(string firstName) {
        this->firstName = firstName;
    }


/*
    Operator overloading
*/
bool Employee::operator==(Employee& otherEmployee) {
    return this->lastName == otherEmployee.getLastName()
        && this->firstName == otherEmployee.getFirstName()
        && this->salary == otherEmployee.getSalary()
        && this->age == otherEmployee.getAge();
}

bool Employee::operator!=(Employee& otherEmployee) {
    return !(*this == otherEmployee);
}

bool Employee::operator<(const Employee& otherEmployee) {
    return this->lastName < otherEmployee.lastName;
}

ostream& operator<<(ostream& os, const Employee& employer) {
    // Using format to modify the display format
    string output = format("**{} {}**", employer.firstName, employer.lastName);
    return os << output;
}

Employee::~Employee() {}