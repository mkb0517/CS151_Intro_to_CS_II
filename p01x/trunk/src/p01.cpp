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
int turn(int player)
{
	player = (player==1?2:1);
	return player;
}

/**
 * Creates stars according to the value passed to it.
 */
void stars(int n)
{
	for (int i=0;i<n;i++) cout << '*';
}

/**
 * Displays the amount of stars left in each pile.
 * Passes an array from main()
 * and cycles through the data points with a for loop.
 */
void show(int a[]) //changed the parameter here to expect an array
{
    for (int i=0; i<3; i++)
    {
        cout << static_cast<char>('A'+i) << ':'; //convert ASCII int to char
        stars(a[i]);
        cout << a[i] << endl;
    }
}

/**
 * Asks the user for their choice of row and number of stars to remove,
 * Then subtracts the stars from the desired pile.
 * If user is cheating by choosing no stars to remove or a pile that is already 0
 * the player is disqualified and the users are notified.
 * An array is used to keep track of the stars left in each pile.
 */
void move(int a[]) //changed the parameter here to expect an array.
{
	char row;
	int n;
	bool test = false;

	cout << "Which row? ";
	while (test == false) //Check to see if row has a valid input
	{
	    cin >> row;

	    if ((toupper(row)=='A')||(toupper(row)=='B')||(toupper(row)=='C'))
	    {
	        test = true;
	    }
	    else
	    {
	        cout << "Please Enter A, B, or C: ";
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

	if ('A'<=(toupper(row))&&(toupper(row)<='C'))
	{
	    //convert row value to upper so the correct array value is changed.
	    a[(toupper(row)-'A')] -= n;
	}
	else n=0; //players shouldn't be able to pass non-A,B,C chars; here for redundancy.

	if (n < 1) //players shouldn't be able to pass n<=0; here for redundancy.
	{
		cout << "You are disqualified for cheating (by making an invalid move)."
				<< endl;
		exit(0);
	}
	else if ((a[0] < 0) || (a[1] < 0) || (a[2] < 0))
	{
	    cout << "You are disqualified for cheating (by making an invalid move)."
	            << endl;
	    show(a); //show the player reduced a pile to negative.
	    exit(0);
	}
}

/**
 * Main body function.
 * Initializes the array that contains the starting pile values.
 * Gives instructions on how to play the game.
 * Calls the show and move functions to make the game run.
 * Contains the win and lose conditions based on how many stars are left.
 */
int main()
{
    //variable and array initialization
	int a[3]={3,5,7};
	int player=2;

	//Game description and instructions
	cout << "Welcome to the game of NIM!" << endl;
	cout << "To play, choose stars to remove from a row" << endl;
	cout << "and try to leave the opponent with one star." << endl;
	cout << "Don't make a pile go negative or you will lose!" << endl;
	cout << "Press Enter to get started" << endl;
	cin.clear();
	cin.ignore(1000,'\n');

	//Game running loop with win and lose conditions
	while(a[0]+a[1]+a[2]>=0)
	{
	    player = turn(player);
	    cout << "Player: ";
	    if (a[0]+a[1]+a[2]==1)
	    {
	        cout << turn(player) << " wins!";
	        break;
	    }
	    else if (a[0]+a[1]+a[2]==0)
	    {
	        cout << turn(player) << " loses...";
	        break;
	    }
	    else
	    {
	        cout << player << endl;
	        show(a);
	        move(a);
	    }
	}
	return 0;
}
