/*

IFT1169 - TP3 A24 -

Auteur: Yoann Deguire - decembre 2024

Description:
Signature de la classe GestionnaireEmployes
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

class GestionnaireEmployes : public Manager {
    vector<Manager> managers;
    vector<Programmeur> programmeurs;


public:
    GestionnaireEmployes();
    GestionnaireEmployes(vector<Manager>& managers, vector<Programmeur>& programmeurs);

    vector<Manager> getManagers();
    vector<Programmeur> getProgrammeurs();

    void ajouterManager(const Manager& manager);
    void ajouterProgrammeur(const Programmeur& programmeur);

    void supprimerManager(const string& nom);
    void supprimerProgrammeur(const string& nom);

    void ajouterProjetAuProg(const string& nom, const string& projet);
    void supprimerProjetAuProg(const string& nom, const string& projet);

    void ajouterProjetAuManager(const string& nom, const string& projet);
    void supprimerProjetAuManager(const string& nom, const string& projet);

    void ajouterProgAuManager(const string& nom, const string& prog);
    void supprimerProgAuManager(const string& nom, const string& prog);
    
    template <class T>
    void afficherProjetEmployes(const string& nom, vector<T>& employes);
    string afficherProjetManager(const string& nom);
    string afficherProjetProgrammeur(const string& nom);

    string programmeurAssocier(const string& nom);

    template <class T>
    T* chercherEmploye(const string& nom, vector<T>& employes);
    Programmeur* chercherProgrammeur(const string& nom);
    Manager* chercherManager(const string& nom);

    template <class T>
    string employesParProjet(const string& projet, vector<T>& employes);
    string managerParProjet(const string& projet);
    string programmeurParProjet(const string& projet);

    string managerDuProgrammeur(const string& nom);

   ~GestionnaireEmployes();
};
#endif