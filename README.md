# Variant Sudoku Solver

Trying to solve Sudokus variants by means of regular deduction.

## Current Implementations

Simple Sudoku solver.

## Furture Plans

This program should have the ability to solve many variations of Sudoku
The Variants I plan to implement include

- X-Cross - Diagonals of the Sqaure board cannot have the same number
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
