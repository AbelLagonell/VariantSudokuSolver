/**
 * @file Array2DCells.cpp
 * @author Abel Lagonell (alagonell1730@floridapoly.edu)
 * @brief A background file that contains functions to help manipulate the Cell class in a 2D array environment. Allowing NewBoard.cpp to be more readable.
 * @version 1.3.1
 * @date 2023-02-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#pragma once
#include <iostream>
#include "Cell.cpp"

using namespace std;

class Array2DCells{
protected:
    Cell array2D[VALUES][VALUES];

public:
    //*Constructor if nothing given
    Array2DCells(){
        for (int r=0; r<VALUES; r++){
            for (int c=0; c<VALUES; c++){
                array2D[r][c].setValue(-1);
            }
        }
    }

    //* Constructor if given int array
    Array2DCells(int arr[VALUES][VALUES]){
        for (int r=0; r<VALUES; r++){
            for (int c=0; c<VALUES; c++){
                array2D[r][c].setValueBUT(arr[r][c]-1);
            }
        }
    }

    //* Sets the Column to not have the index apart from the given cell position
    void setColumnBUT(int row, int column, int index){
        for (int r=0; r<VALUES; r++){
            if (r!=row) getCell(r,column).setValue(index);
        }
    }

    //* Sets the Column to not have the index apart from the given cell positions
    void setColumnBUT(int row[], int size, int column, int index){
        bool check = false;
        for (int r=0; r<VALUES; r++){
            for (int i =0; i<size; i++)
                if (r==row[i]) check = true;
            if (!check) array2D[r][column].setValue(index);
        }
    }

    //* Sets the Row to not have the index apart from the given cell position
    void setRowBUT(int row, int column, int index){
        for (int c=0; c<VALUES; c++){
            if (c!=column) array2D[row][c].setValue(index);
        }
    }

    //* Sets the Row to not have the index apart from the given cell positions
    void setRowBUT(int column[], int size, int row, int index){
        bool check = false;
        for (int c=0; c<VALUES; c++){
            for (int i =0; i<size; i++)
                if (c==column[i]) check = true;
            if (!check) array2D[row][c].setValue(index);
        }
    }

    //* Sets the Square to not have the index apart from the given cell position
    void setSquareBUT(int row, int column, int index){
        int cRow = row - (row%3);
        int cColumn = column - (column%3);
        for(int i = cRow; i<3+cRow;i++){
            for (int j =cColumn; j<3+cColumn; j++){
                if(i!=row && j!=column){
                    array2D[i][j].setValue(index);
                }
            }
        }
    }

    //* Sets the Square to not have the index apart from the given cell positions
    void setSquareBUT(int row[], int column[], int size, int index){
        int cRow = row[0] - (row[0]%3);
        int cColumn = column[0] - (column[0]%3);
        bool check = false;
        for(int i = cRow; i<3+cRow;i++){
            for (int j =cColumn; j<3+cColumn; j++){
                for (int k =0; k<size; k++){
                    if (i==row[k]) check = true;
                    if (j==column[k]) check = true;
                }
                if(!check && !array2D[i][j].getSolved()){
                    array2D[i][j].setValue(index);
                }
            }
        }
    }

    //* Checks if the row has one of every value
    bool checkRow(int row){
        bool present[VALUES];
        Initialize(present, VALUES, false);
        //Goes through the row taking note of all the used indexes
        for (int i=0; i<VALUES; i++){
            if (array2D[row][i].getSolved()) present[CheckSingle(array2D[row][i].getArray(), VALUES)] = true;
        }
        //Makes sure that all the indexes are used
        for (int i=0; i<VALUES; i++){
            if(!present[i]){
                return false;
            }
        }
        return true;
    }

    //* Checks if the column has one of every value
    bool checkColumn(int column){
        bool present[VALUES];
        Initialize(present, VALUES, false);
        //Goes through the column taking note of all the used indexes
        for (int i=0; i<VALUES; i++){
            if (array2D[i][column].getSolved()) present[CheckSingle(array2D[i][column].getArray(), VALUES)] = true;
        }
        //Makes sure that all the indexes are used
        for (int i=0; i<VALUES; i++){
            if(!present[i]){
                return false;
            }
        }
        return true;
    }

    //* Checks if the quadrant has one of every value
    bool checkSquare(int row, int column){
        bool present[VALUES];
        Initialize(present, VALUES, false);
        int cRow = row - (row%3);
        int cColumn = column - (column%3);
        //Goes through the quadrant taking note of all the used indexes
        for(int i = cRow; i<3+cRow;i++){
            for (int j =cColumn; j<3+cColumn; j++){
                if(array2D[i][j].getSolved()){
                    present[CheckSingle(array2D[i][j].getArray(), VALUES)] = true;
                }
            }
        }
        //Checks if all the indexes are used
        for (int i=0; i<VALUES; i++){
            if(!present[i]){
                return false;
            }
        }
        return true;
    }

    //*Counts the number of possibilities that a particular number has
    void enumeratePosiibilities(int *arr, int type, int section){
        switch (type){
            case 0:
                //Row
                for (int i=0; i<VALUES; i++){
                addToArray(arr,array2D[section][i].getArray(),9);
                }
                break;
            case 1:
                //Column
                for (int i=0; i<VALUES; i++){
                    addToArray(arr,array2D[i][section].getArray(),9);
                }
                break;
            case 2:
                //Quadrant
                int anchorX = 3*floor(section/3),
                anchorY = 3*(section%3);
                for (int row =0; row<3; row++){
                    for (int col =0; col<3; col++){
                        if(!array2D[anchorX+row][anchorY+col].getSolved()){
                            addToArray(arr, array2D[anchorX+row][anchorY+col].getArray(), 9);
                        }
                    }
                }
                break;
        }        
    }

    void setTheOne(int type, int section, int index){
        switch (type){
            //ROW
            case 0: 
                for (int i=0; i<VALUES; i++){
                    if (array2D[section][i].getArray()[index] == 1){
                        array2D[section][i].setValueBUT(index);
                    }
                }
                break;
            //COLUMN
            case 1:
                for (int i=0; i<VALUES; i++){
                    if (array2D[i][section].getArray()[index] == 1){
                        array2D[i][section].setValueBUT(index);
                    }
                }
                break;
            //QUADRANT
            case 2:
                int anchorX = 3*floor(section/3),
                    anchorY = 3*(section%3);
                for (int row =0; row<3; row++){
                    for (int col =0; col<3; col++){
                        if(!array2D[anchorX+row][anchorY+col].getArray()[index] == 1){
                            array2D[anchorX+row][anchorY+col].setValueBUT(index);
                        }
                    }
                }
                break;
        }
    }

    //* Checks for a one in the array given and returns the index
    int checkForOne(const int arr[]){
        for (int i =0; i<VALUES; i++){
            if (arr[i] == 1) return i;
        }
        return -1;
    }


    void printCell(int row, int column){
        array2D[row][column].printArray();
    }

    Cell& getCell(int row, int column){
        return array2D[row][column];
    }

};