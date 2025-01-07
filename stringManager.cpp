/*

IFT1169 - TP3 A24 -

Auteur: Yoann Deguire - decembre 2024

Description:
Classe StringManager qui sert de genre d'utility avec méthode de manipulation
de string utile à l'affichage et la modification de propriétés
------------
*/
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <format>
#include <algorithm>
#include "stringManager.h"

using namespace std;

StringManager::StringManager() {}

/*
    - Permet d'afficher des propriétés de type string avec le bon format
    - On passe un string, on split a la virgule et construit un vector
    - On boucle a travers le vector et reconstruit le string avec le bon format
*/
string StringManager::construireSortie(const string& propriete) {
    vector<string> resultat;
    stringstream ss(propriete);
    string nom;
    string sortieComplete = "";
    
    while (getline(ss, nom, ',')) {
        const string sortie = format("{}", nom);
        resultat.push_back(sortie);
    }

    for (size_t i = 0; i < resultat.size(); ++i) {
        if (i > 0 && i < resultat.size()) {
            sortieComplete += ", ";
        }
        sortieComplete += resultat[i];
    }
    return sortieComplete;
}

/*
 - Méthode qui permet de creer un vector a partir d'un string en utilisant la virgule  comme délimitateur
*/
vector<string> StringManager::creezVector(const string& propriete) {
    vector<string> resultat;
    stringstream ss(propriete);
    string nom;
    while (getline(ss, nom, ',')) {
        resultat.push_back(nom);
    }
    return resultat;
}

// Méthode pour reconstruire un string à partir d'un vector
string StringManager::reconstruireString(const vector<string>& listeMots) {
    stringstream ss;

    for (size_t i = 0; i < listeMots.size(); ++i) {
        if (i > 0) {
            ss << ",";
        }
        ss << listeMots[i];
    }
    return ss.str();
}

/* 
    Méthode pour retirer un mot dans un string
    - on crée d'abord un vector
    - on supprime le mot dans la liste
    - on reconstruit le string
*/
string StringManager::retirerMot(const string& propriete, const string& mot) {
    vector<string> listeMots = creezVector(propriete);

    for (auto it = listeMots.begin(); it != listeMots.end(); ++it) {
        if (*it == mot) {
            listeMots.erase(it);
            break;
        }
    }
    return reconstruireString(listeMots);
}


/* 
    Méthode pour ajouter un mot dans un string
    - on crée d'abord un vector
    - on ajoute le mot dans la liste
    - on reconstruit le string
*/
string StringManager::ajouterMot(const string& propriete, const string& mot) {
    vector<string> listeMots = creezVector(propriete);
    listeMots.push_back(mot);
    return reconstruireString(listeMots);
}

StringManager::~StringManager() {}