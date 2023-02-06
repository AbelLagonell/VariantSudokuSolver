/**
 * @brief A cell that contains a value from 0 to 9, with 0 being more than one true value in the array and 1-9 being the position index +1. 
*/

#include <iostream>

class Cell{
private:
    bool value[9]; //*Holding the cell value from 0-9 
    bool solved = false; //*Is the cell solved or not 

public:

    //*Constructor
    Cell(){
        for(int i = 0; i < 9; i++){
            value[i] = true;
        }
    }

    //*Prints outs possible numbers
    void printArray(){
        for (int i = 0; i<9; i++){
            std::cout << ((value[i])? i+1:0) << ", ";
        }
        std::cout << std::endl;
    }

    //*Checks if there is a single possibility
    void checkSolved(){
        if (checkSingularity())
            solved = true;
    }

    //*Gets the solved var
    bool getSolved(){
        return solved;
    }

    //*Setting the value of the cell making everything but the index position 
    void setValue(int index){
        if ( index < 0 || index > 8){
            return;
        }
        for(int j = 0; j < 9; j++){
            if(j != index){
                value[j] = false;
            }
        }
        solved = true;
    }

    //*Setting the index of the cell to false 
    void setSingularValue(int index){
        if ( index < 0 || index > 8){
            return;
        }
        for(int j = 0; j < 9; j++){
            if(j == index){
                value[j] = false;
            }
        }
        checkSolved();
    }

    //*Printing the value of the cell if it only has one true value
    void printValue(){
        if (!(checkSingularity())){
            std::cout << "0 ";
            return;
        }
        for(int i = 0; i < 9; i++){
            if(value[i]){
                std::cout << i+1 << " ";
            }
        }
    }

    //*Checks if the cell has one true value
    bool checkSingularity(){
        int count = 0;
        for(int i = 0; i < 9; i++){
            if(value[i]){
                count++;
            }
        }
        if(count == 1){
            solved=true;
            return true;
        }
        return false;
    }

    //*returns the index of the number
    int giveSingularity(){
        if (!checkSingularity())
            return -1;
        for(int i = 0; i < 9; i++){
            if(value[i]){
                return i;
            }
        }
        return -2;
    }
};