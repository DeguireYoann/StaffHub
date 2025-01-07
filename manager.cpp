/*

IFT1169 - TP3 A24 -

Auteur: Yoann Deguire - decembre 2024

Description:
Classe Manager dérivée de la classe Employe
------------
*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "manager.h"

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
    : Employe(), budget(0), equipe(""), projets("") {}

Manager::Manager(string nom, string prenom, int salaire, int age, int budget, string equipe, string projets)
    : Employe(nom, prenom, salaire, age), budget(budget), equipe(equipe), projets(projets) {}

Manager::Manager(const Manager& autreManager)
    : Employe(autreManager), budget(autreManager.budget), equipe(autreManager.equipe), projets(autreManager.projets) {}


/*
    Surchage des opérateurs
*/
Manager& Manager::operator=(const Manager& autreManager) {
    if (this != &autreManager) {
        Employe::operator=(autreManager);
        budget = autreManager.budget;
        equipe = autreManager.equipe;
        projets = autreManager.projets;
    }
    return *this;
}

Manager& Manager::operator=(const Manager&& autreManager) {
    if (this != &autreManager) {
        Employe::operator=(autreManager);
        budget = autreManager.budget;
        equipe = autreManager.equipe;
        projets = autreManager.projets;
    }
    return *this;
}

/*
    Getter et Setter
*/
string Manager::getProjets() const {
    return projets;
}

string Manager::getEquipe() const {
    return equipe;
}

int Manager::getBudget() const {
    return budget;
}

void Manager::setProjets(string projets) {
    this->projets = projets;
}

void Manager::setEquipe(string equipe) {
    this->equipe = equipe;
}

Manager::~Manager() {}
