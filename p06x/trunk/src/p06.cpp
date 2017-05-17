//============================================================================
// Name        : p06.cpp
// Author      : Matthew Brown
// Version     : 1.06
// Copyright   :
// Description : Dictionary of Hawaiian Translations
//============================================================================

#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <string>
#include <map>


using namespace std;


/**
 * reads preset words into a string stream and then from the stream into a map.
 */
void readFromString(map<string, string>& dic) {
    stringstream ss;
    ss << "ekahi one" << endl << "elua two" << endl << "ekolu three" << endl;
    string word;
    while (ss >> word >> ws) {
        getline(ss, dic[word]);
    }
}

/**
 * reads the dictionary words from a file data.txt into a map.
 */
void readFromFile(map<string, string>& dic) {
    ifstream ifs("data.txt");
    string word;
    while (ifs >> word >> ws) {
        getline(ifs, dic[word]);
    }
}

/**
 * writes the mapped words to data.txt
 */
void writeToFile(const map<string, string>& dic) {
    ofstream out("data.txt");
    for (pair<string, string> def : dic) {
        out << def.first << '\t' << def.second << endl;
    }
}

/**
 * asks user to input words and definitions for the dictionary.
 * if the user inputs a '.' for the word, it erases the dictionary.
 * if a user inputs '.' for the definition, it erases the word supplied.
 */
void addToDict(map<string, string>& dic) {
    string word;
    cout << "New word: " << flush;
    cin >> word;
    if (word == ".") {
        dic.clear();
    } else {
        cout << "New definition: " << flush;
        cin >> ws;
        getline(cin, dic[word]);
        if (dic[word] == ".")
            dic.erase(word);
        else
            cout << '"' << word << '"' << " means " << '"' << dic[word] << '"' << endl;
    }
}
 /**
  * lists out the current words and definitions from the map.
  */
void listDict(const map<string, string>& dic) {
    for (pair<string, string> def : dic) {
        cout << '"' << def.first << "\" means \"" << def.second << '"' << endl;
    }
}

/**
 * main body of the program.
 * initializes the dictionary map.
 * calls the functions to read and write from the streams to the map and file.
 */
auto main() -> int {
    map<string, string> dic;
    readFromString(dic);
    readFromFile(dic);
    listDict(dic);
    addToDict(dic);
    writeToFile(dic);
    cout << "Mahalo." << endl;
    return 0;
}
