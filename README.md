# Sudoku Solver with Constraint Propagation
### Second year, winter semester 2021/2022, Programming in C++

**Goal**: Create a sudoku solver with the constraint propagatin, the ability to find out the next right step and highlighting the wrong choice.

# Documentation

## Launching 

The solver is launched via Qt Creator.

## Program structure

The program contains three classes. Sudoku, Window and Cell.

#### `class Sudoku` 
Implements methods for working with the board that is represented by two dimentional array of Cells.

#### `class Window`
Responsible for receiving data from the user and displaying data.

#### `class Cell`
Keeps the field of possibilities and the current state of the cell.

## Solving Process

Alternately apply Elimination and OnlyChoice until they stop changing the state of the cells. On the processed board, we call backtracking and solve.

#### `Elimination`

If a cell has a value, remove from all possible values of cells by row, column and square this value.

#### `OnlyChoice`

If the cell has the only possible value for a row, column or square, set this value to the cell.

#### `Backtrack`

Gradually choose the value from the possible ones and if there is no conflict, move on to the next cell.

## Course of work

The work was carried out as usual. The biggest difficulty was choosing the right framework, finding guides and creating a GUI and saving user input, in case it is correct.
