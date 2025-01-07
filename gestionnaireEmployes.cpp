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
#include <format>
#include "GestionnaireEmployes.h"
#include "manager.h"
#include "programmeur.h"
#include "stringManager.h"

using namespace std;

/*
 Les méthodes de GestionnaireEmployes
 */


/*
 Les Constructeur de GestionnaireEmployes
 */

GestionnaireEmployes::GestionnaireEmployes()
    :managers(), programmeurs() {}

GestionnaireEmployes::GestionnaireEmployes(vector<Manager>& managers, vector<Programmeur>& programmeurs)
    :managers(managers), programmeurs(programmeurs) {}


/* GETTER */
vector<Manager> GestionnaireEmployes::getManagers() {
    return this->managers;
}

vector<Programmeur> GestionnaireEmployes::getProgrammeurs() {
    return this->programmeurs;
}

// Ajouter un manager par référence dans le vector à la fin de la liste
void GestionnaireEmployes::ajouterManager(const Manager& manager) {
    this->managers.push_back(manager);
}

// Supprimer un manager par nom, on boucle dans la liste et supprime si on trouve manager
void GestionnaireEmployes::supprimerManager(const string& nom) {
    for (auto it = this->managers.begin(); it != this->managers.end(); ++it) {
        if (it->getNom() == nom) {
            this->managers.erase(it);
            break;
        }
    }
    cout << "Manager " << nom << " introuvable." << endl;
}

// Ajouter un programmeur par référence dans le vector à la fin de la liste
void GestionnaireEmployes::ajouterProgrammeur(const Programmeur& programmeur) {
    this->programmeurs.push_back(programmeur);
}

// Supprimer un programmeur par nom, on boucle dans la liste et supprime si on trouve le programmeur
void GestionnaireEmployes::supprimerProgrammeur(const string& nom) {
    for (auto it = this->programmeurs.begin(); it != this->programmeurs.end(); ++it) {
        if (it->getNom() == nom) {
            this->programmeurs.erase(it);
            break;
        }
    }
    cout << "Programmeur " << nom << " introuvable." << endl;
}

// Rechercher un employé par nom dans un vector de type dynamic avec le template T
template <class T>
T* GestionnaireEmployes::chercherEmploye(const string& nom, vector<T>& employes) {
    // on boucle dans chaque élément du vector
    for (auto& employe : employes) {
        if (employe.getNom() == nom) {
            return &employe;
        }
    }
    return nullptr;
}

// Rechercher un programmeur par nom avec la fonction chercherEmploye
Programmeur* GestionnaireEmployes::chercherProgrammeur(const string& nom) {
    return this->chercherEmploye(nom, this->programmeurs);
}

// Rechercher un manager par nom avec la fonction chercherEmploye
Manager* GestionnaireEmployes::chercherManager(const string& nom) {
    return this->chercherEmploye(nom, this->managers);
}

/*
    Ajouter un projet a un programmeur
    - on cherche l'employe
    - on valide si l'a trouver
    - on get les projets et on utilise le stringManger pour ajouter un mot et on l'affecte au projet
*/
void GestionnaireEmployes::ajouterProjetAuProg(const string& nom, const string& projet) {
    Programmeur* programmeur = chercherProgrammeur(nom);

    if (programmeur == nullptr) {
        cout << "programmeur " << nom << " non trouvé." << endl;
        return;
    }

    StringManager stringManager;
    string projets = programmeur->getProjets();

    programmeur->setProjets(stringManager.ajouterMot(projets, projet));
}

/*
    Supprimer un projet a un programmeur
    - on cherche l'employe
    - on valide si l'a trouver
    - on get les projets et on utilise le stringManger pour retier un mot dans le string et on l'affecte au projet
*/
void GestionnaireEmployes::supprimerProjetAuProg(const string& nom, const string& projet) {
    Programmeur* programmeur = chercherProgrammeur(nom);

    if (programmeur == nullptr) {
        cout << "programmeur " << nom << " non trouvé." << endl;
        return;
    }
    
    StringManager stringManager;
    string projets = programmeur->getProjets();

    programmeur->setProjets(stringManager.retirerMot(projets, projet));
}

/*
    Ajouter un projet a un manager
    - on cherche l'employe
    - on valide si l'a trouver
    - on get les projets et on utilise le stringManger pour ajouter un mot et on l'affecte au projet
*/
void GestionnaireEmployes::ajouterProjetAuManager(const string& nom, const string& projet) {
    Manager* manager = chercherManager(nom);

    if (manager == nullptr) {
        cout << "Manager " << nom << " non trouvé." << endl;
        return;
    }

    StringManager stringManager;
    string projets = manager->getProjets();

    manager->setProjets(stringManager.ajouterMot(projets, projet));
}

/*
    Supprimer un projet a un manager
    - on cherche l'employe
    - on valide si l'a trouver
    - on get les projets et on utilise le stringManger pour retier un mot dans le string et on l'affecte au projet
*/
void GestionnaireEmployes::supprimerProjetAuManager(const string& nom, const string& projet) {
    Manager* manager = chercherManager(nom);

    if (manager == nullptr) {
        cout << "Manager " << nom << " non trouvé." << endl;
        return;
    }
    
    string projets = manager->getProjets();
    StringManager stringManager;
    manager->setProjets(stringManager.retirerMot(projets, projet));
}

/*
    Ajouter un programmeur a l'équipe d'un manager
    - on cherche l'employe
    - on valide si l'a trouver
    - on get l'équipe et on utilise le stringManger pour ajouter un nom au string et on l'affecte a l'équipe
*/
void GestionnaireEmployes::ajouterProgAuManager(const string& nom, const string& prog) {
    Manager* manager = chercherManager(nom);

    if (manager == nullptr) {
        cout << "Manager " << nom << " non trouvé." << endl;
        return;
    }
    
    StringManager stringManager;
    string equipe = manager->getEquipe();

    manager->setEquipe(stringManager.ajouterMot(equipe, prog));
}

/*
    Supprimer un programmeur a l'équipe d'un manager
    - on cherche l'employe
    - on valide si l'a trouver
    - on get l'équipe et on utilise le stringManger pour suppprimer un nom au string et on l'affecte a l'équipe
*/
void GestionnaireEmployes::supprimerProgAuManager(const string& nom, const string& prog) {
    Manager* manager = chercherManager(nom);

    if (manager == nullptr) {
        cout << "Manager " << nom << " non trouvé." << endl;
        return;
    }
    
    StringManager stringManager;
    string equipe = manager->getEquipe();

    manager->setEquipe(stringManager.retirerMot(equipe, prog));
}

/*
    Afficher les projets d'un manager
    - on cherche l'employe
    - on valide si l'a trouver
    - on get les projets, s'il en a, on utilise la classe stringManager pour afficher le résultat
*/
string GestionnaireEmployes::afficherProjetManager(const string& nom) {
    Manager* manager = chercherManager(nom);
    string result = "";
    if (manager == nullptr) {
        cout << "Manager " << nom << " non trouvé." << endl;
        return result;
    }

    string projetTrouver = manager->getProjets();

    if (!projetTrouver.empty()) {
        StringManager stringManager;
        result += stringManager.construireSortie(projetTrouver);
    } else {
        result += "Aucun projet trouvé";
    }
    return result;
}

/*
    Afficher les projets d'un programmeur
    - on cherche l'employe
    - on valide si l'a trouver
    - on get les projets, s'il en a, on utilise la classe stringManager pour afficher le résultat
*/
string GestionnaireEmployes::afficherProjetProgrammeur(const string& nom) {
    Programmeur* programmeur = chercherProgrammeur(nom);
    string result = "";

    if (programmeur == nullptr) {
        cout << "Programmeur " << nom << " non trouvé." << endl;
        return result;
    }

    string projetTrouver = programmeur->getProjets();
    if (!projetTrouver.empty()) {
        StringManager stringManager;
        result += stringManager.construireSortie(projetTrouver);
    } else {
        result += "Aucun projet trouvé";
    }
    return result;
}

/*
 Fonction template pour trouver les employés associés à un projet donné
 */
template <class T>
string GestionnaireEmployes::employesParProjet(const string& projet, vector<T>& employes) {
    vector<T> employesTrouves;
    string result = "";

    // On boucle dans chaque employe du vector
    for (const auto& employe : employes) {
        // Si on trouve un projet égal au paramètre on l'ajoute a la liste
        if (employe.getProjets().find(projet) != string::npos) {
            employesTrouves.push_back(employe);
        }
    }

    // Validation
    if (employesTrouves.empty()) {
        result += "Aucun employé trouvé";
        return result;
    }

    // On boucle dans les employes trouvés pour les affichers
    for (auto& employe : employesTrouves) {
        result += employe.getPrenom() + " " + employe.getNom();

        if (employe != employesTrouves.back()) {
            result += ", ";
        }
    }

    return result;
}

// Trouver les programmeurs associés à un projet
string GestionnaireEmployes::programmeurParProjet(const string& projet) {
    return employesParProjet(projet, this->programmeurs);
}

// Trouver les managers associés à un projet
string GestionnaireEmployes::managerParProjet(const string& projet) {
    return employesParProjet(projet, this->managers);
}

/*
 Méthode pour afficher l'équipe associée à un manager par nom
    - On cherche l'employe et valide si on en a un
    - on get l'équipe et cherche dans la liste de programmeur si on trouve un employe du même nom pour l'afficher
 */
string GestionnaireEmployes::programmeurAssocier(const string& nom) {
    Manager* manager = chercherManager(nom);
    string result = "";

    if (manager == nullptr) {
        result += "Manager " + nom + " non trouvé.";
        return result;
    }

    const string& equipe = manager->getEquipe();
    stringstream stream(equipe);
    string nomProgrammeur;
    int nbTrouves = 0;

    while (getline(stream, nomProgrammeur, ',')) {
        if (nomProgrammeur.empty()) {
            continue;
        }

        Programmeur* programmeur = this->chercherProgrammeur(nomProgrammeur);
        if (programmeur == nullptr) {
            continue;
        }

        if (nbTrouves > 0) {
            result += ", ";
        }
        result += programmeur->getPrenom() + " " + programmeur->getNom();
        nbTrouves++;
    }

    if (nbTrouves == 0) {
        result += "****";
    }
    return result;
}

/*
 Fonction qui boucle dans le tableau des objets manager pour trouver le nom d'un programmeur dans la liste de l'équipe et affiche le manager
 */
string GestionnaireEmployes::managerDuProgrammeur(const string& nom) {
    for (auto& manager : this->managers) {
        if (manager.getEquipe().find(nom) != string::npos) {
            return manager.getPrenom() + " " + manager.getNom();
        }
    }
    return "Aucun manager trouvé";
}

GestionnaireEmployes::~GestionnaireEmployes() {}
