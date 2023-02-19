/**
 * @file Cell.cpp
 * @author Abel Lagonell (alagonell1730@floridapoly.edu)
 * @brief A cell that contains a value from 0 to 9, with 0 being more than one true value in the array and 1-9 being the position index +1.
 * @version 1.0
 * @date 2023-02-19
 * 
 * @copyright Copyright (c) 2023
 * 
*/

#include <iostream>
#include "CellManip.cpp"

#define VALUES 9

class Cell{
private:
    bool value[VALUES]; //*Holding the cell value from 0-VALUES 
    bool solved = false; //*Is the cell solved or not 

public:

    //*Constructor
    Cell(){
        Initialize(value, VALUES, true);
    }

    /* 
    * ARRAY ACCESS     
    */

    //*Returns the bool array
    bool* getArray(){
        bool* array = new bool[VALUES];
        for(int i = 0; i < VALUES; i++){
            array[i] = value[i];
        }
        return array;
    }

    //*Prints the array
    void printArray(){
        for (int i =0; i < VALUES; i++){
            std::cout << ((value[i] != false)? i+1:0) << " ";
        }
        
    }

    /*
    * VARIABLE "SOLVED" MANIPULATION
    */

    //*Checks if there is a single possibility
    void checkSolved(){
        if (CheckSingle(value, VALUES) != -1)
            solved = true;
    }

    //*Gets the solved var
    bool getSolved(){
        return solved;
    }

    /* 
    * ARRAY "VALUE" MANIPULATION
    */

    //*Setting the index of the cell to false and checking if the cell is solved
    void setValue(int index){
        if (solved){
            return;
        }
        SetIndex(value, VALUES, index, false);
        checkSolved();
    }

    //*Setting the index of the cell making everything but the index position to false
    void setValueBUT(int index){
        if (solved){
            return;
        }
        SetIndexBUT(value, VALUES, index, false);
        solved = true;
    }

    //*Printing the value of the cell if it only has one true value
    void printValue(){
        int num = CheckSingle(value, VALUES);
        std::cout << ((num!=-1)? (num+1):0) << " ";
    }

    /*
    * OVERLOADING OPERATORS
    */

    //*Overloading the == operator
    bool operator == (const Cell& cell){
        for (int i = 0; i < VALUES; i++){
            if (value[i] != cell.value[i]){
                return false;
            }
        }
        return true;
    }

};

