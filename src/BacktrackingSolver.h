#ifndef SUDOKU_SOLVER_BACKTRACKINGSOLVER_H
#define SUDOKU_SOLVER_BACKTRACKINGSOLVER_H


#include "SudokuGrid.h"

class BacktrackingSolver {

public:

    void solve(SudokuGrid &puzzle);

private:

    SudokuGrid *puzzle;

    bool isCandidate(int row, int column, int value);

    bool columnContains(int columnIndex, int value);
    bool rowContains(int column, int value);
    bool blockContains(int block, int value);

    bool solve(int row, int column);
};


#endif //SUDOKU_SOLVER_BACKTRACKINGSOLVER_H
