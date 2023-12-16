// Class definition for XO_App class
// Author: Ahmed Elkholy , Mahmoud Ehab , Mazen Abdelfattah
// Date:    16/12/2023
// Version: 2

#include <iostream>
#include"../include/Board_Games.hpp"
using namespace std;
void Game_interface(){
    int x;
    cout << "Welcome to FCAI Games. :)\n";
    cout << "Press 1 if you want pyramid XO \n"
            "Press 2 if you want connect 4\n"
            "Press 3 if you want 5x5 XO\n"
            "Press 4 if you want normal XO\n";
    cin>>x;
    switch (x) {
        case 1: {
            char choice;
            Player* players[2];
            players[0] = new Player (1, 'x');

            cout << "if you want to play with AI press 1\n";
            cin >> choice;
            if (choice != '1')
                players[1] = new Player(2, 'o');
            else
                //Player pointer points to child
                players[1] = new RandomPlayer('o', 5);
            GameManager x_o_game(new Pyramid_X_O(), players);
            x_o_game.run();
            break;
        }
        case 2: {
            connect4 game;
            break;
        }
        case 3:{
            char choice;
            Player* players[2];
            players[0] = new Player (1, 'x');
            cout << "if you want to play with AI press 1\n";
            cin >> choice;
            if (choice != '1')
                players[1] = new Player(2, 'o');
            else
                //Player pointer points to child
                players[1] = new RandomPlayer('o', 5);

            GameManager x_o_game(new X_O_5X5(), players);
            x_o_game.run();
            break;
        }
        case 4:{
            char choice;
            Player* players[2];
            players[0] = new Player (1, 'x');
            cout << "if you want to play with AI press 1\n";
            cin >> choice;
            if (choice != '1')
                players[1] = new Player(2, 'o');
            else
                //Player pointer points to child
                players[1] = new RandomPlayer('o', 3);

            GameManager x_o_game(new X_O_Board(), players);
            x_o_game.run();
            break;
        }
    }
}
int main() {
    int n=1;
    while(n==1){
        Game_interface();
        cout<<"If you want to play again press 1\n";
        cin>>n;
    }
    system("pause");
    return 0;
}





