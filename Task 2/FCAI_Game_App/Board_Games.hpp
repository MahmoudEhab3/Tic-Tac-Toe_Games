// Class definition for XO_App class
// Author:  Ahmed Elkholy
// Date:    5/12/2023
// Version: 1
#include <SFML/Graphics.hpp>
#ifndef _BoardGame_CLASSES_H
#define _BoardGame_CLASSES_H
using namespace std;

class Board {
protected:
   int n_rows, n_cols;
   char** board;
   int  n_moves = 0;

public:
   // Return true  if move is valid and put it on board
   // within board boundaries in empty cell
   // Return false otherwise
   virtual bool update_board (int x, int y, char symbol) = 0;
   // Returns true if there is any winner
   // either X or O
   // Written in a complex way. DO NOT DO LIKE THIS.
   virtual bool is_winner() = 0;
   // Return true if all moves are done and no winner
   virtual bool is_draw() = 0;
   // Display the board and the pieces on it
   virtual void display_board() = 0;
   // Return true if game is over
   virtual bool game_is_over() = 0;

   virtual pair<int, int> A_I_move() = 0 ;     // Newwwwwwwwwwwwwwwwwwwww
};

///////////////////////////////////////////
// This class represents a 3 x 3 board
// used in X_O game

class X_O_Board:public Board {
public:
    X_O_Board ();
    bool update_board (int x, int y, char mark);
    void display_board();
    bool is_winner();
    bool is_draw();
    pair<int, int> A_I_move();    // Newwwwwwwwwwwwwwwwwwwww
    bool game_is_over();
};

class Pyramid_X_O: public Board {
public:
   Pyramid_X_O ();
   bool update_board (int x, int y, char mark);
   void display_board();
   void remove_board(int x, int y);
   bool is_winner();
   bool is_draw();
   bool game_is_over();
   pair<int, int> A_I_move(); // Newwwwwwwwwwwwwwwwwwwww
   bool is_valid_move(int x, int y);
};

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
    pair<int, int> A_I_move();         // Newwwwwwwwwwwwwwwwwwwww
    bool is_draw();
    bool game_is_over();
    bool update_board (int x, int y, char mark);
    void computer_move();

};

class X_O_5X5: public Board {
private:
    static int count_x;
    static int count_o;
public:
    X_O_5X5 ();
    bool update_board (int x, int y, char mark);
    void display_board();
    pair<int, int> A_I_move();   // Newwwwwwwwwwwwwwwwwwwww
    bool is_winner();
    bool is_draw();
    bool game_is_over();
};


///////////////////////////////////////////
// This class represents a player who has
// a name and a symbol to put on board
class Player {
    protected:
        string name;
        char symbol;
    public:
        // Two constructors to initiate player
        // Give player a symbol to use in playing
        // It can be X or O or others
        // Optionally, you can give him ID or order
        // Like Player 1 and Player 2
        Player (char symbol); // Needed for computer players
        Player (int order, char symbol);
        // Get desired move: x y (each between 0 and 2)
        // Virtual (can change for other player types)
        virtual void get_move(int& x, int& y);
        // Give player info as a string
        string to_string();
        // Get symbol used by player
        char get_symbol();
};

///////////////////////////////////////////
// This class represents a random computer player
// that generates random positions x y (0 to 2)
// If invalid, game manager asks to regenerate
class RandomPlayer: public Player{
    protected:
        int dimension;
        Board* brdptr= nullptr;           //newwwwwwwwwwwwwwwwwwwwwww
    public:
        // Take a symbol and pass it to parent
        RandomPlayer (char symbol, int dimension, Board* brdptr);         //newwwwwwwwwwwwwwwwwwwwww
        // Generate a random move
        void get_move(int& x, int& y);
};

///////////////////////////////////////////
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

#endif
