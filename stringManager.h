/*

IFT1169 - TP3 A24 -

Auteur: Yoann Deguire - decembre 2024

Description:
signature de la classe StringManager
------------
*/
#include <iostream>
#include <vector>
#include <string>

using namespace std;

#ifndef STRING_MANAGER_H
#define STRING_MANAGER_H

class StringManager {
public:
    StringManager();

    string construireSortie(const string& propriete);
    vector<string> creezVector(const string& propriete);
    string reconstruireString(const vector<string>& listeMots);
    string retirerMot(const string& propriete, const string& mot);
    string ajouterMot(const string& propriete, const string& mot);

    ~StringManager();
};
#endif