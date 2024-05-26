//
// Created by Mazen on 12/13/2023.
//

#ifndef A3_TASK2_20230607_GAMEMANAGER_H
#define A3_TASK2_20230607_GAMEMANAGER_H
#include "Board.h"
#include "Player.h"

class GameManager {
private:
    Board* boardPtr;
    Player* players[2];
public:
    GameManager(Board*, Player* playerPtr[2]);
    void run();
    // This method creates board and players
    // It displays board
    // While True
    //   For each player
    //      It takes a valid move as x, y pair (between 0 - 2)
    //      It updates board and displays otit
    //      If winner, declare so and end
    //      If draw, declare so and end

};


#endif //A3_TASK2_20230607_GAMEMANAGER_H
