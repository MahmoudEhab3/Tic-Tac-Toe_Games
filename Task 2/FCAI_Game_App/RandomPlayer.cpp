// Class definition for XO_RandomPlayer class
// Which is a computer player playing randomly
// Author:  Ahmed Elkholy
// Date:    5/12/2023
// Version: 1
#include<iostream>
#include<random>
#include<iomanip>
#include<algorithm>
#include"../include/Board_Games.hpp"
using namespace std;

// Set player symbol and name as Random Computer Player
RandomPlayer::RandomPlayer (char symbol, int dimension):Player(symbol)
{
    this->dimension = dimension;
    this->name = "Random Computer Player";
    cout << "My names is " << name << endl;
}

// Generate a random move
void RandomPlayer::get_move (int& x, int& y)  {        //Newwwwwwwwwwwwwwwwwwww
    x = A_I_move().first;
    y = A_I_move().second;
}
