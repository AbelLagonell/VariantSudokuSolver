#pragma once
#include <iostream>
#include "Cell.cpp"

class Array2DCells{
private:
    Cell array2D[VALUES][VALUES];

public:
    //*Constructor if nothing given
    Array2DCells(){
        for (int r=0; r<VALUES; r++){
            for (int c=0; c<VALUES; c++){
                Initialize(array2D[r][c].getArray(), VALUES, true);
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
            if (r!=row) array2D[r][column].setValueBUT(index);
        }
    }

    //* Sets the COlumn to not have the index apart from the given cell positions
    void setColumnBUT(int row[], int size, int column, int index){
        for (int r=0; r<VALUES; r++){
            for (int i =0; i<size; i++){ 
                //? Put in a check for each of the array values
                array2D[r][column].setValueBUT(index);
            }
        }
    }
};