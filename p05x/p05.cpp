//============================================================================
// Name        : p05.cpp
// Author      : Matthew Brown
// Description : Introducing pointers with the game of NIM
//============================================================================

#include <iostream>
#include <cctype>
#include <string>
#include <vector>
#include <cstdlib>
#include <locale>
using namespace std;

/**
 * Row struct to act as a container for the string, count, and shape
 * values of the rows.
 */
struct Row {
    string name;
    int count;
    char shape;
};

/**
 * Selection class to create a pointer for Row.
 */
class Selection {
    Row *p;
    int amount;
public:
    /**
     * default constructor
     */
    Selection() {
        p=0;
        amount=0;
    }

    /**
     * overloaded constructor
     */
    Selection(Row *p, int amount) : p(p), amount(amount) {}

    /**
     * destructor
     */

    /**
     * Selection amount getter
     */
    int getAmount() const {
        return amount;
    }

    /**
     * Selection amount setter
     */
    void setAmount(int amount) {
        this->amount = amount;
    }

    /**
     * Selection p getter
     */
    Row*& getP() {
        return p;
    }

    /**
     * Selection p setter
     */
    void setP(Row*& p) {
        this->p = p;
    }

    /**
     * Selection overloaded decrement operator
     */
    Selection operator-- () {
        p->count -= amount;
        if (p->count < 0) {
            cout << "You have been disqualified for reducing a row below 0";
            exit(0);
        }
        return *this;
    }

};

/**
 * Switches between player 1 and 2 when called.
 */
int turn() {
    static int player = 2;
    player = (player == 1 ? 2 : 1);
    return player;
}

/**
 * Uses a string class to create symbols to be returned based on
 * the value passed to it.
 */
string symbols(int n, char s) {
    string symbol;
    for (int i=0; i<n; i++)
    {
        symbol += s;
    }
    return symbol;
}

/**
 * Add s to the end of a string if count > 1.
 */
string add_s(string name){
    name += "s";
    return name;
}

/**
 * Displays the current state of the board.
 */
void show(Row *p) {
    while (p->shape){
        if (p->count>1) {
            cout << p->count << " ";
            cout << add_s(p->name) << ": ";
            cout << symbols(p->count, p->shape) << endl;
        }
        else if (p->count==1) {
            cout << p->count << " ";
            cout << p->name << ": ";
            cout << symbols(p->count, p->shape) << endl;
        }
        p++;
    }
}

/**
 * Changes a string input to lower case.
 */
string lowercase(string name){
    locale loc;
    string lower="";
    string str = name;
    for (unsigned int i=0; i<str.length();i++){
         lower += tolower(str[i],loc);
    }
    return lower;
}

/**
 * checks to see if the input has an s.
 * If there is, it removes it.
 */
string check_s(string row){
    char lastChar = row.at( row.size() - 1 );
    if (lastChar=='s'){
        row=row.substr(0,row.size()-1);
    }
    return row;
}

/**
 * asks for input from the user to choose a row and how many to delete
 * then deletes n from row. If the user drops the count below 0 then
 * they are disqualified for cheating.
 *
 */
Selection move(Row *p) {
    string row = "";
    int n = 0;
    bool test = false;
    Selection selected;

    cout << ": Which group? ";
    cin >> row;
    row=lowercase(row);
    row=check_s(row);

    while (p->shape) {
        if (row==p->name) {
            cout << "How many from the " << row << " group? ";
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
            if (n==1){
                cout << n << " " << row << " removed from the group." << endl << endl;
                selected.setAmount(n);
                selected.setP(p);
            }
            else if (n>1){
                cout << n << " " << row << "s removed from the group." << endl << endl;
                selected.setAmount(n);
                selected.setP(p);
            }
            break;
        }
        p++;
        if (p->name=="") {
            cout << "Invalid move; Disqualified for cheating." << endl;
            exit(0);
        }
    }
    return selected;
}

/**
 * sums the amount of symbols left in the game. returns the sum.
 */
int total(Row *p) {
    int sum = 0;
    while (p->shape) { // haven't reached the sentinel yet
        sum += p++->count; // add the count to the sum and increment the pointer
    }
    return sum;  // total of count values for all rows
}

/**
 * Main body of the program.
 * Initializes the rows as an array that gets pointed to by class Row
 * Contains the main loop that runs the game.
 */
int main() {
    Row a[] = { // name, amount, shape of items in each row
            { "dollar", 3, '$' },  //
            { "star", 5, '*' },   //
            { "dot", 6, '.' },   //
            { "wave", 5, '~' }, //
            { "", 0, '\0' },   // null character shape is the sentinel that marks the end.
    };
    for (;;) {
        show(a);  // Display the game setup
        cout << endl << "Player " << turn();  // player 1 and player 2 take turns
        if (!total(a)) {  // is the total of the counts of all rows zero?
            cout << " wins!";  // then the other player took the past piece. This player wins.
            break;  // game over
        }
        Selection selected = move(a);   // Get the selected amount and a pointer to the selected row
        --selected;   // Remove the selected amount from the selected row
    }
    return 0;
}

