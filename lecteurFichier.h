/*

IFT1169 - TP3 A24 -

Auteur: Yoann Deguire - decembre 2024

Description:
Signature de la classe LecteurFichier
------------
*/
#include <iostream>
#include <string>
#include <vector>
#include "programmeur.h"
#include "manager.h"

using namespace std;

#ifndef LECTEUR_FICHIER_H
#define LECTEUR_FICHIER_H

class LecteurFichier {
    string routeFichierProg = "";
    string routeFichierManager = "";
    string enTeteManager[7] = {"Nom", "Prenom", "Age", "Salaire", "Equipe", "Budget", "Projets Supervises"};
    string enTeteProg[7] = {"Nom", "Prenom", "Age", "Salaire", "Langage de Programmation", "Niveau d'Experience", "Projets en Cours"};
public:
    LecteurFichier();

    string getRouteFichierProg();
    string getRouteFichierManager();

    void setRouteFichierProg(const string& nomFichier);
    void setRouteFichierManager(const string& nomFichier);

    bool validerFichier(const string& nomFichier, const string enTete[7]);
    bool validerFichiers();

    void lireFichierManager(vector<Manager>& managers);
    void ecrireFichierManager(const vector<Manager>& managers);

    void lireFichierProgrammeur(vector<Programmeur>& programmeurs);
    void ecrireFichierProgrammeur(const vector<Programmeur>& programmeurs);
    ~LecteurFichier();
};

#endif