/**
 * @file NewBoard.cpp
 * @author Abel Lagonell (alagonell1730@floridapoly.edu)
 * @brief Sudoku solver using custom class Cell and Board in which the board is a 9x9 array of Cell objects.
 * @version 1.4.1
 * @date 2023-02-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <cmath>
#include <iostream>
#include "Array2DCells.cpp"

using namespace std;

class Board : public Array2DCells{
private:
    //*checks if Board is solved
    bool BoardSolved(){
        for (int i=0; i<VALUES; i++){
                if (!checkRow(i) || !checkColumn(i)) return false;
        }
        return true;
    }

    //Sets up the standard rules of Sudoku
    void standardRule(int row, int column){
        int index = CheckSingle(array2D[row][column].getArray(), VALUES);
        setRowBUT(row, column, index);
        setColumnBUT(row, column, index);
        setSquareBUT(row, column, index);
    }

    //Tries to find hidden singles and marks them if it does
    void hiddenSingle(int type, int section){
        int numOfAppear[9];
        enumeratePosiibilities(numOfAppear,type,section);
        int index = checkForOne(numOfAppear);
        if (index != -1){
            setTheOne(type, section, index);
        }
    }

public:
    //*Initializes the board with the initial array values given, to be set to the cells in the board
    Board(int arr[VALUES][VALUES]) : Array2DCells(arr) {}

    //*Prints the board
    void printBoard(){
        cout << "----------------------" <<endl;
        for(int i = 0; i < VALUES; i++){
            for(int j = 0; j < VALUES; j++){
                array2D[i][j].printValue();
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
        while(!BoardSolved()){
            for (int i=0; i<VALUES; i++){
                for (int j=0; j<VALUES; j++){
                    if(array2D[i][j].getSolved()){
                        standardRule(i, j);
                    }
                }
                hiddenSingle(0,i);
                hiddenSingle(1,i);
                hiddenSingle(2,i);
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

    return 0;
}