/**
 * @file NewBoard.cpp
 * @author Abel Lagonell (alagonell1730@floridapoly.edu)
 * @brief Sudoku solver using custom class Cell and Board in which the board is a 9x9 array of Cell objects.
 * @version 0.1
 * @date 2023-02-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <cmath>
#include <iostream>
#include "Cell.cpp"

using namespace std;

#define GRID 9

class Board{
private:
    Cell board[GRID][GRID]; //Holding the board
    bool solved = false; //Is the board solved or not

    //*checks if Board is solved
    bool BoardSolved(){
        return true;
    }

    //*Checks a singular row to see if the row is solved
    bool checkRow(int row){

    }



public:
    //*Initializes the board with the initial array values given, to be set to the cells in the board
    Board(int arr[GRID][GRID]){
        for(int i = 0; i < GRID; i++){
            for(int j = 0; j < GRID; j++){
                int value = arr[i][j]-1;
                board[i][j].setValueBUT(value);
            }
        }
    }

    //*Prints the board
    void printBoard(){
        cout << "----------------------" <<endl;
        for(int i = 0; i < GRID; i++){
            for(int j = 0; j < GRID; j++){
                board[i][j].printValue();
                if (j == 2 || j == 5){
                    cout << "| ";
                }
            }
            cout << endl;
            if( i == 2 || i == 5 || i == 8)
                cout << "----------------------" <<endl;
        }
        cout << "----------------------" <<endl;
    }

    //*Solves the board
    void Solve(){
        int i = 1;
        while(!BoardSolved() && i<4){
            for (int i=0; i<GRID; i++){
                for (int j=0; j<GRID; j++){
                    if(board[i][j].getSolved()){
                    }
                }
            }
            i++;
            printBoard();
        }
        cout << endl;
    }

};

int main(){
    int ezBoard[9][9] 
         {{5, 3, 0, 0, 7, 0, 0, 0, 0},
          {6, 0, 0, 1, 9, 5, 0, 0, 0},
          {0, 9, 8, 0, 0, 0, 0, 6, 0},
          {8, 0, 0, 0, 6, 0, 0, 0, 3},
          {4, 0, 0, 8, 0, 3, 0, 0, 1},
          {7, 0, 0, 0, 2, 0, 0, 0, 6},
          {0, 6, 0, 0, 0, 0, 2, 8, 0},
          {0, 0, 0, 4, 1, 9, 0, 0, 5},
          {0, 0, 0, 0, 8, 0, 0, 7, 9}};

    Board b2(ezBoard);

    b2.Solve();

}