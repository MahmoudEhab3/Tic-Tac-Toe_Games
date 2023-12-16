//
// Created by Mazen on 12/13/2023.
//

#ifndef A3_TASK2_20230607_X_O_BOARD_H
#define A3_TASK2_20230607_X_O_BOARD_H
#include "Board.h"

class X_O_Board:public Board {
    static int count_x,count_o;
public:
    X_O_Board ();
    bool update_board (int x, int y, char mark);
    void display_board();
    bool is_winner();
    bool is_draw();
    bool game_is_over();
};


#endif //A3_TASK2_20230607_X_O_BOARD_H
