/*

IFT1169 - TP3 A24 -

Auteur: Yoann Deguire - decembre 2024

Description:
Classe Manager dérivée de la classe Employee
------------
*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "Manager.h"

using namespace std;

/*
 Les méthodes de Manager
 */

/*
    Constructeur de la classe
    - Constructeur vide
    - Constructeur avec assignation des propriétés
    - Constructeur de recopie
*/
Manager::Manager()
    : Employee(), budget(0), team(""), projects("") {}

Manager::Manager(string lastName, string firstName, int salary, int age, int budget, string team, string projects)
    : Employee(lastName, firstName, salary, age), budget(budget), team(team), projects(projects) {}

Manager::Manager(const Manager& otherManager)
    : Employee(otherManager), budget(otherManager.budget), team(otherManager.team), projects(otherManager.projects) {}


/*
    Surchage des opérateurs
*/
Manager& Manager::operator=(const Manager& otherManager) {
    if (this != &otherManager) {
        Employee::operator=(otherManager);
        budget = otherManager.budget;
        team = otherManager.team;
        projects = otherManager.projects;
    }
    return *this;
}

Manager& Manager::operator=(const Manager&& otherManager) {
    if (this != &otherManager) {
        Employee::operator=(otherManager);
        budget = otherManager.budget;
        team = otherManager.team;
        projects = otherManager.projects;
    }
    return *this;
}

/*
    Getter et Setter
*/
string Manager::getProjects() const {
    return projects;
}

string Manager::getTeam() const {
    return team;
}

int Manager::getBudget() const {
    return budget;
}

void Manager::setProjects(string projects) {
    this->projects = projects;
}

void Manager::setTeam(string team) {
    this->team = team;
}

Manager::~Manager() {}
