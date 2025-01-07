/*

IFT1169 - TP3 A24 -

Auteur: Yoann Deguire - decembre 2024

Description:
Signature de la classe Programmeur
------------
*/
#include <iostream>
#include <string>
#include "employe.h"

using namespace std;

#ifndef PROGRAMMEUR_H
#define PROGRAMMEUR_H

class Programmeur : public Employe {
    string experience;
    string langage;
    string projets;

public:
    Programmeur();

    Programmeur(string nom, string prenom, int age, int salaire,  string langage, string experience, string projets);
    Programmeur(const Programmeur& autreProgrammeur);
    Programmeur& operator=(const Programmeur& autreProgrammeur);
    
    string getProjets() const;
    string getLangage() const;
    string getExperience() const;

    void setProjets(string projets);

    ~Programmeur();
};
#endif