/*

IFT1169 - TP3 A24 -

Auteur: Yoann Deguire - decembre 2024

Description:

Classe Employee

------------
*/
#include <iostream>
#include <string>
#include <format>
#include "employe.h"

using namespace std;
/*
 Les méthodes de Employe
*/

/*
    Constructeur de la classe
    - Constructeur vide
    - Constructeur avec assignation des propriétés
    - Constructeur de recopie
*/
Employe::Employe()
    : nom(""), prenom(""), salaire(0), age(0) {}

Employe::Employe(string nom, string prenom, int salaire, int age)
    : nom(nom), prenom(prenom), salaire(salaire), age(age) {}

Employe::Employe(const Employe& autreEmploye) 
    : nom(autreEmploye.nom), prenom(autreEmploye.prenom), salaire(autreEmploye.salaire), age(autreEmploye.age) {}

Employe& Employe::operator=(const Employe& autreEmploye) {
    if (this != &autreEmploye) {
        nom = autreEmploye.nom;
        prenom = autreEmploye.prenom;
        salaire = autreEmploye.salaire;
        age = autreEmploye.age;
    }
    return *this;
}


/*
    Getter
*/
const string Employe::getNom() {
    return this->nom;
}

const string Employe::getNom() const {
    return this->nom;
}

const string Employe::getPrenom() {
    return this->prenom;
}

const string Employe::getPrenom() const {
    return this->prenom;
}

const int Employe::getSalaire() {
    return this->salaire;
}

const int Employe::getSalaire() const {
    return this->salaire;
}

const int Employe::getAge() {
    return this->age;
}

const int Employe::getAge() const {
    return this->age;
}


/*
    Setter
*/
    void Employe::setNom(string nom) {
        this->nom = nom;
    }

    void Employe::setPrenom(string prenom) {
        this->prenom = prenom;
    }


/*
    Surchage des opérateurs
*/
bool Employe::operator==(Employe& autreEmploye) {
    return this->nom == autreEmploye.getNom()
        && this->prenom == autreEmploye.getPrenom()
        && this->salaire == autreEmploye.getSalaire()
        && this->age == autreEmploye.getAge();
}

bool Employe::operator!=(Employe& autreEmploye) {
    return !(*this == autreEmploye);
}

bool Employe::operator<(const Employe& autreEmploye) {
    return this->nom < autreEmploye.nom;
}

ostream& operator<<(ostream& os, const Employe& employer) {
    // Utilisation de format pour modifier le format d'affichage
    string sortie = format("**{} {}**", employer.prenom, employer.nom);
    return os << sortie;
}

Employe::~Employe() {}