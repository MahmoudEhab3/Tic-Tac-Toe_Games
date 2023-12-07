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
    vector<vector<bool> > grid;
public:
    Universe(int rows,int columns) : rows(rows),columns(columns){
        grid.resize(rows, vector<bool>(columns, false));
    }
    void initialize() {
        srand(time(nullptr));
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                grid[i][j] = rand() %2 ==0;
            }
        }
    }
    void resest(){
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
             grid[i][j] = false;
            }
        }
    }
    int count_neighbors(int row,int col){
        int count = 0;
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                if (i == 0 && j == 0) {
                    continue;  // Skip the current cell
                }
                int neighborRow = (row + i + rows) % rows;
                int neighborColumn = (col + j + columns) % columns;
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
                    std::cout << 'O';
                } else {
                    std::cout << '.';
                }
            }
            std::cout << '\n';
        }
        std::cout << '\n';
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
    int columns = 50;
    int iterations = 2;

    Universe universe(rows, columns);
    universe.run(iterations);

}
