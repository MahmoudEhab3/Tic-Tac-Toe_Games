// File: A3_S2_20230607_Problem3.cpp
// Purpose: Game of life
// Author: Mazen Abdelfattah
// Section: S2
// ID: 20230607
// TA: Khaled Ibrahim

#include <bits/stdc++.h>
using namespace std;

class Universe{
private:
    int rows,columns;
    vector<vector<bool> > grid; //2D vector of booleans
public:
    Universe(int rows,int columns) : rows(rows),columns(columns){ //Parameterized constructor
        grid.resize(rows, vector<bool>(columns, false) );
    }
    void initialize() { //to initialize the cells
        //We will use 'srand' to randomly choose the places of the cells
        //The srand and rand functions in C++ are used for generating pseudo-random numbers.
        srand(time(nullptr));
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                grid[i][j] = rand() %2 ==0;
            }
        }
    }
    void resest(){ //Set all cells as dead
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
             grid[i][j] = false;
            }
        }
    }
    int count_neighbors(int row,int col){//To return the number of alive cells around SPECIFIC cell
        int count = 0;                   //We use it in 'next generation' function
        for (int i = -1; i <= 1; ++i) { //We set the 2 loops -1 0 1 to iterate over the 3*3 square around the cell
            for (int j = -1; j <= 1; ++j) {
                if (i == 0 && j == 0) {
                    continue;  // Skip the current cell
                }
                int neighborRow = (row + i + rows) % rows;          //toroidal (or wrapping) behavior.
                int neighborColumn = (col + j + columns) % columns; //toroidal (or wrapping) behavior.
                if (grid[neighborRow][neighborColumn]) {
                    count++;
                }
            }
        }
        return count;
    }
    void next_generation(){
        vector<vector<bool>> nextGrid = grid;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                int aliveNeighbors = count_neighbors(i, j);
                //Using count_neighbors function to know the alive neighbor cells
                if(grid[i][j]){
                    if(aliveNeighbors < 2 || aliveNeighbors > 3){
                        nextGrid[i][j] = false;
                    }
                    else{
                        if(aliveNeighbors == 3){
                            nextGrid[i][j] = true;
                        }
                    }
                }
            }
        }
        grid = nextGrid;
    }
    void display(){
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                if (grid[i][j]) { 
                    cout << '*';
                } else {
                    cout << '.';
                }
            }
            cout << '\n';
        }
        cout << '\n';
    }
    void run(int iterations){
        initialize();
        for (int i = 0; i < iterations; ++i) {
            display();
            next_generation();
        }
    }
};

int main() {
    int rows = 20;
    int columns = 20;
    int iterations = 5;

    Universe universe(rows, columns);
    universe.run(iterations);
}
