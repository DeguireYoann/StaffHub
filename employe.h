/*

IFT1169 - TP3 A24 -

Auteur: Yoann Deguire - decembre 2024

Description:
Signature de la classe Employee
------------
*/
#include <iostream>
#include <string>

using namespace std;

#ifndef EMPLOYE_H
#define EMPLOYE_H

class Employe {
protected:
/*
 Les propriétées privées
*/
    string nom, prenom;
    int salaire;
    int age;

public:
/*
 Les méthodes public de Employe
*/

    /*
        Constructeur de la classe
        - Constructeur vide
        - Constructeur avec assignation des propriétés
        - Constructeur de recopie
    */
    Employe();
    Employe(string nom, string prenom, int salaire, int age);
    Employe(const Employe& autreEmploye);

    /*
        Getter
    */
    const string getNom();
    const string getNom() const;
    const string getPrenom();
    const string getPrenom() const;
    const int getSalaire();
    const int getSalaire() const;
    const int getAge();
    const int getAge() const;

    /*
        Setter
    */
    void setNom(string nom);
    void setPrenom(string prenom);

    /*
        Surchage des opérateurs
    */
    bool operator==(Employe& autreEmploye);
    bool operator!=(Employe& autreEmploye);
    bool operator<(const Employe& autreEmploye);
    
    Employe& operator=(const Employe& autreEmploye);
    string& operator+=(string& result);
    friend ostream& operator<<(ostream&,const Employe&);

    // Destructeur
    ~Employe();
};
#endif