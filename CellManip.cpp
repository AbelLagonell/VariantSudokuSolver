/**
 * @file CellManip.cpp
 * @author Abel Lagonell (alagonell1730@floridapoly.edu)
 * @brief A background file that contains functions to manipulate the Cell class.
 * @version 1.1
 * @date 2023-02-19
 * 
 * @copyright Copyright (c) 2023
 * 
*/

#pragma once
#include <iostream>

//* Initializes bool array to be all value
void Initialize(bool *arr, int size, bool value){
    for (int i=0; i<size; i++){
        arr[i] = value;
    }
}

//* Prints the array
void PrintArray(bool *arr, int size){
    for (int i=0; i<size; i++){
        std::cout << ((arr[i])? i+1:0) << ", ";
    }
    std::cout << std::endl;
}

//* Sets the index to the value
void SetIndex(bool *arr, int size, int index, bool value){
    if ( index < 0 || index > size){
        return;
    }
    arr[index] = value;
}

//* Sets all indexes BUT the one given to value
void SetIndexBUT(bool *arr, int size, int index, bool value){
    if ( index < 0 || index > size){
        return;
    }
    for (int i=0; i<size; i++){
        if (i != index) arr[i] = value;
    }
}

//* Returns the index if there is a single True Value
int CheckSingle(const bool arr[], int size){
    int truths = 0,
        index = 0;
    for (int i=0; i<size; i++){
        if(arr[i]){
            truths++;
            index =i;
        }
    }
    if(truths>1)
        return -1;
    else
        return index;
}

//* Prints the index number plus one if there is a singular value
void PrintIndex(const bool arr[], int size){
    int index = CheckSingle(arr, size);
    if (index != -1) std::cout << index+1 << " ";
}

//*Adds 1 to the index of an array if the value is true
void addToArray(int arr[], bool value[], int size){
    for (int i =0; i<size; i++){
        if(value[i]){
            arr[i]++;
        }
    }
}