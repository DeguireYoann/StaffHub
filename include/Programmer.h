/*



Auteur: Yoann Deguire

Description:
Signature de la classe Programmer
------------
*/
#include <iostream>
#include <string>
#include "Employee.h"

using namespace std;

#ifndef PROGRAMMEUR_H
#define PROGRAMMEUR_H

class Programmer : public Employee {
    string experience;
    string language;
    string projects;

public:
    Programmer();

    Programmer(string lastName, string firstName, int age, int salary,  string language, string experience, string projects);
    Programmer(const Programmer& otherProgrammer);
    Programmer& operator=(const Programmer& otherProgrammer);
    
    string getProjects() const;
    string getLanguage() const;
    string getExperience() const;

    void setProjects(string projects);

    ~Programmer();
};
#endif