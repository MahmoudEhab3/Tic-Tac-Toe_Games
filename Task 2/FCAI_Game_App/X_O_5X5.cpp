//
// Created by Mazen on 12/13/2023.
//

#include"../include/Board_Games.hpp"
#include <bits/stdc++.h>
using namespace std;

int X_O_5X5::count_x=0;
int X_O_5X5::count_o=0;

// Set the board
X_O_5X5::X_O_5X5 () {
    n_rows = n_cols = 5;
    board = new char*[n_rows];
    for (int i = 0; i < n_rows; i++) {
        board [i] = new char[n_cols];
        for (int j = 0; j < n_cols; j++)
            board[i][j] = 0;
    }
}

// Return true  if move is valid and put it on board
// within board boundaries in empty cell
// Return false otherwise
bool X_O_5X5::update_board (int x, int y, char mark){
    // Only update if move is valid
    if (!(x < 0 || x > 5 || y < 0 || y > 5) && (board[x][y] == 0)) {
        board[x][y] = toupper(mark);
        n_moves++;
        return true;
    }
    else
        return false;
}

// Display the board and the pieces on it
void X_O_5X5::display_board() {
    for (int i: {0,1,2,3,4}) {
        cout << "\n| ";
        for (int j: {0,1,2,3,4}) {
            cout << "(" << i << "," << j << ")";
            cout << setw(4) << board [i][j] << " |"; 
        }
        cout << "\n-----------------------------";
    }
    cout << endl;
}

// Returns true if there is any winner
// either X or O
// Written in a complex way. DO NOT DO LIKE THIS.

bool X_O_5X5::is_winner() {

    if (n_moves == 24) {

        //Check rows and columns
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board[i][j] == 'X' && board[i][j + 1] == 'X' && board[i][j + 2] == 'X') count_x++;
                if (board[i][j] == 'O' && board[i][j + 1] == 'O' && board[i][j + 2] == 'O') count_o++;
                if (board[j][i] == 'X' && board[j + 1][i] == 'X' && board[j + 2][i] == 'X') count_x++;
                if (board[j][i] == 'O' && board[j + 1][i] == 'O' && board[j + 2][i] == 'O') count_o++;
            }
        }

        //Check main diagonals
        for (int i = 0; i < 3; ++i) {
            if (board[i][i] == 'X' && board[i + 1][i + 1] == 'X' && board[i + 2][i + 2] == 'X') count_x++;
            if (board[i][i] == 'O' && board[i + 1][i + 1] == 'O' && board[i + 2][i + 2] == 'O') count_o++;
        }

        //Check secondary diagonals
        for (int i = 0; i < 3; ++i) {
            if (board[i][4 - i] == 'X' && board[i + 1][3 - i] == 'X' && board[i + 2][2 - i] == 'X') count_x++;
            if (board[i][4 - i] == 'O' && board[i + 1][3 - i] == 'O' && board[i + 2][2 - i] == 'O') count_o++;
        }

        //Additional diagonals
        if (board[0][2] == 'X' && board[1][3] == 'X' && board[2][4] == 'X') count_x++;
        if (board[0][2] == 'O' && board[1][3] == 'O' && board[2][4] == 'O') count_o++;

        if (board[2][0] == 'X' && board[3][1] == 'X' && board[4][2] == 'X') count_x++;
        if (board[2][0] == 'O' && board[3][1] == 'O' && board[4][2] == 'O') count_o++;

        if (board[1][0] == 'X' && board[2][1] == 'X' && board[3][2] == 'X') count_x++;
        if (board[1][0] == 'O' && board[2][1] == 'O' && board[3][2] == 'O') count_o++;

        if (board[0][1] == 'X' && board[1][2] == 'X' && board[2][3] == 'X') count_x++;
        if (board[0][1] == 'O' && board[1][2] == 'O' && board[2][3] == 'O') count_o++;

        if (board[2][1] == 'X' && board[3][2] == 'X' && board[4][3] == 'X') count_x++;
        if (board[2][1] == 'O' && board[3][2] == 'O' && board[4][3] == 'O') count_o++;

        if (board[1][2] == 'X' && board[3][2] == 'X' && board[3][4] == 'X') count_x++;
        if (board[1][2] == 'O' && board[3][2] == 'O' && board[3][4] == 'O') count_o++;

        if (board[0][2] == 'X' && board[1][1] == 'X' && board[2][0] == 'X') count_x++;
        if (board[0][2] == 'O' && board[1][1] == 'O' && board[2][0] == 'O') count_o++;

        if (board[2][0] == 'X' && board[1][1] == 'X' && board[0][2] == 'X') count_x++;
        if (board[2][0] == 'O' && board[1][1] == 'O' && board[0][2] == 'O') count_o++;

        if (board[2][4] == 'X' && board[3][3] == 'X' && board[4][2] == 'X') count_x++;
        if (board[2][4] == 'O' && board[3][3] == 'O' && board[4][2] == 'O') count_o++;

        if (board[1][4] == 'X' && board[2][3] == 'X' && board[3][2] == 'X') count_x++;
        if (board[1][4] == 'O' && board[2][3] == 'O' && board[3][2] == 'O') count_o++;

        if (board[2][3] == 'X' && board[3][2] == 'X' && board[4][1] == 'X') count_x++;
        if (board[2][3] == 'O' && board[3][2] == 'O' && board[4][1] == 'O') count_o++;

        if (board[0][3] == 'X' && board[1][2] == 'X' && board[2][1] == 'X') count_x++;
        if (board[0][3] == 'O' && board[1][2] == 'O' && board[2][1] == 'O') count_o++;

        if (board[1][2] == 'X' && board[2][1] == 'X' && board[3][0] == 'X') count_x++;
        if (board[1][2] == 'O' && board[2][1] == 'O' && board[3][0] == 'O') count_o++;

        if (count_x < count_o) {
            cout << "O WINS !!\nScore : "<<count_o<<"\n";
            exit(0);
        } else if (count_x > count_o) {
           cout << "X WINS !!\nScore : "<<count_x<<"\n";
            exit(0);
        }
        else{
            return false;
        }
    }
    return false;
}

// Return true if 24 moves are done and no winner
bool X_O_5X5::is_draw() {
    return (n_moves >= 24 && !is_winner());
}

bool X_O_5X5::game_is_over () {
    return n_moves >= 24;
}

pair<int, int> X_O_5X5::A_I_move() {  //Newwwwwwwwwwwwwwwww
     return {(int) (rand()/(RAND_MAX + 1.0) * 5),(int) (rand()/(RAND_MAX + 1.0) * 5)};
}
