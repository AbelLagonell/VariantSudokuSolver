/**
 * @brief A cell that contains a value from 0 to VALUES, with 0 being more than one true value in the array and 1-VALUES being the position index +1. 
*/

#include <iostream>
#include "CellManip.cpp"

#define VALUES 9

class Cell{
private:
    bool value[VALUES]; //*Holding the cell value from 0-VALUES 
    bool solved = false; //*Is the cell solved or not 

public:

    //*Returns the bool array
    bool* getArray(){
        bool* array = new bool[VALUES];
        for(int i = 0; i < VALUES; i++){
            array[i] = value[i];
        }
        return array;
    }

    //*Constructor
    Cell(){
        Initialize(value, VALUES, true);
    }

    //*Checks if there is a single possibility
    void checkSolved(){
        if (CheckSingle(value, VALUES) != -1)
            solved = true;
    }

    //*Gets the solved var
    bool getSolved(){
        return solved;
    }

    //*Setting the value of the cell making everything but the index position 
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

    void printArray(){
        for (int i =0; i < VALUES; i++){
            std::cout << ((value[i]!=false)? i+1:0) << " ";
        }
        
    }

};