/**
 * @file Board.cpp
 * @author Abel Lagonell (alagonell1730@floridapoly.edu)
 * @brief Sudoku solver using custom class Cell and Board in which the board is a 9x9 array of Cell objects.
 * @version 1.0
 * @date 2023-02-03
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <iostream>
#include "Cell.cpp"

using namespace std;

class Board{
private:
    Cell board[9][9];
    bool Quadrants[9] = {false,false,false,false,false,false,false,false,false};
    bool Columns[9] = {false,false,false,false,false,false,false,false,false};
    bool Rows[9] = {false,false,false,false,false,false,false,false,false};

    void printCell(int row, int column){
        board[row][column].printArray();
    }

public:
    //*Initializes the board with the initial array values given, to be set to the cells in the board
    Board(int arr[9][9]){
        for(int i = 0; i < 9; i++){
            for(int j = 0; j < 9; j++){
                int value = arr[i][j]-1;
                board[i][j].setValue(value);
            }
        }
    }

    //*Prints the board
    void printBoard(){
        cout << "----------------------" <<endl;
        for(int i = 0; i < 9; i++){
            for(int j = 0; j < 9; j++){
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
        bool arr[9] = {false,false,false,false,false,false,false,false,false};
        //Checks if the cell is solved and if it is, it sets the index of the array to true
        for (int i=0; i<9; i++){
            if(board[row][i].getSolved()){
                arr[board[row][i].giveSingularity()] = true;
            }
        }
        //Checks if the cell is not solved and according to the array sets the values to false
        for (int i=0; i<9; i++){
            if(!board[row][i].getSolved()){
                for (int j=0; j<9; j++){
                    if(arr[j])
                        board[row][i].setSingularValue(j);
                }
            }
        }
    }

    //*Sets it so that the column cannot have the same number
    void setColumn(int column){
        bool arr[9] = {false,false,false,false,false,false,false,false,false};
        //Checks if the cell is solved and if it is, it sets the index of the array to true
        for (int i=0; i<9; i++){
            if(board[i][column].getSolved()){
                arr[board[i][column].giveSingularity()] = true;
            }
        }
        //Checks if the cell is not solved and according to the array sets the values to false
        for (int i=0; i<9; i++){
            if(!board[i][column].getSolved()){
                for (int j=0; j<9; j++){
                    if(arr[j])
                        board[i][column].setSingularValue(j);
                }
            }
        }
    }
    
    //*Sets it so that the quadrant cannot have the number
    void setSquare(int row, int column){
        bool arr[9] = {false,false,false,false,false,false,false,false,false};
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
                    for (int k=0; k<9; k++){
                        if(arr[k])
                            board[i][j].setSingularValue(k);
                    }
                }
            }
        }        
    }

    //*Checks a singular row to see if the row is solved
    bool checkRow(int row){
        bool usedIndexes[9] = {false,false,false,false,false,false,false,false,false};
        if(Rows[row]){
            return true;
        }
        for (int i=0; i<9; i++){
            usedIndexes[board[row][i].giveSingularity()] = true;
        }
        for (int i=0; i<9; i++){
            if(!usedIndexes[i]){
                return false;
            }
        }
        Rows[row] = true;
        return true;
    }

    //*Checks a singular column to see if the column is solved
    bool checkColumn(int column){
        bool usedIndexes[9] = {false,false,false,false,false,false,false,false,false};
        if(Columns[column]){
            return true;
        }
        for (int i=0; i<9; i++){
            usedIndexes[board[i][column].giveSingularity()] = true;
        }
        for (int i=0; i<9; i++){
            if(!usedIndexes[i]){
                return false;
            }
        }
        Columns[column] = true;
        return true;
    }

    //*checks if Board is solved
    bool BoardSolved(){
        for (int i=0; i<9; i++){
            if(!checkRow(i) || !checkColumn(i)){
                return false;
            }
        }
        return true;
    }

    //*Solves the board
    void Solve(){
        int i = 0;
        while(!BoardSolved()){
            for (int i=0; i<9; i++){
                for (int j=0; j<9; j++){
                    if(board[i][j].getSolved()){
                        standardRule(i,j);
                    }
                }
            }
            i++;
            loading(i);
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
    int board[9][9] 
         {{5, 3, 0, 0, 7, 0, 0, 0, 0},
          {6, 0, 0, 1, 9, 5, 0, 0, 0},
          {0, 9, 8, 0, 0, 0, 0, 6, 0},
          {8, 0, 0, 0, 6, 0, 0, 0, 3},
          {4, 0, 0, 8, 0, 3, 0, 0, 1},
          {7, 0, 0, 0, 2, 0, 0, 0, 6},
          {0, 6, 0, 0, 0, 0, 2, 8, 0},
          {0, 0, 0, 4, 1, 9, 0, 0, 5},
          {0, 0, 0, 0, 8, 0, 0, 7, 9}};

    Board b(board);

    b.printBoard();
    b.Solve();
    return 0;
}
