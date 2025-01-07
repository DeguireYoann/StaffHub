/*

IFT1169 - TP3 A24 -

Auteur: Yoann Deguire - decembre 2024

Description:
Signature de la classe EmployeeController
------------
*/
#include <iostream>
#include <string>
#include <vector>
#include "manager.h"
#include "programmeur.h"

using namespace std;

#ifndef GESTIONNAIRE_EMPLOYES_H
#define GESTIONNAIRE_EMPLOYES_H

class EmployeeController : public Manager {
    vector<Manager> managers;
    vector<Programmer> programmeurs;


public:
    EmployeeController();
    EmployeeController(vector<Manager>& managers, vector<Programmer>& programmeurs);

    vector<Manager> getManagers();
    vector<Programmer> getProgrammeurs();

    void ajouterManager(const Manager& manager);
    void ajouterProgrammeur(const Programmer& programmeur);

    void supprimerManager(const string& lastName);
    void supprimerProgrammeur(const string& lastName);

    void ajouterProjetAuProg(const string& lastName, const string& projet);
    void supprimerProjetAuProg(const string& lastName, const string& projet);

    void ajouterProjetAuManager(const string& lastName, const string& projet);
    void supprimerProjetAuManager(const string& lastName, const string& projet);

    void ajouterProgAuManager(const string& lastName, const string& prog);
    void supprimerProgAuManager(const string& lastName, const string& prog);
    
    template <class T>
    void afficherProjetEmployes(const string& lastName, vector<T>& employes);
    string afficherProjetManager(const string& lastName);
    string afficherProjetProgrammeur(const string& lastName);

    string programmeurAssocier(const string& lastName);

    template <class T>
    T* chercherEmploye(const string& lastName, vector<T>& employes);
    Programmer* chercherProgrammeur(const string& lastName);
    Manager* chercherManager(const string& lastName);

    template <class T>
    string employesParProjet(const string& projet, vector<T>& employes);
    string managerParProjet(const string& projet);
    string programmeurParProjet(const string& projet);

    string managerDuProgrammeur(const string& lastName);

   ~EmployeeController();
};
#endif