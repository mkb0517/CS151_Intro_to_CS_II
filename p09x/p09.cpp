/**============================================================================
// Name        : p09.cpp
// Author      : Matthew Brown
// Version     : v1.09
// Description : NIM program using structured exceptions instead of status
//==========================================================================*/

#define _hypot hypot // bug workaround. To fix, upgrade G++ by installing

#include <stdexcept>
#include <iostream> // cin, cout, instream, ostream, endl
#include <vector> // vector
#include <sstream> // istringstream
#include <iomanip> // setw
#include <algorithm> // sort, find_if, remove_if

using namespace std;
/**
 * base Cluster class
 * stores a char for each character and an int for how many of the character
 */
class Cluster { // how many of which item together
protected:
    char item;
    int amount;
public:
    /**
     * Overloaded Cluster Constructor
     * default values are set to '*' and 0 but are overridden when the game is initialized
     */
    Cluster(char item = '*', int amount = 0) :
            item(item), amount(amount) {
    }
    /**
     * overloaded << operator to handle the output of our Clusters
     */
    friend ostream &operator<<(ostream &out, const Cluster &x) {
        out << string(x.amount, x.item);
        return out;
    }
    /**
     * Overloaded >> operator to handle the input to our Clusters
     */
    friend istream &operator>>(istream &in, Cluster &x) {
        in >> x.item;
        for (x.amount = 1; in.peek() == x.item; x.amount++) {
            in >> x.item;
        }
        return in;
    }

    /**
     * Getter for our protected variable amount
     */
    int getAmount() const {
        return amount;
    }

    /**
     * Getter for our protected variable item
     */
    char getItem() const {
        return item;
    }

    /**
     * Setter for our protected Cluster Amount
     */
    void setAmount(int amount) {
        this->amount = amount;
    }

    /**
     * Setter for our protected Cluster Item
     */
    void setItem(char item) {
        this->item = item;
    }

    /**
     * Gives Game access to Cluster private variables
     */
    friend class Game;
};

/**
 * Row class, a sub-class of Cluster to handle each individual row
 */
class Row: public Cluster {
public:
    /**
     * Overloaded << operator for Row to handle the output of the row state
     */
    friend ostream &operator<<(ostream &out, const Row &x) {
        return out << setw(2) << x.amount << ": " << (Cluster) x;
    }
};

/**
 * Selection class, sub-class of Cluster that handles the players' moves
 */
class Selection: public Cluster {
public:
    /**
     * Default Selection Constructor
     */
    Selection() :
            Cluster('$', 5) {
    }

    /**
     * Overloaded Selection constructor
     */
    Selection(char item, int amount) :
            Cluster(item, amount) {
    }

    /**
     * overloaded << operator to handle the moves given by players
     */
    friend ostream &operator<<(ostream &out, const Selection &selection) {
        return out << selection.amount << " from " << selection.item
                   << " group.";
    }
};

/**
 * Game base class.
 * stores the rows in a vector and handles the state of the game
 */
class Game {
    vector<Row> rows;
public:
    /**
     * Getter to access the private Rows variable.
     */
    vector<Row> &getRows() {
        return rows;
    }
    /**
     * Removes any empty rows and then sorts them by amount remaining from lowest to highest
     */
    void fixup() {
        // Delete all rows that are empty (their amount is zero).
        // remove_if does not erase the elements, but moves them to the end
        // and points to where they were removed so they can be erased.
        // Use erase to remove the elements from that point to the end
        rows.erase(
                remove_if(rows.begin(), rows.end(), // target those items in  this range that satisfy the function.
                          [](const Row &r) {return !r.amount;}), // The function defined here tells when amount is zero
                rows.end());
        if (rows.empty()) {
            return;
        }
        // Sort all rows according to the ordering given by the less-than function
        sort(rows.begin(), rows.end(), [](const Row &a,const Row &b) { // the less-than function is defined here
            if (a.amount<b.amount) return true; // first sort on the amount
            if (a.amount>b.amount) return false;
            return a.item<b.item;}); // if the amount is equal, sort on the item next
        if (rows[0].amount < 0) {
            return;
        }
    }

    /**
     * Overloaded Game constructor
     */
    Game(string setup = "#######$$$%%%%%%") {
        istringstream in(setup);
        in >> *this;
        fixup();
    }

    /**
     * Overloaded -= operator to handle the actual removal of items from the rows
     */
    bool operator-=(Selection remove) {
        // i is an iterator object. An iterator is a class that is designed to act a lot like a pointer
        auto i = find_if(
                rows.begin(), rows.end(),
                [remove](const Row &r) {return r.item==remove.item;});
        i->amount -= remove.amount;
        if (i->amount < 0){
            return false;
        }
        if (i == rows.end()) {
            return false;
        }
        fixup();
        return true;
    }

    /**
     * Overloaded >> operator to handle the input of characters into rows
     */
    friend istream &operator>>(istream &in, Game &g) {
        Row r;
        while (in >> r) {
            g.rows.push_back(r);
        }
        return in;
    }

    /**
     * Overloaded << operator to handle the output of rows in the game
     */
    friend ostream &operator<<(ostream &out, const Game &g) {
        for (Row row : g.rows) {
            out << row << endl;
        }
        return out;
    }
};

/**
 * Base player class that stores a name
 * Has a << operator to handle it's name output
 * has a virtual move() function for sub-classes to define
 */
class Player {
private:
    string name;
public:
    /**
     * Overloaded Player Constructor
     */
    Player(const string &name) :
            name(name) {
    }

    /**
     * Overloaded << operator to handle the output of Player names
     */
    friend ostream &operator<<(ostream &out, const Player *player) {
        return out << player->name;
    }

    /**
     * Pure virtual function to be defined by the different player sub-classes
     * Requires the sub-classes to have a move() function
     */
    virtual Selection move()=0;

    /**
     * Default Player Destructor
     */
    virtual ~Player() = default;
};


/**
 * SimpleRoboticPlayer class, subclass of Player
 * Requires a game state to be passed to it to act upon
 */
class SimpleRobotPlayer: public Player {
    Game &game;
    /**
     * Naming function for robotic players
     */
    static string nextName() {
        static int n = 0;
        if (n++) return "Simple Robot Player #" + n;
        return "Simple Robot Player";
    }
public:
    /**
     * Overloaded constructor for SimpleRoboticPlayer
     */
    SimpleRobotPlayer(Game &game, string name = nextName()) :
            Player(name), game(game) {
    }
    /**
     * Overloaded move() function for SimpleRobotic player
     * required by Base-class
     * Takes the 1 item from the whatever is in the first row.
     */
    virtual Selection move() {
        return Selection(game.getRows()[0].getItem(), 1);
    }
};

/**
 * MyRobotPlayer class, sub-class of Player
 * A robotic player created by me to beat anyone it plays against! Hopefully.
 * A Game state is passed by reference to be acted upon
 */
class MyRobotPlayer : public Player {
    Game &game;
    /**
     * Naming function for MyRobotPlayer
     */
    static string nextName() {
        static int n = 0;
        if (n++) return "Voltron Player #" + n;
        return "Voltron Player";
    }
public:
    /**
     * Overloaded MyRobotPlayer Constructor
     */
    MyRobotPlayer(Game &game, string name = nextName()) :
            Player(name), game(game) {
    }
    /**
     * Overloaded move() function
     * Required by the base class
     * MyRobotPlayer searches through all the rows looking for the largest row
     * It keeps a counter of how many rows there are,
     * how many rows only have 1 character in them,
     * and stores the largest row and character to use.
     *
     * When there are more than 4 rows:
     * If there are an even number of rows, it removes all the characters from that row
     * If there is an odd number of rows, it removes all but 1 from that row.
     * If there is only 1 left in each row, it removes the first row.
     *
     * When there are 4 or less rows:
     * It breaks up the moves into specific cases based on
     * the number of one item rows and the number of rows left.
     * Otherwise it defaults to the logic in the first part.
     */
    virtual Selection move() {
        int num_rows = 0;
        int highest = 0;
        int one_rows = 0;
        char chosen;
        Selection selection;
        for (unsigned int i = 0; i<game.getRows().size(); i++){
            if (game.getRows()[i].getAmount()>highest){
                highest = game.getRows()[i].getAmount();
                chosen = game.getRows()[i].getItem();
            }
            if (game.getRows()[i].getAmount()==1){ // count how many rows contain 1 character
                one_rows++;
            }
            num_rows++;
        }

        if (highest==1){
            selection.setItem(chosen);
            selection.setAmount(highest);
        }
        else if (num_rows > 4){
            if ((num_rows%2==0)&&(one_rows<3)){
                selection.setItem(chosen);
                selection.setAmount(highest);
            }
            else if ((num_rows%2==1)&&(one_rows>2)){
                selection.setItem(game.getRows()[0].getItem());
                selection.setAmount(1);
            }
            else if (num_rows%2==1){
                selection.setItem(chosen);
                selection.setAmount(highest-1);
            }
        }
        else { // rows <= 4 and don't all contain 1 item.
            if ((num_rows==4)&&(one_rows==1)){
                selection.setItem(chosen);
                selection.setAmount(highest-1);
            }
            else if ((num_rows==4)&&(one_rows==2)&&(highest>2)){
                selection.setItem(chosen);
                selection.setAmount(1);
            }
            else if ((num_rows==3)&&(one_rows==2)){
                selection.setItem(chosen);
                selection.setAmount(highest-1);
            }
            else if ((num_rows==3)&&(one_rows==1)&&(highest>2)){
                selection.setItem(chosen);
                selection.setAmount(highest-2);
            }
            else if ((num_rows==3)&&(one_rows==1)&&(highest==2)){
                selection.setItem(game.getRows()[0].getItem());
                selection.setAmount(1);
            }
            else if ((num_rows==2)&&(one_rows==0)&&(highest>2)){
                selection.setItem(chosen);
                selection.setAmount(highest-2);
            }
            else {
                if (num_rows%2==0){
                    selection.setItem(chosen);
                    selection.setAmount(highest);
                }
                else if (num_rows%2==1){
                    selection.setItem(chosen);
                    selection.setAmount(highest-1);
                }
            }
        }
        return selection;
    }
};

/**
 * HumanPlayer class, sub-class of Player
 * For a human to play against my robot
 */
class HumanPlayer: public Player {
    Game &game;
    /**
     * Naming function for human players
     */
    static string nextName() {
        static int n = 0;
        cout << "Name of player #" << ++n << ": ";
        string result;
        cin >> result;
        return result;
    }
public:
    /**
     * Overloaded Constructor for HumanPlayer
     */
    HumanPlayer(Game &game, string name = nextName()) :
            Player(name), game(game) {
    }

    /**
     * Asks the human player to make a move
     * Moves are inputed by entering the shape as many times as you want removed
     * ie: %%%%% would be entered if you want to remove five (5) percents (%)
     */
    virtual Selection move() {
        Selection selection;
        cout << "Enter items to remove: ";
        cin >> selection;
        return selection;
    }
};

 /**
  * Game exception for when someone removes too many items from a row
  * and the row goes negative
  */
class NegativeException : public exception {
    const char *message="You have been disqualified for removing too many from a row!";
public:
    const char *what() {
        return message;
    }
};

/**
 * Game exception for when a player tries to take from a row that doesn't exist
 */
class InvalidException : public exception {
    const char *message="You have been disqualified for trying to remove an item from a row that isn't there!";
public:
    const char *what() {
        return message;
    }
};

/**
 * Game exception for when the last item is removed from the game
 * and the game ends.
 */
class EndException : public exception {
    const char *message="  Lost for removing the last item!";
public:
    const char *what() {
        return message;
    }
};

/**
 * Main body of the program
 * Contains the main loop of the game.
 * Initializes the players, calls the move functions,
 * Contains the winning/losing conditions.
 */
int main() {
    try {
        Game game(".....@@@@#####%%%%%%%****");
        // We must use pointers to avoid slicing, which would implicitly convert the subclass to the base class.
        vector<Player*> players = { new MyRobotPlayer(game), new HumanPlayer(game) };
        for (;;) {
            for (auto player : players) {
                cout << game << player << ':' << endl;
                Selection selection = player->move();
                cout << "  Took " << selection << endl;
                if (!(game -= selection)){ // if an invalid move is made, send it to the exception blocks
                    for (unsigned int i=0; i<game.getRows().size();i++){
                        if (game.getRows()[i].getAmount()<0){
                            throw NegativeException();
                        }
                    }
                    throw InvalidException();
                }
                if (game.getRows().empty()){
                    throw EndException();
                }
            }
        }
    } catch (EndException &e) {
        cout << "  " << e.what() << endl;
    } catch (NegativeException &e) {
        cout << "  " << e.what() << endl;
    } catch (InvalidException &e) {
        cout << "  " << e.what() << endl;
    }
	return 0;
}
