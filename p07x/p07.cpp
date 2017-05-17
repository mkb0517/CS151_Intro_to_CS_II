/**============================================================================
// Name        : p07.cpp
// Author      : Matthew Brown
// Version     : 1.07
// Copyright   : 
// Description : bit reader
//====================*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/**
 * recursive function to print out the corresponding bits of a char
 */
void binary(char byte, int numbits=8){
    if (numbits==0) {
        cout << " ";
        return;
    }
    cout << (byte&(1<<(numbits-1)) ? 1 : 0);
    binary(byte,numbits-1);
}

/**
 * Main body of the program
 * checks if there are valid command line arguments
 * opens each file passed via command line and reads the characters from the file
 * calls the binary function and prints out the characters read as binary
 */
int main(int argc,char *argv[]) {
    if (argc<2) {
        cerr << "Usage:  " << argv[0] << " filename" << endl;
        return 1;
    }
    char toread;
    for (int i=1;i<argc;i++){     // open all files passed from the command line
        ifstream ifs(argv[i], ios::binary); // open the file in binary mode
        int counter = 0;
        while (!ifs.fail()){
            if (counter<8){     // set up a counter to newline after 8 bytes are printed
                ifs.read(&toread,1);     // reads the next byte out of the file
                if ((toread==0)||(toread==' ')) {}  // if there is white space in the file, skip it
                else if (ifs.eof()) break; // if you reach the end of file, quit and go one to the next file
                else if(toread!=0) { // if you pass the other checks, then go on to call the function
                    binary(toread);
                    counter++;
                }
            }
            else {      // when counter reaches 8, start a new line and reset the counter
                cout << endl;
                counter = 0;
            }
        }
        cout << endl;
    }
    cout << endl;
    return 0;
}
