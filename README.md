# Variant Sudoku Solver

Trying to solve Sudoku variants by means of regular deduction.

## Current Implementations

Simple Sudoku solver.

## Future Plans

This program should have the ability to solve many variations of Sudoku
The Variants I plan to implement include

- X-Cross - Diagonals of the Square board cannot have the same number
- Chess Moves - A piece's movement represents where the numbers cannot be the same
  - King - 3x3 space
  - Knight - end of **L**
  - Bishop - Diagonal from the cell
- Consecutive Numbers - Numbers must have chronological numbers next to them in the orthogonal directions
- Non-consecutive Numbers - Numbers cannot have chronological numbers next to them in the orthogonal directions
- Palindrome - Within a line the numbers have to be in a palindrome such that the last two number are the same, and the next two numbers inwards are the same, and so on.
- Thermostat - Bulb has the smallest digit while the rest are in ascending order, not necessarily in chronological order
- Hyper Sudoku - Sudoku that has 3x3s inside
- Varying Size of board - both in terms of square and rectangle boards as well as irregular boards

---

## Changelog

1.0 - Finished the basic version of Sudoku (Feb 6, 2023)
1.1 - Started Implementation of Diagonals (Feb 6, 2023)  
1.2 - Updated the version numbers (1.1 used to be 2.0)
    - started implementation of a strategy for sudoku such that the solver can solve much harder sudoku puzzles. Implementation of X-cross to be delayed for this reason. (Feb 10, 2023)
1.3 - The Sudoku currently is close to finishing a full sudoku only needing bug fixes of making sure the cell has only one possible number that it can be  
2.0 - Due to the sudoku used for testing purposes a chance at making the code more readable was seized. Also with this restructure a finding of a website that explains the different strategies that can be used and will be using that as the core of the upcoming sudoku solver. The code will be transferred to the NewBoard.cpp with some of the basic functionality going towards the separate CellManip and Array2DCells  
2.1 - Current Array2DCells, Cell, and CellManip files are all functional. Cell and Array2DCells work by making Array2DCells a class that holds a 2D array of cell objects. CellManip is just a functionality layer that allows both Array2DCells and Cell to work in modification of arrays.  
2.2 - Added the Hidden singles functionality, in which the square, quadrant, or column has only one place to put the number, it puts it there. While it may not intefere with the current Sudoku functionality it is still untested since the wiki does not provide an example problem, but in the future this functionality will be a core part of the solver. Also added version numbers to the files themselves to represent the progress they have achieved.[^1]

## Sources

[ Sudoku Wiki ] (<https://www.sudokuwiki.org/Sudoku_Solver_for_Android>)  
This is the sudoku solver that gives me the strategies in written form  

---
> [^1]Versions will go as follows:
>
> - The first number is a major release meaning it will change once it can start solving different types of sudoku
> - The second number is how many functions the file has
> - The last number is 1 if there were minor changes like changing a variable or adding a description
