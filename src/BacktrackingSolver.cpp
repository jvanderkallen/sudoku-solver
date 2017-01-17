#include <algorithm>
#include <iostream>
#include "BacktrackingSolver.h"

bool BacktrackingSolver::isCandidate(int row, int column, int value) {
    return !rowContains(row, value) && !columnContains(column, value) && !blockContains(row, column, value);
}

bool BacktrackingSolver::rowContains(int rowIndex, int value) {
    std::vector<int> row = puzzle->getRow(rowIndex);
    return std::find(row.begin(), row.end(), value) != row.end();
}

bool BacktrackingSolver::columnContains(int columnIndex, int value) {
    std::vector<int> column = puzzle->getColumn(columnIndex);
    return std::find(column.begin(), column.end(), value) != column.end();
}

bool BacktrackingSolver::blockContains(int rowIndex, int columnIndex, int value) {
    std::vector<int> block = puzzle->getBlock(rowIndex, columnIndex);
    return std::find(block.begin(), block.end(), value) != block.end();
}

void BacktrackingSolver::solve(SudokuGrid &puzzle) {
    this->puzzle = &puzzle;
    solve(0, 0);
}

bool BacktrackingSolver::solve(int row, int column) {
    if (row >= puzzle->SIZE || column >= puzzle->SIZE) {
        return true;
    }

    int nextColumn = (column + 1) % puzzle->SIZE;
    int nextRow = nextColumn != 0 ? row : row + 1;

    if (puzzle->cellIsFilledIn(row, column)) {
        return solve(nextRow, nextColumn);
    }

    for (int value = 1; value <= puzzle->SIZE; value++) {
        if (isCandidate(row, column, value)) {
            puzzle->setCell(row, column, value);

            if (solve(nextRow, nextColumn)) {
                return true;
            }
        }
    }

    puzzle->clearCell(row, column);
    return false;
}


