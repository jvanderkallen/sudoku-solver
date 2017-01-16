# Sudoku Solver
This is a command line application that solves Sudoku puzzles. It uses recursive backtracking to find a solution.

## Build
In order to build the project run the following commands:
```bash
$ mkdir build
$ cd build
$ cmake ..
$ make
```

## Usage
```
Usage: sudoku_solver [OPTION]
Solve a Sudoku.

Options:
-h				show this help information
-s sudoku		solve the provided Sudoku
-f filepath		solve the Sudokus in the provided file (file must contain one Sudoku per line)
```