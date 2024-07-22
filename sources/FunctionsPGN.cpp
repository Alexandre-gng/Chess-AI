#include <fstream>
#include <iostream>
#include <string>
#include <ctype.h>
#include "ClassBoard.h"

using namespace std;

/*
ChessBoard PGNtoBoard(string pathfile) {
    ChessBoard Board;
    ChessBoard* ptrBoard = &Board;

    ifstream file(pathfile);
    string line;
    string a = "\"";
    cout << " a = " << a << endl;
    if(file) {
        string nameEvent;
        char TEMPFirstChar;
        // Gets all of the basic tags
        do {
            file >> line;
            for (auto i: line) {
                cout << i << " " << endl;
            }
            cout << "end line " << endl;
            int i = 1;
            string tag;
            while (isalpha(line[i])) {
                tag+= line[i];
                i++;
            }
            if (tag == "Event") {
                cout << line;
            }
            TEMPFirstChar = line[0];
        } while (TEMPFirstChar == *"[");
        // Gets all of the moves
        if (isdigit(line[0])) {
            do {

            } while ()
        }
    }
    return Board;
}
*/