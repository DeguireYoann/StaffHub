/*

IFT1169 - TP3 A24 -

Author: Yoann Deguire - December 2024

Description:
FileReader class to parse CSV files and construct Programmer & Manager objects.
------------
*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "FileReader.h"

using namespace std;

FileReader::FileReader() {}

string FileReader::getProgrammerFilePath() {
    return programmerFilePath;
}

string FileReader::getManagerFilePath() {
    return managerFilePath;
}

void FileReader::setProgrammerFilePath(const string& fileName) {
    if(fileName != programmerFilePath)
        programmerFilePath = fileName;
}

void FileReader::setManagerFilePath(const string& fileName) {
    if(fileName != managerFilePath)
        managerFilePath = fileName;
}

bool FileReader::validateFile(const string& fileName, const string header[7]) {
    ifstream file(fileName);

    if (!file.is_open()) {
        cerr << "Error: Unable to open the file." << endl;
        return false;
    }

    string line;

    // Read the first line
    if (getline(file, line)) {
        stringstream ss(line);
        string value;
        int fields = 0;

        // Header validation
        while (getline(ss, value, ';')) {
            if (fields >= 7 || value != header[fields]) {
                cerr << "Error: Invalid header - Field " << fields + 1
                     << " expected: " << header[fields] 
                     << ", found: " << value << endl;
                return false;
            }
            fields++;
        }

        // Check if all expected fields are present
        if (fields != 7) {
            cerr << "Error: The header does not contain the correct number of fields." << endl;
            return false;
        }
    } else {
        cerr << "Error: The file is empty or cannot be read." << endl;
        return false;
    }

    file.close();
    return true;
}

bool FileReader::validateFiles() {    
    const bool isManagerFileValid = this->validateFile(managerFilePath, managerHeader);
    const bool isProgrammerFileValid = this->validateFile(programmerFilePath, programmerHeader);

    return isManagerFileValid && isProgrammerFileValid;
}

/*
    Read the manager data file and add the managers to a vector passed as a parameter.
*/
void FileReader::readManagerFile(vector<Manager>& managers)
{
    ifstream file(managerFilePath);
    if (!file.is_open()) {
        return;
    }

    string line;
    getline(file, line);

    while (getline(file, line)) {
        string lastName = "", firstName = "", language = "", team = "", projects = "";
        int age = 0, salary = 0, budget = 0;

        // Extract values for variables
        stringstream stream(line);
        getline(stream, lastName, ';');
        getline(stream, firstName, ';');
        stream >> age;
        stream.ignore();
        stream >> salary;
        stream.ignore();
        getline(stream, team, ';');
        stream >> budget;
        stream.ignore();
        getline(stream, projects);

        // Create an object with a constructor
        managers.push_back(Manager(lastName, firstName, salary, age, budget, team, projects));
    }

    file.close();
}

void FileReader::writeManagerFile(const vector<Manager>& managers)
{
    ofstream file(managerFilePath);
    if (!file.is_open()) {
        return;
    }

    // File header
    for (int i = 0; i < 7; ++i) {
        file << managerHeader[i];
        if (i < 6) file << ";"; // Separate with ;
    }
    file << endl;

    // Iterate through managers and write data
    for (const auto& manager : managers) {
        file << manager.getLastName() << ";"
             << manager.getFirstName() << ";"
             << manager.getAge() << ";"
             << manager.getSalary() << ";"
             << manager.getTeam() << ";"
             << manager.getBudget() << ";"
             << manager.getProjects() << endl;
    }

    file.close();
}

/*
    Process each line of a file according to the path, create a Programmer object from each row, and add it to a vector passed as a parameter.
*/
void FileReader::readProgrammerFile(vector<Programmer>& programmers)
{
    ifstream file(programmerFilePath);
    if (!file.is_open()) {
        return;
    }

    string line;
    getline(file, line);

    while (getline(file, line)) {
        string lastName = "", firstName = "", language = "", experience = "", projects = "";
        int age = 0, salary = 0;

        // Extract values for variables
        stringstream stream(line);
        getline(stream, lastName, ';');
        getline(stream, firstName, ';');
        stream >> age;
        stream.ignore();
        stream >> salary;
        stream.ignore();
        getline(stream, language, ';');
        getline(stream, experience, ';');
        getline(stream, projects);

        // Create an object with a constructor
        programmers.push_back(Programmer(lastName, firstName, age, salary, language, experience, projects));
    }

    file.close();
}

void FileReader::writeProgrammerFile(const vector<Programmer>& programmers)
{
    ofstream file(programmerFilePath);
    if (!file.is_open()) {
        return;
    }

    // File header
    for (int i = 0; i < 7; ++i) {
        file << programmerHeader[i];
        if (i < 6) file << ";"; // Separate with ;
    }
    file << endl;

    // Iterate through programmers and write data
    for (const auto& programmer : programmers) {
        file << programmer.getLastName() << ";"
             << programmer.getFirstName() << ";"
             << programmer.getAge() << ";"
             << programmer.getSalary() << ";"
             << programmer.getLanguage() << ";"
             << programmer.getExperience() << ";"
             << programmer.getProjects() << endl;
    }

    file.close();
}

FileReader::~FileReader() {}
