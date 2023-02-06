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

#include <iostream>
#include "Cell.cpp"

using namespace std;

#define GRID 9
#define NUMOFRULES 2

class Board{
private:
    Cell board[GRID][GRID];
    bool Columns[GRID];
    bool Rows[GRID];
    bool Diagonals[2];
    bool Variants[NUMOFRULES] {
        false, //X-Cross 
        false
    };

    void printCell(int row, int column){
        board[row][column].printArray();
    }
    void Initialize(bool arr[], int size){
        for (int i =0; i < size; i++){
            arr[i] = false;
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
        Initialize(Diagonals, 2);
        Initialize(Variants, NUMOFRULES);


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
        for (int i=0; i<GRID; i++){
            usedIndexes[board[row][i].giveSingularity()] = true;
        }
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
        for (int i=0; i<GRID; i++){
            usedIndexes[board[i][column].giveSingularity()] = true;
        }
        for (int i=0; i<GRID; i++){
            if(!usedIndexes[i]){
                return false;
            }
        }
        Columns[column] = true;
        return true;
    }

    //*checks if Board is solved
    bool BoardSolved(bool const rules[]){
        for (int i=0; i<GRID; i++){
            if(!checkRow(i) || !checkColumn(i) || !checkXCross())
                //if(!checkVariants(rules))
                    return false;
        }
        return true;
    }

    //*Solves the board
    void Solve(bool const rules[NUMOFRULES]){
        int i = 0;
        while(!BoardSolved(rules)){
            for (int i=0; i<GRID; i++){
                for (int j=0; j<GRID; j++){
                    if(board[i][j].getSolved()){
                        standardRule(i,j);
                        setXCross();
                        //variantRules(rules);
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

    bool VariantRules(bool const rules[NUMOFRULES]){
        for (int i =0; i< NUMOFRULES; i++)
            if (rules[i])
                return true;
        return false;
    }

    void variantRules(bool const rules[NUMOFRULES]){
        if (VariantRules(rules))
            return;
        if(rules[0]){ 
            setXCross();
        }
    }

    bool checkVariants(bool const rules[NUMOFRULES]){
        if (!VariantRules(rules))
            return true;
        bool checkedRules[NUMOFRULES];
        Initialize(checkedRules, NUMOFRULES);
        if (rules[0])
            checkedRules[0] = checkXCross();
        for (int i =0; i<NUMOFRULES; i++){
            if (!checkedRules[i]){
                return false;
            }
        }
        return true;
    }

    void setXCross(){
        bool arrLeft[GRID] = {false,false,false,false,false,false,false,false,false};
        bool arrRight[GRID] = {false,false,false,false,false,false,false,false,false};
        for (int i = 0; i<GRID; i++){
            if(board[i][i].getSolved()){
                arrLeft[board[i][i].giveSingularity()] = true;
            }
            if(board[i][8-i].getSolved()){
                arrRight[board[i][8-i].giveSingularity()] = true;
            }
        }
        for (int i = 0; i<GRID; i++){
            if(!board[i][i].getSolved()){
                for (int j=0; j<GRID; j++){
                    if(arrLeft[j])
                        board[i][i].setSingularValue(j);
                }
            }
            if(!board[i][8-i].getSolved()){
                for (int j=0; j<GRID; j++){
                    if(arrRight[j])
                        board[i][8-i].setSingularValue(j);
                }
            }
        }
    }

    bool checkXCross(){
        bool usedIndexesLeft[GRID];
        Initialize(usedIndexesLeft, GRID);
        bool usedIndexesRight[GRID];
        Initialize(usedIndexesLeft, GRID);
        if(Diagonals[0] && Diagonals[1]){
            return true;
        }
        for (int i=0; i<GRID; i++){
            usedIndexesLeft[board[i][i].giveSingularity()] = true;
            usedIndexesRight[board[i][8-i].giveSingularity()] = true;
        }
        for (int i=0; i<GRID; i++){
            if(!usedIndexesLeft[i]){
                Diagonals[0] = false;
                return false;
            } else
                Diagonals[0] = true;
            if (!usedIndexesRight[i]){
                Diagonals[1] = false;
                return false;
            } else 
                Diagonals[1] = true;
        }
        return true;
    }
};

int main(){
    int board[9][9] 
         {{0, 0, 0, 1, 0, 6, 0, 3, 2},
          {0, 0, 0, 0, 0, 9, 0, 0, 0},
          {0, 0, 0, 0, 2, 0, 0, 0, 8},
          {3, 6, 0, 0, 0, 5, 9, 0, 0},
          {0, 0, 0, 0, 6, 0, 0, 0, 0},
          {0, 0, 4, 9, 0, 0, 0, 6, 5},
          {2, 0, 0, 0, 8, 0, 0, 0, 0},
          {0, 0, 0, 3, 0, 0, 0, 0, 0},
          {4, 9, 0, 5, 0, 1, 0, 0, 0}};

    Board b(board);

    bool activeRules[NUMOFRULES] = {true,false};

    b.printBoard();
    b.Solve(activeRules);
    return 0;
}
