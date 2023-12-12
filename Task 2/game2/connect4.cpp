#include "connect4.h"
#include "BoardGame_Classes.hpp"
using namespace std;
connect4::connect4() {
    int choice;
    cout << "Choose your opponent:" << endl;
    cout << "1. Another player" << endl;
    cout << "2. Computer" << endl;
    cout << "Enter 1 or 2: ";
    cin >> choice;
    if (choice == 1) {
        display_board();
        while (!game_end) {
            cout << "Player: " << player << " ";
            int input;
            cin >> input;
            update_board(input - 1, 0, 0);
            display_board();
            is_draw();
            is_winner();
            player = (player == 1) ? 2 : 1;
        }
    };
    // Inside the connect4::connect4() function
    if (choice == 2) {
        display_board();
        while (!game_end) {
            cout << "Player: " << player << " ";
            if (player == 1) {
                int input;
                cin >> input;
                update_board(input - 1, 0, 0);
            } else {
                computer_move(); // Execute computer's move before updating the board
            }
            display_board();
            is_draw();
            is_winner();
            player = (player == 1) ? 2 : 1;
        }
    }

}
//_____________________________________________________________
void connect4::display_board() {
    cout<<"  1   2   3   4   5   6   7"<<endl;
    for (int i=0;i<6;i++){
        for (int j=0;j<7;j++){
            if(board[i][j] == 0){
                cout<<"|  |";
            }
            else if(board[i][j] == 1)
            {
                cout<<"| X|";
            }
            else if(board[i][j] == 2)
            {
                cout<<"| O|";
            }
        }
        cout<<endl;
    }
    cout<<"----------------------------"<<endl;
}

//_______________________________________________________________
bool connect4::update_board (int input, int y, char mark){
    {
        if(n_rows>=0){
            if(board[n_rows][input] != 0){
                n_rows--;
                update_board(input,0,0);

            }
            else{
                board[n_rows][input]=player;
                n_rows=5;
            }
        }else{
            cout<<"wrong input"<<endl;
            player=player==1?2:1;
            n_rows=5;
        }
    }
}

//____________________________________________________________

bool connect4::is_winner(){
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 7; j++) {
            if (board[i][j] == player) {
                // Check horizontally
                if (j + 3 < 7 &&
                    board[i][j + 1] == player &&
                    board[i][j + 2] == player &&
                    board[i][j + 3] == player) {
                    game_end = true;
                    cout << "Player " << player << " wins horizontally!" << endl;
                    return true;
                }

                // Check vertically
                if (i + 3 < 6 &&
                    board[i + 1][j] == player &&
                    board[i + 2][j] == player &&
                    board[i + 3][j] == player) {
                    game_end = true;
                    cout << "Player " << player << " wins vertically!" << endl;
                    return true;
                }

                // Check diagonally (down-right)
                if (i + 3 < 6 && j + 3 < 7 &&
                    board[i + 1][j + 1] == player &&
                    board[i + 2][j + 2] == player &&
                    board[i + 3][j + 3] == player) {
                    game_end = true;
                    cout << "Player " << player << " wins diagonally!" << endl;
                    return true;
                }

                // Check diagonally (up-right)
                if (i - 3 >= 0 && j + 3 < 7 &&
                    board[i - 1][j + 1] == player &&
                    board[i - 2][j + 2] == player &&
                    board[i - 3][j + 3] == player) {
                    game_end = true;
                    cout << "Player " << player << " wins diagonally!" << endl;
                    return true;
                }
            }
        }
    }
}
//____________________________________________________________________________________
bool connect4::is_draw() {
    // Check if there are any empty spaces left on the board
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 7; j++) {
            if (board[i][j] == 0) {
                // If at least one empty space is found, the game is not a draw
                return false;
            }
        }
    }

    // If no empty spaces are found, and no player has won, the game is a draw
    cout << "The game is a draw!" << endl;
    return true;

}
//_____________________________________________________________________________

bool connect4::game_is_over() {
    // Check if a player has won
    if (!is_winner()) {
        return true;
    }
    // Check if the game is a draw
    if (is_draw()) {
        return true;
    }
    // If neither player has won nor the game is a draw, the game is not over
    return false;
}
//______________________________________________________________________________
void connect4::computer_move() {
    // You can implement a simple random move for the computer player
    int random_column;
    do {
        random_column = rand() % 7;  // Generate a random column (0-6)
    } while (board[0][random_column] != 0);  // Keep generating until an empty column is found

    update_board(random_column, 0, 0);
    cout << "Computer chose column " << random_column + 1 << endl;
}