/*

IFT1169 - TP3 A24 -

Auteur: Yoann Deguire - decembre 2024

Description:
Signature de la classe Manager
------------
*/
#include <iostream>
#include <string>
#include "employe.h"

using namespace std;

#ifndef MANAGER_H
#define MANAGER_H

class Manager : public Employe {
    int budget;
    string equipe;
    string projets;

public:
    Manager();

    Manager(string nom, string prenom, int salaire, int age, int budget, string equipe, string projets);
    Manager(const Manager& autreManager);
    Manager& operator=(const Manager& autreManager);
    Manager& operator=(const Manager&& autreManager);
    
    string getProjets() const;
    string getEquipe() const;
    int getBudget() const;

    void setProjets(string projets);
    void setEquipe(string equipe);

    ~Manager();
};

#endif