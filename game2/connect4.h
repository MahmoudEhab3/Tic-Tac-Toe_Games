// File: A3_S1_20220457_.cpp
// Purpose: Connect4
// Author: Mahmoud Ehab
// Section: S1
// ID: 20220457
// TA: Khaled Ibrahim

#ifndef CONNECT4_CONNECT4_H
#define CONNECT4_CONNECT4_H
#include <bits/stdc++.h>
#include "BoardGame_Classes.hpp"

class connect4:public Board  {
private:
    int board[6][7] = {{0}};
    int player=1;
    int n_rows=5;
    bool game_end = false;
public:
    connect4();
    void display_board();
    bool is_winner();
    bool is_draw();
    bool game_is_over();
    bool update_board (int x, int y, char mark);
    void computer_move();

};
#endif //CONNECT4_CONNECT4_H
