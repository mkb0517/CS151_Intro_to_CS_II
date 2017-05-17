/**===========================================================================
// Name        : p03.cpp
// Author      : Matthew Brown
// Version     : 1.03
// Copyright   : 
// Description : Translation Dictionary:
 * Builds a data base for Hawaiian words and definitions. Users
 * can input Hawaiian words and if it is not already in the
 * database, it will ask for a definition. Once in, it will display
 * the definition whenever someone inputs that word again.
 * ========================================*/

#include <iostream>
#include <string>
#include <map>

using namespace std;

/**
 * The Main body of the program.
 * It contains the main loop that runs the program
 * Asks the user for a hawaiian word and displays the definition if it
 * is already entered, otherwise it asks for the definition.
 * Stores the values in a map.
 * It lets the user know how to exit the loop
 * and outputs "Aloha" on exit.
 */
int main() {
    string word;
    map<string,string> Dict;

   cout << "Welcome to the User-Defined Hawaiian Dictionary!" << endl;
   cout << "To exit the program, enter a period . " << endl;
   while (word!="."){
       cout << "Please enter a Hawaiian word: ";
       getline(cin, word);
       if (word=="."){
           break;
       }
       else if (Dict[word]==""){
           cout << "That word isn't in the list yet! " << endl
                   << "Please enter the definition: " << endl;
           getline(cin,Dict[word]);
           cout << "Your entry has been recorded, thank you!" << endl;
       }
       else if (Dict[word]!=""){
           cout << "The Definition of " << word << " is : ";
           cout << Dict[word] << endl;
       }
   }
    cout << "Aloha" << endl; // prints Aloha
    return 0;
}
