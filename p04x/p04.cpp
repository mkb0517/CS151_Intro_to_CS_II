//============================================================================
// Name        : p04.cpp
// Author      : Matthew Brown
// Version     : v1.04
// Copyright   : 
// Description : The game of NIM with class Row
//============================================================================

#include <iostream>
#include <cctype>
#include <string>
#include <vector>
#include <locale>
using namespace std;

/**
 * Row class to create objects to store the information for the rows.
 * Stores a name, count, and shape in the object.
 * Stores the objects in a vector.
 */
class Row{
public:
    string name;
    int count;
    char shape;

    Row();
    Row(string name_, int count_, char shape_);
    void AddRow(Row &rows);

    virtual ~Row();
};
 /**
  * Default constructor for Row class
  */
Row::Row(){
    name="";
    count=0;
    shape='\n';
    vector<Row> row;
}
/**
 * Overloaded constructor for Row class
 */
Row::Row(string name_, int count_, char shape_){
    name=name_;
    count=count_;
    shape=shape_;
}
/**
 * Default destructor for Row class
 */
Row::~Row(){}

/**
 * Changes between player 1 and 2 as the function is called
 * based on the value passed to it.
 */
int turn(int player) {
    player = (player==1?2:1);
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
 * Prints out the rows,
 * the symbols based on what is returned from symbols(),
 * and the numeric value of the stars left in each vector slot.
 */
void show(vector<Row> &rows) {
    for (unsigned int i=0; i<rows.size(); i++)
    {
        if (rows[i].count>1){
            cout << rows[i].count << " " << add_s(rows[i].name) << ": ";
            cout << symbols(rows[i].count, rows[i].shape);
            cout << endl;
        }
        else if (rows[i].count==1){
            cout << rows[i].count << " " << rows[i].name << ": ";
            cout << symbols(rows[i].count, rows[i].shape);
            cout << endl;
        }
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
 * Gets input from the players to remove stars from the vector.
 * Returns false to continue the main() loop.
 * Returns true to exit the main() loop after outputting
 * a message about being disqualified for cheating
 */
bool move(vector<Row> &rows) {
    string row="";
    int n;
    bool test = false;

    cout << "Which row? ";
    while (test == false) //Check to see if row has a valid input
    {
        cin >> row;
        row=lowercase(row);
        row=check_s(row);

        for (unsigned int i=0; i<rows.size(); i++) {
            if (row==rows[i].name) {
                test = true;
                cout << "How many " << row <<"s?";
                break;
            }
        }
        if (test == true) break;
        else {
            cout << "Please Enter ";
            for (unsigned int i=0; i<rows.size(); i++) {
                if (rows[i].count>0){
                    if (i<rows.size()-1) {
                        cout << rows[i].name << ", ";
                    }
                    else if (i==rows.size()-1) {
                        cout << "or " << rows[i].name << ": ";
                    }
                }
            }
            cin.clear();
        }
    }

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
    if (n==1){
        cout << n << " " << row << " removed." << endl;
    }
    else {
        cout << n << " " << row << "s removed." << endl;
    }

    for (unsigned int i=0; i<rows.size(); i++) {
        if (row==rows[i].name) {
            rows[i].count -= n;
            break;
        }
    }

    if (n < 1) //players shouldn't be able to pass n<=0; here for redundancy.
    {
        cout << "You are disqualified for cheating (by making an invalid move)."
                    << endl;
        return true;
    }
    for (unsigned int i=0; i<rows.size(); i++) {
        if (rows[i].count < 0) {
            cout << "You are disqualified for cheating (by making an invalid move)."
                << endl;
            return true;
        }
    }
    return false;
}

/**
 * Main body of the program.
 * Initiates the objects, vector, and main loop that runs the program.
 * Contains the win and lose conditions.
 */
int main() {
    int player = 2;
    bool endLoop = false;
    vector<Row> rows(0);

    Row row0("dollar",3,'$'),
        row1("star",5,'*'),
        row2("wave",7,'~'),
        row3("dot",1,'.');

    rows.push_back(row0);
    rows.push_back(row1);
    rows.push_back(row2);
    rows.push_back(row3);

    //Game description and instructions
    cout << "Welcome to the game of NIM!" << endl;
    cout << "To play, choose a row and how many to remove from it." << endl;
    cout << "Try to leave the opponent with one star." << endl;
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
           for (unsigned int i=0; i<rows.size(); i++) {
               sum += rows[i].count;
           }
           if (sum==1) //current player win condition
           {
               cout << turn(player) << " wins!" << endl;
               break;
           }
           else if (sum==0) //current player lose condition
           {
               cout << turn(player) << " loses... Player "
                       << player << " wins!" << endl;
               break;
           }
           else
           {
               cout << player << endl;
               show(rows);
               cout << endl;
               endLoop=move(rows);
               cout << endl;
           }
       }

    return 0;
}
