//
// Created by Mazen on 12/13/2023.
//

#include "X_O_Board.h"

#include <bits/stdc++.h>
using namespace std;

// Set the board
X_O_Board::X_O_Board () {
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
bool X_O_Board::update_board (int x, int y, char mark){
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
void X_O_Board::display_board() {
    for (int i: {0,1,2,3,4}) {
        cout << "\n| ";
        for (int j: {0,1,2,3,4}) {
            cout << "(" << i << "," << j << ")";
            cout << setw(4) << board [i][j] << " |"; //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
        }
        cout << "\n-----------------------------";
    }
    cout << endl;
}

// Returns true if there is any winner
// either X or O
// Written in a complex way. DO NOT DO LIKE THIS.
bool X_O_Board::is_winner() {

    char row_win[15], col_win[15], diag_win[18];
    for (int i:{0,1,2}) {
        for (int j:{0,1,2}) {
            row_win[i] = board[i][j] & board[i][j+1] & board[i][j+2];
            col_win[i] = board[j][i] & board[j][i+1] & board[j][i+2];
        }
    }

    // Check diagonals for potential wins
    int index = 0;
    // Primary diagonals from top-left to bottom-right
    for (int i = 0; i <= 2; ++i) { //3
        diag_win[index++] = board[i][i] == board[i + 1][i + 1] && board[i + 1][i + 1] == board[i + 2][i + 2];
    }

    // Secondary diagonals from top-right to bottom-left
    for (int i = 0; i <= 2; ++i) { //3
        diag_win[index++] = board[i][4 - i] == board[i + 1][3 - i] && board[i + 1][3 - i] == board[i + 2][2 - i];
    }

    // Additional diagonals
    diag_win[index++] = board[0][2] == board[1][3] && board[1][3] == board[2][4];
    diag_win[index++] = board[2][0] == board[3][1] && board[3][1] == board[4][2];
    diag_win[index++] = board[1][0] == board[2][1] && board[2][1] == board[3][2];
    diag_win[index++] = board[0][1] == board[1][2] && board[1][2] == board[2][3];
    diag_win[index++] = board[2][1] == board[3][2] && board[3][2] == board[4][3];
    diag_win[index++] = board[1][2] == board[2][3] && board[2][3] == board[3][4];

    diag_win[index++] = board[0][2] == board[1][1] && board[1][1] == board[2][0];
    diag_win[index++] = board[2][4] == board[3][3] && board[3][3] == board[4][2];
    diag_win[index++] = board[1][4] == board[2][3] && board[2][3] == board[3][2];
    diag_win[index++] = board[2][3] == board[3][2] && board[3][2] == board[4][1];
    diag_win[index++] = board[0][3] == board[1][2] && board[1][2] == board[2][1];
    diag_win[index++] = board[1][2] == board[2][1] && board[2][1] == board[3][0];


    for (int i:{0,1,2,3,4}) {
        if ( (row_win[i] && (row_win[i] == board[i][0])) ||
             (col_win[i] && (col_win[i] == board[0][i])) )
        {return true;}
    }
    if ((diag_win[0] && diag_win[0] == board[1][1]) ||
        (diag_win[1] && diag_win[1] == board[1][1]))
    {return true;}
    return false;
}

// Return true if 9 moves are done and no winner
bool X_O_Board::is_draw() {
    return (n_moves == 24 && !is_winner());
}

bool X_O_Board::game_is_over () {
    return n_moves >= 24;
}
