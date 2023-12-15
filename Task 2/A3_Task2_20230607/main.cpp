#include <bits/stdc++.h>
#include "Player.h"
#include "RandomPlayer.h"
#include "GameManager.h"
#include "X_O_Board.h"
using namespace std;

int main() {
    int choice;
    Player* players[2];
    players[0] = new Player (1, 'x');

    cout << "Welcome to FCAI X-O Game. :)\n";
    cout << "Press 1 if you want to play with computer: ";
    cin >> choice;
    if (choice != 1)
        players[1] = new Player (2, 'o');
    else
        //Player pointer points to child
        players[1] = new RandomPlayer ('o', 5);

    GameManager x_o_game (new X_O_Board(), players);
    x_o_game.run();
    //cout<<"Press Enter to continue..."; cin.get();
    system ("pause");
}
