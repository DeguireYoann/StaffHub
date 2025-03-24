/*



Auteur: Yoann Deguire

Description:
EmployeeController class signature
------------
*/
#include <iostream>
#include <string>
#include <vector>
#include "Manager.h"
#include "Programmer.h"

using namespace std;

#ifndef EMPLOYEE_CONTROLLER_H
#define EMPLOYEE_CONTROLLER_H

class EmployeeController : public Manager {
    vector<Manager> managers;
    vector<Programmer> programmers;


public:
    EmployeeController();
    EmployeeController(vector<Manager>& managers, vector<Programmer>& programmers);

    vector<Manager> getManagers();
    vector<Programmer> getProgrammers();

    void addManager(const Manager& manager);
    void addProgrammer(const Programmer& programmer);

    void removeManager(const string& lastName);
    void removeProgrammer(const string& lastName);

    void addProjectToProgrammer(const string& lastName, const string& project);
    void removeProjectFromProgrammer(const string& lastName, const string& project);

    void addProjectToManager(const string& lastName, const string& project);
    void removeProjectFromManager(const string& lastName, const string& project);

    void addProgrammerToManager(const string& lastName, const string& prog);
    void removeProgrammerFromManager(const string& lastName, const string& prog);
    
    template <class T>
    void displayProjectEmployee(const string& lastName, vector<T>& employes);
    string displayManagerProjects(const string& lastName);
    string displayProgrammerProjects(const string& lastName);

    string associatedProgrammers(const string& lastName);

    template <class T>
    T* findEmployee(const string& lastName, vector<T>& employes);
    Programmer* findProgrammer(const string& lastName);
    Manager* findManager(const string& lastName);

    template <class T>
    string employeesByProject(const string& project, vector<T>& employes);
    string managersByProject(const string& project);
    string programmersByProject(const string& project);

    string managerOfProgrammer(const string& lastName);

   ~EmployeeController();
};
#endif