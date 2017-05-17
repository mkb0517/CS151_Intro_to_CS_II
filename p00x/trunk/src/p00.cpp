/**============================================================================
 * Name        : p00.cpp
 * Author      : Matthew Brown
 * Version     :
 * Copyright   :
 * Description : The game of NIM
 *     Players must remove at least one star from one row each turn.
 *     To win, a player must always leave at least one star for the opponent.
 *============================================================================
 */

#include <iostream>
#include <cctype>
#include <cstdlib>
using namespace std;

/**
 * Alternates between player 1 and 2 as the function is called.
 */
int turn(int player) {
	player = (player==1?2:1);
	return player;
}

/**
 * Creates stars according to the value passed to it.
 */
void stars(int n) {
	for (int i=0;i<n;i++) cout << '*';
}

/**
 * Displays the amount of stars left in each pile.
 */
void show(int a, int b, int c) {
	cout << "A:";
	stars(a);
	cout << a << endl;
	cout << "B:";
	stars(b);
	cout << b << endl;
	cout << "C:";
	stars(c);
	cout << c << endl;
}

/**
 * Asks the user for their choice of row and number of stars to remove,
 * Then subtracts the stars from the desired pile.
 * If user is cheating by choosing no stars to remove or a pile that is already 0
 * the player is disqualified and the users are notified.
 * A reference operator is used here to change the values of the variables
 * outside of the function
 */
void move(int &a, int &b, int &c) {
	char row;
	int n;
	bool test = false;
	cout << "Which row?";
	while (test == false) //Check to see if row has a valid input
	{
	    cin >> row;
	    if ((toupper(row)=='A')||(toupper(row)=='B')||(toupper(row)=='C'))
	    {
	        test = true;
	    }
	    else cout << "Please Enter A, B, or C" << endl;
	}
	cout << "How many from row " << row << "?";
	test=false;
	while (test == false) //Check to see if n has a valid input
	{
	    cin >> n;
	    if (n>0) test = true;
	    else
	    {
	        cout << "Please enter a valid number" << endl;
	        cin.clear();
	        cin.ignore(1000,'\n');
	    }
	}
	cout << n << " from row " << row << "." << endl;
	switch (toupper(row)) {
	case 'A':
		a -= n;
		break;
	case 'B':
		b -= n;
		break;
	case 'C':
		c -= n;
		break;
	default:
		n = 0;
	}
	if (n < 1 || a < 0 || b < 0 || c < 0) {
		cout << "You are disqualified for cheating (by making an invalid move)."
				<< endl;
		exit(0);
	}
}

/**
 * Main body function. Calls the show and move functions to make the game run.
 * Contains the win and lose conditions based on how many stars are left.
 */
int main() {
	int a=3,b=5,c=7;
	int player=2;
	cout << "Welcome to the game of NIM!" << endl;
	cout << "To play, choose stars to remove from a row" << endl;
	cout << "and try to leave the opponent with one star." << endl;
	cout << "Don't make a pile go negative or you will lose!" << endl;
	cout << "Press Enter to get started" << endl;
	cin.clear();
	cin.ignore(1000,'\n');
	while(a+b+c>=0)
	{
	    player = turn(player);
	    cout << "Player: ";
	    if (a+b+c==1)
	    {
	        cout << turn(player) << " wins!";
	        break;
	    }
	    else if (a+b+c==0)
	    {
	        cout << turn(player) << " loses...";
	        break;
	    }
	    else
	    {
	        cout << player << endl;
	        show(a, b, c);
	        move(a, b, c);
	    }
	}
	return 0;
}
