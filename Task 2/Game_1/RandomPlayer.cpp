// Class definition for XO_RandomPlayer class
// Which is a computer player playing randomly
// Author:  Ahmed Elkholy
// Date:    5/12/2023
// Version: 1
#include<iostream>
#include<random>
#include<iomanip>
#include<algorithm>
#include"../include/BoardGame_Classes.hpp"
using namespace std;

// Set player symbol and name as Random Computer Player
RandomPlayer::RandomPlayer (char symbol, int dimension):Player(symbol)
{
    this->dimension = dimension;
    this->name = "Random Computer Player";
    cout << "My names is " << name << endl;
}

// Generate a random move
void RandomPlayer::get_move (int& x, int& y) {
    x = (int) (rand()/(RAND_MAX + 1.0) * dimension);
    y = (int) (rand()/(RAND_MAX + 1.0) * dimension);
    while((x==0&&y==0)||(x==0&&y==1)||(x==0&&y==3)||(x==0&&y==4)||(x==1&&y==0)||(x==1&&y==4)){
        x = (int) (rand()/(RAND_MAX + 1.0) * dimension);
        y = (int) (rand()/(RAND_MAX + 1.0) * dimension);
    }
}
