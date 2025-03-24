/*



Auteur: Yoann Deguire

Description:
Signature de la classe Manager
------------
*/
#include <iostream>
#include <string>
#include "Employee.h"

using namespace std;

#ifndef MANAGER_H
#define MANAGER_H

class Manager : public Employee {
    int budget;
    string team;
    string projects;

public:
    Manager();

    Manager(string lastName, string firstName, int salary, int age, int budget, string team, string projects);
    Manager(const Manager& otherManager);
    Manager& operator=(const Manager& otherManager);
    Manager& operator=(const Manager&& otherManager);
    
    string getProjects() const;
    string getTeam() const;
    int getBudget() const;

    void setProjects(string projects);
    void setTeam(string team);

    ~Manager();
};

#endif