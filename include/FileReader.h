/*



Auteur: Yoann Deguire

Description:
FileReader class signature
------------
*/
#include <iostream>
#include <string>
#include <vector>
#include "Programmer.h"
#include "Manager.h"

using namespace std;

#ifndef LECTEUR_FICHIER_H
#define LECTEUR_FICHIER_H

class LecteurFichier {
    string routeFichierProg = "";
    string routeFichierManager = "";

    string enTeteManager[7] = {"LastName", "FirstNAme", "Age", "Salary", "Team", "Budget", "Supervised projects"};
    string enTeteProg[7] = {"LastName", "FirstName", "Age", "Salary", "Programmation Language", "Experience Level", "Working Projects"};
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

    void lireFichierProgrammeur(vector<Programmer>& programmeurs);
    void ecrireFichierProgrammeur(const vector<Programmer>& programmeurs);
    ~LecteurFichier();
};

#endif