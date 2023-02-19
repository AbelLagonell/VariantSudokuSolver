/**
 * @file Board.cpp
 * @author Abel Lagonell (alagonell1730@floridapoly.edu)
 * @brief Sudoku solver using custom class Cell and Board in which the board is a GRIDxGRID array of Cell objects.
 * @version 2.0
 * @date 2023-02-03
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
    Cell board[GRID][GRID];
    bool Columns[GRID],
         Rows[GRID], 
         Quadrants[GRID];

    //*Prints the cell at the given row and column
    void printCell(int row, int column){
        PrintArray(board[row][column].getArray(), GRID);
    }

    //*Prints the given array of size GRID
    void printArr(int arr[]){
        printArr(arr, GRID);
    }

    void printArr(bool arr[]){
        for (int i = 0; i < GRID; i++){
            cout << ((arr[i])? i+1:0) << ", ";
        }
    }

    //*Prints the given array of any size
    void printArr(int arr[], int size){
        for (int i = 0; i < size; i++){
            cout << arr[i] << ", ";
        }
        cout << endl;
    }

    //*Sets array to false for all indexes
    void Initialize(bool arr[], int size){
        for (int i =0; i < size; i++){
            arr[i] = false;
        }
    }

    //*Sets array to 0 for all indexes
    void Initialize(int arr[], int size){
        for (int i =0; i < size; i++){
            arr[i] = 0;
        }
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
        Initialize(Columns, GRID);
        Initialize(Rows, GRID);
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

    //*implements the row, column, and box implementation to put all the indexes of the already set values to false
    void standardRule(int row, int column) {
        setRow(row);
        setColumn(column);
        setSquare(row,column);
    }

    void hiddenStrategies(){
        for (int i = 0; i < GRID; i++){
            hiddenSingles(i);
        }
    }

    //*Sets it so that the row cannot have the same number
    void setRow(int row){
        bool arr[GRID],
             found = false;
        Initialize(arr, GRID);
        //Checks if the cell is solved and if it is, it sets the index of the array to true and Checks if the cell is not solved and according to the array sets the values to false
        for (int i=0; i<GRID; i++){
            if(board[row][i].getSolved()){
                arr[CheckSingle(board[row][i].getArray(),GRID)] = true;
                found = true;
            }
            if(!board[row][i].getSolved() && found){
                for (int j=0; j<GRID; j++){
                    if(arr[j])
                        SetIndex(board[row][i].getArray(), GRID, j, false);
                }
            }
            found = false;
        }
        
    }

    //*Sets it so that the column cannot have the same number
    void setColumn(int column){
        bool arr[GRID],
             found = false;
        Initialize(arr, GRID);
        //Checks if the cell is solved and if it is, it sets the index of the array to true and Checks if the cell is not solved and according to the array sets the values to false
        for (int i=0; i<GRID; i++){
            if(board[i][column].getSolved()){
                arr[CheckSingle(board[i][column].getArray(), GRID)] = true;
                found = true;
            }
            if(!board[i][column].getSolved() && found){
                for (int j=0; j<GRID; j++){
                    if(arr[j])
                        SetIndex(board[i][column].getArray(), GRID, j, false);
                }
            }
            found = false;
        }
        
    }

    //* Sets the column to not include the index apart from the cells that are in the square provided
    void setColumn(int column, int squareIndex, int index){
        for (int row=0; row<GRID; row++){
            if(!board[row][column].getSolved() && 3*floor(row/3) + floor(column/3) != squareIndex){
                standardRule(row,column);
                SetIndex(board[row][column].getArray(), GRID, index, false);
            }
        }
    }

    //* Sets the row to not include the index apart from the cells that are in the square provided
    void setRow(int row, int squareIndex, int index){
        for (int column=0; column<GRID; column++){
            if(!board[row][column].getSolved() && 3*floor(row/3) + floor(column/3) != squareIndex){
                standardRule(row,column);
                SetIndex(board[row][column].getArray(), GRID, index, false);
            }
        }
    }

    //*Sets it so that the quadrant cannot have the number
    void setSquare(int row, int column){
        bool arr[GRID];
        Initialize(arr, GRID);
        int cRow = row - (row%3);
        int cColumn = column - (column%3);

        for(int i = cRow; i<3+cRow;i++){
            for (int j =cColumn; j<3+cColumn; j++){
                if(board[i][j].getSolved()){
                    arr[CheckSingle(board[i][j].getArray(), GRID)] = true;
                }
            }
        }
        //Checks if the cell is not solved and according to the array sets the values to false
        for(int i = cRow; i<3+cRow;i++){
            for (int j =cColumn; j<3+cColumn; j++){
                if(!board[i][j].getSolved()){
                    for (int k=0; k<GRID; k++){
                        if(arr[k])
                            SetIndex(board[i][j].getArray(), GRID, k, false);
                    }
                }
            }
        }        
    }

    //*Checks a singular row to see if the row is solved
    bool checkRow(int row){
        bool usedIndexes[GRID];
        Initialize(usedIndexes, GRID);
        if(Rows[row]){
            return true;
        }
        //Goes through the row taking note of all the used indexes
        for (int i=0; i<GRID; i++){
            usedIndexes[CheckSingle(board[row][i].getArray(), GRID)] = true;
        }
        //Makes sure that all the indexes are used
        for (int i=0; i<GRID; i++){
            if(!usedIndexes[i]){
                return false;
            }
        }
        Rows[row] = true;
        return true;
    }

    //*Checks a singular column to see if the column is solved
    bool checkColumn(int column){
        bool usedIndexes[GRID] = {false,false,false,false,false,false,false,false,false};
        if(Columns[column]){
            return true;
        }
        //Goes through the column taking note of all the used indexes
        for (int i=0; i<GRID; i++){
            usedIndexes[CheckSingle(board[i][column].getArray(), GRID)] = true;
        }
        //Makes sure that all the indexes are used
        for (int i=0; i<GRID; i++){
            if(!usedIndexes[i]){
                return false;
            }
        }
        Columns[column] = true;
        return true;
    }

    //* Checks a singular quadrant to see if the quadrant is solved
    bool checkSquare(int row, int column){
        bool usedIndexes[GRID];
        Initialize(usedIndexes, GRID);
        int cRow = row - (row%3);
        int cColumn = column - (column%3);
        if (Quadrants[(cRow%3)*3+cColumn%3])
            return true;
        //Goes through the quadrant taking note of all the used indexes
        for(int i = cRow; i<3+cRow;i++){
            for (int j =cColumn; j<3+cColumn; j++){
                if(board[i][j].getSolved()){
                    usedIndexes[CheckSingle(board[i][j].getArray(), GRID)] = true;
                }
            }
        }
        //Checks if all the indexes are used
        for (int i=0; i<GRID; i++){
            if(!usedIndexes[i]){
                return false;
            }
        }
        Quadrants[(cRow%3)*3+cColumn%3] = true;
        return true;
        
    }

    void hiddenSingles(int squareIndex){
        int anchorX = 3*floor(squareIndex/3),
            anchorY = 3*(squareIndex%3),
            appearances[9] = {0,0,0,0,0,0,0,0,0};
        numberOfAppearancesQUADRANT(appearances, squareIndex);
        cout << "Square " << squareIndex << " appearances: \t";
        printArr(appearances, 9);
        for (int i=0; i<9; i++){
            if(appearances[i] == 1){
                for (int row =0; row<3; row++){
                    for (int col =0; col<3; col++){
                        if(board[anchorX+row][anchorY+col].getArray()[i]){
                            SetIndex(board[anchorX+row][anchorY+col].getArray(), GRID, i, false);
                        }
                    }
                }
            }
        }
    }

    //*Counts the number of appearances
    void numberOfAppearancesQUADRANT (int appearances[9], int squareIndex){
        int anchorX = 3*floor(squareIndex/3),
            anchorY = 3*(squareIndex%3);
        for (int row =0; row<3; row++){
            for (int col =0; col<3; col++){
                if(!board[anchorX+row][anchorY+col].getSolved()){
                    addToArray( appearances, board[anchorX+row][anchorY+col].getArray());
                }
            }
        }
    }

    //*Checks if there is a pair in the square
    void pairInSquare(int squareIndex){
        int anchorX = 3*floor(squareIndex/3),
            anchorY = 3*(squareIndex%3),
            posX[3] = {0, 0, 0},
            posY[3] = {0, 0, 0},
            appearances[9] = {0,0,0,0,0,0,0,0,0};
        bool sameX = false,
             sameY = false;

        numberOfAppearancesQUADRANT(appearances, squareIndex);
        
        //First checks if there is one instance and then sets it to that square and then uses pairs to dismiss possibilities
        for (int i=0; i<9; i++){
            if(appearances[i] == 3 || appearances[i] == 2){
                for (int row =0; row<3; row++){
                    for (int col =0; col<3; col++){
                        if(!board[anchorX+row][anchorY+col].getSolved() && board[anchorX+row][anchorY+col].getArray()[i]){
                            for (int pos=0; pos<3; pos++){
                                if(posX[pos] == 0){
                                    posX[pos] = anchorX+row;
                                    posY[pos] = anchorY+col;
                                    break;
                                }
                            }
                            if (sameValues(posY) != -1){
                                setColumn(posY[0], squareIndex, i);
                                board[8][2].printArray();
                            }
                            if (sameValues(posX) != -1){
                                setRow(posX[0], squareIndex, i);
                            } 
                        }

                    }
                }
            }
            Initialize(posX,3);
            Initialize(posY,3);

        }
    }

    //*Checks if the array has same values
    int sameValues(int arr[3]){
        bool same = false;
        int sharedIndex = -1;
        if(arr[0] != arr[1] || (arr[1] != arr[2] && arr[2] != 0)){
            return -1;
        }
        return arr[0];
    }

    //*Adds 1 to the index of an array if the value is true
    void addToArray(int arr[], bool value[]){
        for (int i =0; i<GRID; i++){
            if(value[i]){
                arr[i]++;
            }
        }
    }

    //*checks if Board is solved
    bool BoardSolved(){
        for (int i=0; i<GRID; i++){
            if(!checkRow(i) || !checkColumn(i))
                    return false;
        }
        return true;
    }

    //*Solves the board
    void Solve(){
        int i = 1;
        while(!BoardSolved() && i<4){
            for (int i=0; i<GRID; i++){
                for (int j=0; j<GRID; j++){
                    if(board[i][j].getSolved()){
                        cout << "cell: \t";
                        board[8][2].printArray();
                        standardRule(i,j);
                    }
                }
                    //pairInSquare(i);
            }
            hiddenStrategies();
            i++;
            printBoard();
        }
        cout << endl;
    }

    //*Prints out "Loading..." with varying .. for showing program running
    void loading(int i){
        cout << "\rLoading";
        for (int j=0; j<i%4+1; j++){
            if(j!=4)
                cout << ".";
        }
        cout << " (" << i << ")";
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

    int board[9][9] 
         {{0, 0, 0, 7, 0, 4, 0, 0, 5},
          {0, 2, 0, 0, 1, 0, 0, 7, 0},
          {0, 0, 0, 0, 8, 0, 0, 0, 2},
          {0, 9, 0, 0, 0, 6, 2, 5, 0},
          {6, 0, 0, 0, 7, 0, 0, 0, 8},
          {0, 5, 3, 2, 0, 0, 0, 1, 0},
          {4, 0, 0, 0, 9, 0, 0, 0, 0},
          {0, 3, 0, 0, 6, 0, 0, 9, 0},
          {2, 0, 0, 4, 0, 7, 0, 0, 0}};

    Board b(board);

    b.printBoard();
    b.Solve();
    
    Board b2(ezBoard);

    //b2.Solve();
    
    return 0;
}
