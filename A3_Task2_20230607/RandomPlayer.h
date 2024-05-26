//
// Created by Mazen on 12/13/2023.
//

#ifndef A3_TASK2_20230607_RANDOMPLAYER_H
#define A3_TASK2_20230607_RANDOMPLAYER_H
#include "Player.h"

class RandomPlayer: public Player {
protected:
    int dimension;
public:
    // Take a symbol and pass it to parent
    RandomPlayer (char symbol, int dimension);
    // Generate a random move
    void get_move(int& x, int& y);
};


#endif //A3_TASK2_20230607_RANDOMPLAYER_H
