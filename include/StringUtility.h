/*

Auteur: Yoann Deguire - decembre 2024

Description:
signature de la classe StringUtility
------------
*/
#include <iostream>
#include <vector>
#include <string>

using namespace std;

#ifndef STRING_MANAGER_H
#define STRING_MANAGER_H

class StringUtility {
public:
    StringUtility();

    string construireSortie(const string& propriete);
    vector<string> creezVector(const string& propriete);
    string reconstruireString(const vector<string>& listeMots);
    string retirerMot(const string& propriete, const string& mot);
    string ajouterMot(const string& propriete, const string& mot);

    ~StringUtility();
};
#endif