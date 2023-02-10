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
#define NUMOFRULES 1

class Board{
private:
    Cell board[GRID][GRID];
    bool Columns[GRID],
         Rows[GRID], 
         Quadrants[GRID];

    //*Prints the cell at the given row and column
    void printCell(int row, int column){
        board[row][column].printArray();
    }

    //*Prints the given array of size GRID
    void printArr(int arr[]){
        printArr(arr, GRID);
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
                board[i][j].setValue(value);
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

    //*Sets it so that the row cannot have the same number
    void setRow(int row){
        bool arr[GRID];
        Initialize(arr, GRID);
        //Checks if the cell is solved and if it is, it sets the index of the array to true
        for (int i=0; i<GRID; i++){
            if(board[row][i].getSolved()){
                arr[board[row][i].giveSingularity()] = true;
            }
        }
        //Checks if the cell is not solved and according to the array sets the values to false
        for (int i=0; i<GRID; i++){
            if(!board[row][i].getSolved()){
                for (int j=0; j<GRID; j++){
                    if(arr[j])
                        board[row][i].setSingularValue(j);
                }
            }
        }
    }

    //*Sets it so that the column cannot have the same number
    void setColumn(int column){
        bool arr[GRID];
        Initialize(arr, GRID);
        //Checks if the cell is solved and if it is, it sets the index of the array to true
        for (int i=0; i<GRID; i++){
            if(board[i][column].getSolved()){
                arr[board[i][column].giveSingularity()] = true;
            }
        }
        //Checks if the cell is not solved and according to the array sets the values to false
        for (int i=0; i<GRID; i++){
            if(!board[i][column].getSolved()){
                for (int j=0; j<GRID; j++){
                    if(arr[j])
                        board[i][column].setSingularValue(j);
                }
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
                    arr[board[i][j].giveSingularity()] = true;
                }
            }
        }
        //Checks if the cell is not solved and according to the array sets the values to false
        for(int i = cRow; i<3+cRow;i++){
            for (int j =cColumn; j<3+cColumn; j++){
                if(!board[i][j].getSolved()){
                    for (int k=0; k<GRID; k++){
                        if(arr[k])
                            board[i][j].setSingularValue(k);
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
            usedIndexes[board[row][i].giveSingularity()] = true;
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
            usedIndexes[board[i][column].giveSingularity()] = true;
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
                    usedIndexes[board[i][j].giveSingularity()] = true;
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

    //*Checks if there is a pair in the square
    //? Currently does nothing
    void pairInSquare(int squareIndex){
        int anchorX = 3*floor(squareIndex/3),
            anchorY = 3*(squareIndex%3),
            posX[3] = {0, 0, 0},
            posY[3] = {0, 0, 0},
            apperances[9] = {0,0,0,0,0,0,0,0,0};
        bool sameX = false,
             sameY = false;

        for (int row =0; row<3; row++){
            for (int col =0; col<3; col++){
                if(!board[anchorX+row][anchorY+col].getSolved()){
                    addToArray( apperances, board[anchorX+row][anchorY+col].getValue());
                }
            }
        }
        for (int i=0; i<9; i++){
            if(apperances[i] == 3 || apperances[i] == 2){
                for (int row =0; row<3; row++){
                    for (int col =0; col<3; col++){
                        if(!board[anchorX+row][anchorY+col].getSolved() && board[anchorX+row][anchorY+col].getValue()[i]){
                             if (squareIndex == 5)
                                cout << "Found a " << i+1 << " at " << anchorX+row << ", " << anchorY+col << endl; 
                            for (int pos=0; pos<3; pos++){
                                if(posX[pos] == 0){
                                    posX[pos] = anchorX+row;
                                    posY[pos] = anchorY+col;
                                    break;
                                }
                            }
                        }
                    }
                }
            }
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
        int i = 0;
        while(!BoardSolved() && i<3){
            for (int i=0; i<GRID; i++){
                for (int j=0; j<GRID; j++){
                    if(board[i][j].getSolved()){
                        standardRule(i,j);
                    }
                    pairInSquare(i);
                }
            }
            i++;
        }
        cout << endl;
        printBoard();
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
         {{8, 7, 9, 0, 4, 0, 0, 0, 0},
          {6, 0, 0, 0, 0, 2, 9, 0, 0},
          {0, 0, 0, 0, 0, 7, 0, 8, 0},
          {0, 2, 4, 0, 0, 6, 0, 0, 3},
          {0, 0, 1, 0, 0, 0, 2, 0, 0},
          {3, 0, 0, 2, 0, 0, 4, 9, 0},
          {0, 4, 0, 8, 0, 0, 0, 0, 0},
          {0, 0, 3, 7, 0, 0, 0, 0, 4},
          {0, 0, 0, 0, 5, 0, 3, 6, 8}};

    Board b(board);

    b.printBoard();
    b.Solve();
    
    Board b2(ezBoard);

    b2.Solve();
    
    return 0;
}
