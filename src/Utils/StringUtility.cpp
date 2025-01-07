/*

IFT1169 - TP3 A24 -

Author: Yoann Deguire - December 2024

Description:
StringUtility class that serves as a utility with string manipulation methods
useful for displaying and modifying properties
------------
*/
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <format>
#include <algorithm>
#include "StringUtility.h"

using namespace std;

StringUtility::StringUtility() {}

/*
    - Allows displaying string properties with the correct format
    - Takes a string, splits it by commas, and builds a vector
    - Loops through the vector and reconstructs the string with the correct format
*/
string StringUtility::buildOutput(const string& property) {
    vector<string> result;
    stringstream ss(property);
    string lastName;
    string completeOutput = "";
    
    while (getline(ss, lastName, ',')) {
        const string output = format("{}", lastName);
        result.push_back(output);
    }

    for (size_t i = 0; i < result.size(); ++i) {
        if (i > 0 && i < result.size()) {
            completeOutput += ", ";
        }
        completeOutput += result[i];
    }
    return completeOutput;
}

/*
 - Method to create a vector from a string using commas as delimiters
*/
vector<string> StringUtility::createVector(const string& property) {
    vector<string> result;
    stringstream ss(property);
    string lastName;
    while (getline(ss, lastName, ',')) {
        result.push_back(lastName);
    }
    return result;
}

// Method to reconstruct a string from a vector
string StringUtility::rebuildString(const vector<string>& wordList) {
    stringstream ss;

    for (size_t i = 0; i < wordList.size(); ++i) {
        if (i > 0) {
            ss << ",";
        }
        ss << wordList[i];
    }
    return ss.str();
}

/* 
    Method to remove a word from a string
    - First, a vector is created
    - The word is removed from the list
    - The string is reconstructed
*/
string StringUtility::removeWord(const string& property, const string& word) {
    vector<string> wordList = createVector(property);

    for (auto it = wordList.begin(); it != wordList.end(); ++it) {
        if (*it == word) {
            wordList.erase(it);
            break;
        }
    }
    return rebuildString(wordList);
}

/* 
    Method to add a word to a string
    - First, a vector is created
    - The word is added to the list
    - The string is reconstructed
*/
string StringUtility::addWord(const string& property, const string& word) {
    vector<string> wordList = createVector(property);
    wordList.push_back(word);
    return rebuildString(wordList);
}

StringUtility::~StringUtility() {}
