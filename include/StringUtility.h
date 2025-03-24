/*

Auteur: Yoann Deguire

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

    string buildOutput(const string& property);
    vector<string> createVector(const string& property);
    string rebuildString(const vector<string>& wordList);
    string removeWord(const string& property, const string& word);
    string addWord(const string& property, const string& word);

    ~StringUtility();
};
#endif