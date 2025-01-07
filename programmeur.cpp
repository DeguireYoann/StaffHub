/*

IFT1169 - TP3 A24 -

Auteur: Yoann Deguire - decembre 2024

Description:
------------
*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "programmeur.h"

using namespace std;
/*
 Les méthodes de Programmeur
 */

/*
    Constructeur de la classe
    - Constructeur vide
    - Constructeur avec assignation des propriétés
    - Constructeur de recopie
*/
Programmeur::Programmeur() 
    : Employe(), experience(""), langage(""), projets("") {}

Programmeur::Programmeur(string nom, string prenom, int age, int salaire, string langage, string experience, string projets)
    : Employe(nom, prenom, salaire, age), experience(experience), langage(langage), projets(projets) {}

Programmeur::Programmeur(const Programmeur& autreProgrammeur)
    : Employe(autreProgrammeur), experience(autreProgrammeur.experience), langage(autreProgrammeur.langage), projets(autreProgrammeur.projets) {}

/*
    Surchage des opérateurs
*/
Programmeur& Programmeur::operator=(const Programmeur& autreProgrammeur) {
    if (this != &autreProgrammeur) {
        Employe::operator=(autreProgrammeur);
        experience = autreProgrammeur.experience;
        langage = autreProgrammeur.langage;
        projets = autreProgrammeur.projets;
    }
    return *this;
}

/*
    Getter et Setter des propriétées privées
*/
string Programmeur::getProjets() const {
    return projets;
}

string Programmeur::getLangage() const {
    return langage;
}
string Programmeur::getExperience() const {
    return experience;
}

void Programmeur::setProjets(string projets) {
    this->projets = projets;
}

Programmeur::~Programmeur() {}
