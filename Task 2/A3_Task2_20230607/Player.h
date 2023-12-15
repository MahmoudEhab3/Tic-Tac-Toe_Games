//
// Created by Mazen on 12/13/2023.
//

#ifndef A3_TASK2_20230607_PLAYER_H
#define A3_TASK2_20230607_PLAYER_H

#include <bits/stdc++.h>
using namespace std;

class Player {
protected:
    string name;
    char symbol;
public:
    // Two constructors to initiate player
    // Give player a symbol to use in playing
    // It can be X or O or others
    // Optionally, you can give him ID or order
    // Like Player 1 and Player 2
    Player (char symbol); // Needed for computer players
    Player (int order, char symbol);
    // Get desired move: x y (each between 0 and 2)
    // Virtual (can change for other player types)
    virtual void get_move(int& x, int& y);
    // Give player info as a string
    string to_string();
    // Get symbol used by player
    char get_symbol();
};


#endif //A3_TASK2_20230607_PLAYER_H
