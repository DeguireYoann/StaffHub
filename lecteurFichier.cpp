/*

IFT1169 - TP3 A24 -

Auteur: Yoann Deguire - decembre 2024

Description:
Classe LecteurFicher permettant de "parser" des fichiers CSV et construire des objects de type 
Programmeur & Manager 
------------
*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "lecteurFichier.h"

using namespace std;

LecteurFichier::LecteurFichier() {}

string LecteurFichier::getRouteFichierProg() {
    return routeFichierProg;
}

string LecteurFichier::getRouteFichierManager() {
    return routeFichierManager;
}

void LecteurFichier::setRouteFichierProg(const string& nomFichier) {
    if(nomFichier != routeFichierProg)
        routeFichierProg = nomFichier;
}

void LecteurFichier::setRouteFichierManager(const string& nomFichier) {
    if(nomFichier != routeFichierManager)
        routeFichierManager = nomFichier;
}

bool LecteurFichier::validerFichier(const string& nomFichier, const string enTete[7]) {
    ifstream fichier(nomFichier);

    if (!fichier.is_open()) {
        cerr << "Erreur : Impossible d'ouvrir le fichier." << endl;
        return false;
    }

    string ligne;

    // Lire la première ligne
    if (getline(fichier, ligne)) {
        stringstream ss(ligne);
        string valeur;
        int champs = 0;

        // Entête
        while (getline(ss, valeur, ';')) {
            if (champs >= 7 || valeur != enTete[champs]) {
                cerr << "Erreur : Entête invalide - Champ " << champs + 1
                     << " attendu : " << enTete[champs] 
                     << ", trouver : " << valeur << endl;
                return false;
            }
            champs++;
        }

        // Vérifier que tous les champs attendus sont présents
        if (champs != 7) {
            cerr << "Erreur : L'en-tête ne contient pas le bon nombre de champs." << endl;
            return false;
        }
    } else {
        cerr << "Erreur : Le fichier est vide ou ne peut pas être lu." << endl;
        return false;
    }

    fichier.close();
    return true;
}

bool LecteurFichier::validerFichiers() {    
    const bool fichierManagerValide = this->validerFichier(routeFichierManager, enTeteManager);
    const bool fichierProgValide = this->validerFichier(routeFichierProg, enTeteProg);

    return fichierManagerValide && fichierProgValide;
}

/*
    Lire le fichier de donnée des managers et construire les ajouters à un vector passer en paramètres
*/
void LecteurFichier::lireFichierManager(vector<Manager>& managers)
{
    ifstream fichier(routeFichierManager);
    if (!fichier.is_open()) {
        return;
    }

    string ligne;
    getline(fichier, ligne);

    while (getline(fichier, ligne)) {
        string nom = "", prenom = "", langage = "", equipe = "",projets = "";
        int age = 0, salaire = 0, budget = 0;

        // récupération des valeurs pour les variables
        stringstream stream(ligne);
        getline(stream, nom, ';');
        getline(stream, prenom, ';');
        stream >> age;
        stream.ignore();
        stream >> salaire;
        stream.ignore();
        getline(stream, equipe, ';');
        stream >> budget;
        stream.ignore();
        getline(stream, projets);

        // assignation d'un object avec constructeur
        managers.push_back(Manager(nom, prenom, salaire, age, budget, equipe, projets));
    }

    fichier.close();
}

void LecteurFichier::ecrireFichierManager(const vector<Manager>& managers)
{
    ofstream fichier(routeFichierManager);
    if (!fichier.is_open()) {
        return;
    }

    // Entête du fichier
    for (int i = 0; i < 7; ++i) {
        fichier << enTeteManager[i];
        if (i < 6) fichier << ";"; // Séparer par des ;
    }
    fichier << endl;

    // Parcours des managers et écriture des données
    for (const auto& manager : managers) {
        fichier << manager.getNom() << ";"
                << manager.getPrenom() << ";"
                << manager.getAge() << ";"
                << manager.getSalaire() << ";"
                << manager.getEquipe() << ";"
                << manager.getBudget() << ";"
                << manager.getProjets() << endl;
    }

    fichier.close();
}

/*
 Fonction qui passe tout les lignes d'un fichier selon la route et construit un object de classe Programmeur par ligne et par cellule de tableau
 Ensuite on l'ajoute a un vector passer en paramètre
 */
void LecteurFichier::lireFichierProgrammeur(vector<Programmeur>& programmeurs)
{
    ifstream fichier(routeFichierProg);
    if (!fichier.is_open()) {
        return;
    }

    string ligne;
    getline(fichier, ligne);

    while (getline(fichier, ligne)) {
        string nom = "", prenom = "", langage = "", experience = "", projets = "";
        int age = 0, salaire = 0;

        // récupération des valeurs pour les variables
        stringstream stream(ligne);
        getline(stream, nom, ';');
        getline(stream, prenom, ';');
        stream >> age;
        stream.ignore();
        stream >> salaire;
        stream.ignore();
        getline(stream, langage, ';');
        getline(stream, experience, ';');
        getline(stream, projets);

        // assignation d'un object avec constructeur
        programmeurs.push_back(Programmeur(nom, prenom, age, salaire, langage, experience, projets));
    }

    fichier.close();
}

void LecteurFichier::ecrireFichierProgrammeur(const vector<Programmeur>& programmeurs)
{
    ofstream fichier(routeFichierProg);
    if (!fichier.is_open()) {
        return;
    }

    // Entête du fichier
    for (int i = 0; i < 7; ++i) {
        fichier << enTeteProg[i];
        if (i < 6) fichier << ";"; // Séparer par des ;
    }
    fichier << endl;

    // Parcours des programmeurs et écriture des données
    for (const auto& programmeur : programmeurs) {
        fichier << programmeur.getNom() << ";"
                << programmeur.getPrenom() << ";"
                << programmeur.getAge() << ";"
                << programmeur.getSalaire() << ";"
                << programmeur.getLangage() << ";"
                << programmeur.getExperience() << ";"
                << programmeur.getProjets() << endl;
    }

    fichier.close();
}

LecteurFichier::~LecteurFichier() {}
