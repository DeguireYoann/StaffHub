/*



Auteur: Yoann Deguire

Description:
------------
*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "Programmer.h"

using namespace std;
/*
 Les méthodes de Programmer
 */

/*
    Constructeur de la classe
    - Constructeur vide
    - Constructeur avec assignation des propriétés
    - Constructeur de recopie
*/
Programmer::Programmer() 
    : Employee(), experience(""), language(""), projects("") {}

Programmer::Programmer(string lastName, string firstName, int age, int salary, string language, string experience, string projects)
    : Employee(lastName, firstName, salary, age), experience(experience), language(language), projects(projects) {}

Programmer::Programmer(const Programmer& otherProgrammer)
    : Employee(otherProgrammer), experience(otherProgrammer.experience), language(otherProgrammer.language), projects(otherProgrammer.projects) {}

/*
    Surchage des opérateurs
*/
Programmer& Programmer::operator=(const Programmer& otherProgrammer) {
    if (this != &otherProgrammer) {
        Employee::operator=(otherProgrammer);
        experience = otherProgrammer.experience;
        language = otherProgrammer.language;
        projects = otherProgrammer.projects;
    }
    return *this;
}

/*
    Getter et Setter des propriétées privées
*/
string Programmer::getProjects() const {
    return projects;
}

string Programmer::getLanguage() const {
    return language;
}
string Programmer::getExperience() const {
    return experience;
}

void Programmer::setProjects(string projects) {
    this->projects = projects;
}

Programmer::~Programmer() {}
