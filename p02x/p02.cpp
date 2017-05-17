/**============================================================================
// Name        : p02.cpp
// Author      : Matthew Brown
// Version     : 1.02
// Copyright   : 
// Description : This is the game of NIM!
//==========================================================================*/

#include <iostream>
#include <cctype>
#include <string>
#include <vector>
using namespace std;

/**
 * Changes between player 1 and 2 as the function is called
 * based on the value passed to it.
 */
int turn(int player) {
	player = (player==1?2:1);
	return player;
}

/**
 * Uses a string class to create stars to be returned based on
 * the value passed to it.
 */
string stars(int n) {
    string star;
    for (int i=0; i<n ;i++)
    {
        star += "*";
    }
    return star;
}

/**
 * Prints out the rows,
 * the stars based on what is returned from stars(),
 * and the numeric value of the stars left in each vector slot.
 */
void show(vector<int> &a) {
    for (unsigned int i=0; i<a.size(); i++)
    {
    	cout << static_cast<char>('A'+i) << ": ";
    	cout << stars(a[i]);
    	cout << a[i] << endl;
    }
}

/**
 * Gets input from the players to remove stars from the vector.
 * Returns false to continue the main() loop.
 * Returns true to exit the main() loop after outputting
 * a message about being disqualified for cheating
 *
 */
bool move(vector<int> &a) {
	char row;
	int n;
	bool test = false;

	cout << "Which row? ";
	while (test == false) //Check to see if row has a valid input
	{
	    cin >> row;

	    for (unsigned int i=0; i<a.size(); i++) {
	        if (toupper(row)==static_cast<int>(65+i)) {
	            test = true;
	            break;
	        }
	    }
	    if (test == true) break;
	    else {
	        cout << "Please Enter ";
	        for (unsigned int i=0; i<a.size()-1; i++) {
	            cout << static_cast<char>(65+i) << ", ";
	        }
	        cout << "or " << static_cast<char>(65+a.size()-1) << ": ";
	        cin.clear();
	        cin.ignore(1000,'\n');
	    }
	}

	cout << "How many from row " << static_cast<char>(toupper(row)) << "? ";
	test=false;
	while (test == false) //Check to see if n has a valid input
	{
		cin >> n;

		if (n>0) test = true;
		else
		{
		    cout << "Please enter a valid number: ";
		    cin.clear();
		    cin.ignore(1000,'\n');
		}
	}
	cout << n << " from row " << static_cast<char>(toupper(row)) << "." << endl;

	for (unsigned int i=0; i<a.size(); i++) {
	    if (toupper(row)==static_cast<int>(65+i)) {
		    a[(toupper(row)-'A')] -= n;
		    break;
	    }
	}

	if (n < 1) //players shouldn't be able to pass n<=0; here for redundancy.
	{
		cout << "You are disqualified for cheating (by making an invalid move)."
					<< endl;
		return true;
	}
	for (unsigned int i=0; i<a.size(); i++) {
	    if (a[i] < 0) {
	        show(a); //show the player reduced a pile to negative.
		    cout << "You are disqualified for cheating (by making an invalid move)."
	 	        << endl;
	    	return true;
    	}
	}
	return false;
}

/**
 * Main body of the program.
 * Initializes necessary variables and the vector to store pile data in.
 * Contains the main loop that calls the functions to execute  the game.
 * Contains the win/lose conditions to exit out of the loop.
 */
int main() {
	//Variable and vector declaration and initialization
	int player=2;
	bool endLoop=false;
    vector<int> a;
    a.push_back(3); //a[0]
    a.push_back(5); //a[1]
    a.push_back(7); //a[2]

    //Game description and instructions
    cout << "Welcome to the game of NIM!" << endl;
    cout << "To play, choose stars to remove from a row" << endl;
    cout << "and try to leave the opponent with one star." << endl;
    cout << "Don't make a pile go negative or you will lose!" << endl;
    cout << "Press Enter to get started" << endl;
    cin.clear();
    cin.ignore(1000,'\n');

    //Main loop to run the game. Ends when move returns a true value.
    while (endLoop==false)
    {
        int sum=0;
    	player=turn(player);
    	cout << "Player: ";

    	//make the sum to check for win conditions
    	for (unsigned int i=0; i<a.size(); i++) {
    	    sum += a[i];
    	}
    	if (sum==1) //current player win condition
    	{
    		cout << turn(player) << " wins!" << endl;
    		show(a);
    		break;
    	}
    	else if (sum==0) //current player lose condition
    	{
    		cout << turn(player) << " loses... Player "
    		        << player << " wins!" << endl;
    		show(a);
    		break;
    	}
    	else
    	{
    	    cout << player << endl;
    		show(a);
    		cout << endl;
    		endLoop=move(a);
    		cout << endl;
    	}
    }
    return 0;
}
