// Class definition for Pyramid_X_O class
// Author:  Ahmed Elkholy
// Date:    5/12/2023
// Version: 1
#include <iostream>
#include <random>
#include <iomanip>
#include <algorithm>
#include "../include/Board_Games.hpp"
using namespace std;

// Set the board
Pyramid_X_O::Pyramid_X_O () {
   n_rows = n_cols = 5;
   board = new char*[n_rows];
   for (int i = 0; i < n_rows; i++) {
      board [i] = new char[n_cols];                       //Done!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
      for (int j = 0; j < n_cols; j++)
         board[i][j] = 0;
   }
}

void Pyramid_X_O::remove_board(int x, int y) {
    board[x][y]=0;
    n_moves--;
}

bool Pyramid_X_O::is_valid_move(int x, int y) {                     //Newwwwwwwwwwwwwwwwwwwww
    // Check if the cell at position (x, y) is empty
    if(((x==0&&y==2)||(x==1&&y==1)||(x==1&&y==2)||(x==1&&y==3)||(x==2&&y==0)||(x==2&&y==1)||(x==2&&y==2)||(x==2&&y==3)||(x==2&&y==4))&&board[x][y]==0){
        return true;
    }else{
        return false;
    }
}

// Return true  if move is valid and put it on board
// within board boundaries in empty cell
// Return false otherwise
bool Pyramid_X_O::update_board (int x, int y, char mark)  {
   // Only update if move is valid
   if (is_valid_move(x,y)) {
      board[x][y] = toupper(mark);                                    //Done!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
      n_moves++;
      return true;
   }
   else
      return false;
}

// Display the board and the pieces on it
void Pyramid_X_O::display_board() {
    for (int i = 0; i < 3; ++i) {
        if (i==0) cout <<"              ";
        if (i==1) cout <<"    ";
        for (int j = 0; j < 3 + i; ++j) {
            if (j >= 3 - 1 - i && j <= 3 - 1 + i) {
                cout << "(" << i << "," << j << ")";            //Done!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                cout<<"| ";
                cout <<board [i][j];
                cout<<" |";
            } else {
                cout <<setw(7);
            }
        }
        cout << "\n";
    }
    cout << endl;
}

// Returns true if there is any winner
// either X or O
// Written in a complex way. DO NOT DO LIKE THIS.
bool Pyramid_X_O::is_winner() {
    char row_win[4], col_win[1], diag_win[2];

    row_win [0] = board[1][1] & board[1][2] & board[1][3];
    row_win [1] = board[2][1] & board[2][2] & board[2][3];
    row_win [2] = board[2][0] & board[2][1] & board[2][2];
    row_win [3] = board[2][2] & board[2][3] & board[2][4];
    col_win [0] = board[0][2] & board[1][2] & board[2][2];
    diag_win[0] = board[0][2] & board[1][3] & board[2][4];
    diag_win[1] = board[0][2] & board[1][1] & board[2][0];


    if ( (row_win[0] && (row_win[0] == board[1][2]))) return true;
    if ( (row_win[1] && (row_win[1] == board[2][2]))) return true;
    if ( (row_win[2] && (row_win[2] == board[2][1]))) return true;
    if ( (row_win[3] && (row_win[3] == board[2][3]))) return true;
    if ( (col_win[0] && (col_win[0] == board[0][2]))) return true;
    if ((diag_win[0] && diag_win[0] == board[0][2]) ||
        (diag_win[1] && diag_win[1] == board[0][2]))
    {return true;}

    return false;

}

pair<int,int> Pyramid_X_O::A_I_move() {         //Newwwwwwwwwwwwwwwwwwwww
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 5; j++) {
            if (is_valid_move(i,j)) {
                board[i][j]='o';
                if (is_winner()) {
                    board[i][j]=0;
                    return {i, j};
                }
                board[i][j]=0;
            }
        }
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 5; j++) {
            if (is_valid_move(i,j)) {
                board[i][j]='x';
                if (is_winner()) {
                    board[i][j]=0;
                    return {i, j};
                }
                board[i][j]=0;
            }
        }
    }

    while (true) {
        int x = rand() % 3;
        int y = rand() % 5;
        if (is_valid_move(x,y)) {
            return {x, y};
        }
    }
}

// Return true if 9 moves are done and no winner
bool Pyramid_X_O::is_draw() {
    return (n_moves == 9 && !is_winner());                             //Done!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
}

bool Pyramid_X_O::game_is_over () {
    return n_moves >= 9;                                                //Done!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
}

