//
// Author: Yoann Deguire - December 2024
//
// Description:
// ------------
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <format>
#include "/EmployeeController.h"
#include "/Manager.h"
#include "/Programmer.h"
#include "StringUtility.h"

using namespace std;

// Methods of EmployeeController

// Constructors of EmployeeController
EmployeeController::EmployeeController() : managers(), programmers() {}

EmployeeController::EmployeeController(vector<Manager>& managers, vector<Programmer>& programmers)
    : managers(managers), programmers(programmers) {}

// Getters
vector<Manager> EmployeeController::getManagers() {
    return this->managers;
}

vector<Programmer> EmployeeController::getProgrammers() {
    return this->programmers;
}

// Add a manager by reference to the end of the list
void EmployeeController::addManager(const Manager& manager) {
    this->managers.push_back(manager);
}

// Remove a manager by lastName; iterate through the list and remove if found
void EmployeeController::removeManager(const string& lastName) {
    for (auto it = this->managers.begin(); it != this->managers.end(); ++it) {
        if (it->getLastName() == lastName) {
            this->managers.erase(it);
            break;
        }
    }
    cout << "Manager " << lastName << " not found." << endl;
}

// Add a programmer by reference to the end of the list
void EmployeeController::addProgrammer(const Programmer& programmer) {
    this->programmers.push_back(programmer);
}

// Remove a programmer by lastName; iterate through the list and remove if found
void EmployeeController::removeProgrammer(const string& lastName) {
    for (auto it = this->programmers.begin(); it != this->programmers.end(); ++it) {
        if (it->getLastName() == lastName) {
            this->programmers.erase(it);
            break;
        }
    }
    cout << "Programmer " << lastName << " not found." << endl;
}

// Search for an employee by lastName in a dynamic vector using a template
template <class T>
T* EmployeeController::findEmployee(const string& lastName, vector<T>& employees) {
    for (auto& employee : employees) {
        if (employee.getLastName() == lastName) {
            return &employee;
        }
    }
    return nullptr;
}

// Find a programmer by lastName using findEmployee
Programmer* EmployeeController::findProgrammer(const string& lastName) {
    return this->findEmployee(lastName, this->programmers);
}

// Find a manager by lastName using findEmployee
Manager* EmployeeController::findManager(const string& lastName) {
    return this->findEmployee(lastName, this->managers);
}

// Add a project to a programmer
void EmployeeController::addProjectToProgrammer(const string& lastName, const string& project) {
    Programmer* programmer = findProgrammer(lastName);

    if (programmer == nullptr) {
        cout << "Programmer " << lastName << " not found." << endl;
        return;
    }

    StringUtility stringUtility;
    string projects = programmer->getProjects();

    programmer->setProjects(stringUtility.addWord(projects, project));
}

// Remove a project from a programmer
void EmployeeController::removeProjectFromProgrammer(const string& lastName, const string& project) {
    Programmer* programmer = findProgrammer(lastName);

    if (programmer == nullptr) {
        cout << "Programmer " << lastName << " not found." << endl;
        return;
    }

    StringUtility stringUtility;
    string projects = programmer->getProjects();

    programmer->setProjects(stringUtility.removeWord(projects, project));
}

// Add a project to a manager
void EmployeeController::addProjectToManager(const string& lastName, const string& project) {
    Manager* manager = findManager(lastName);

    if (manager == nullptr) {
        cout << "Manager " << lastName << " not found." << endl;
        return;
    }

    StringUtility stringUtility;
    string projects = manager->getProjects();

    manager->setProjects(stringUtility.addWord(projects, project));
}

// Remove a project from a manager
void EmployeeController::removeProjectFromManager(const string& lastName, const string& project) {
    Manager* manager = findManager(lastName);

    if (manager == nullptr) {
        cout << "Manager " << lastName << " not found." << endl;
        return;
    }

    StringUtility stringUtility;
    string projects = manager->getProjects();

    manager->setProjects(stringUtility.removeWord(projects, project));
}

// Add a programmer to a manager's team
void EmployeeController::addProgrammerToManager(const string& lastName, const string& programmerName) {
    Manager* manager = findManager(lastName);

    if (manager == nullptr) {
        cout << "Manager " << lastName << " not found." << endl;
        return;
    }

    StringUtility stringUtility;
    string team = manager->getTeam();

    manager->setTeam(stringUtility.addWord(team, programmerName));
}

// Remove a programmer from a manager's team
void EmployeeController::removeProgrammerFromManager(const string& lastName, const string& programmerName) {
    Manager* manager = findManager(lastName);

    if (manager == nullptr) {
        cout << "Manager " << lastName << " not found." << endl;
        return;
    }

    StringUtility stringUtility;
    string team = manager->getTeam();

    manager->setTeam(stringUtility.removeWord(team, programmerName));
}

// Display a manager's projects
string EmployeeController::displayManagerProjects(const string& lastName) {
    Manager* manager = findManager(lastName);
    string result = "";

    if (manager == nullptr) {
        cout << "Manager " << lastName << " not found." << endl;
        return result;
    }

    string foundProjects = manager->getProjects();

    if (!foundProjects.empty()) {
        StringUtility stringUtility;
        result += stringUtility.buildOutput(foundProjects);
    } else {
        result += "No projects found.";
    }
    return result;
}

// Display a programmer's projects
string EmployeeController::displayProgrammerProjects(const string& lastName) {
    Programmer* programmer = findProgrammer(lastName);
    string result = "";

    if (programmer == nullptr) {
        cout << "Programmer " << lastName << " not found." << endl;
        return result;
    }

    string foundProjects = programmer->getProjects();

    if (!foundProjects.empty()) {
        StringUtility stringUtility;
        result += stringUtility.buildOutput(foundProjects);
    } else {
        result += "No projects found.";
    }
    return result;
}

// Template function to find employees associated with a given project
template <class T>
string EmployeeController::employeesByProject(const string& project, vector<T>& employees) {
    vector<T> foundEmployees;
    string result = "";

    for (const auto& employee : employees) {
        if (employee.getProjects().find(project) != string::npos) {
            foundEmployees.push_back(employee);
        }
    }

    if (foundEmployees.empty()) {
        result += "No employees found.";
        return result;
    }

    for (auto& employee : foundEmployees) {
        result += employee.getFirstName() + " " + employee.getLastName();

        if (employee != foundEmployees.back()) {
            result += ", ";
        }
    }
    return result;
}

// Find programmers associated with a project
string EmployeeController::programmersByProject(const string& project) {
    return employeesByProject(project, this->programmers);
}

// Find managers associated with a project
string EmployeeController::managersByProject(const string& project) {
    return employeesByProject(project, this->managers);
}

// Display the team associated with a manager by lastName
string EmployeeController::associatedProgrammers(const string& lastName) {
    Manager* manager = findManager(lastName);
    string result = "";

    if (manager == nullptr) {
        result += "Manager " + lastName + " not found.";
        return result;
    }

    const string& team = manager->getTeam();
    stringstream stream(team);
    string programmerName;
    int foundCount = 0;

    while (getline(stream, programmerName, ',')) {
        if (programmerName.empty()) {
            continue;
        }

        Programmer* programmer = this->findProgrammer(programmerName);
        if (programmer == nullptr) {
            continue;
        }

        if (foundCount > 0) {
            result += ", ";
        }
        result += programmer->getFirstName() + " " + programmer->getLastName();
        foundCount++;
    }

    if (foundCount == 0) {
        result += "****";
    }
    return result;
}

// Function to find the manager of a programmer by looping through the manager list
string EmployeeController::managerOfProgrammer(const string& lastName) {
    for (auto& manager : this->managers) {
        if (manager.getTeam().find(lastName) != string::npos) {
            return manager.getFirstName() + " " + manager.getLastName();
        }
    }
    return "No manager found.";
}

EmployeeController::~EmployeeController() {}
