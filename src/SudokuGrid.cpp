#include <cstdlib>
#include <stdexcept>
#include <cstring>
#include "SudokuGrid.h"

SudokuGrid::SudokuGrid(const char *puzzle) {
    size_t length = strlen(puzzle);

    if (length != SIZE * SIZE) {
        throw std::invalid_argument("Sudoku puzzle must consist of 81 values");
    }

    for (int i = 0; i < SIZE * SIZE; i++) {
        int value = puzzle[i] - '0';
        this->setCell(i / SIZE, i % SIZE, value);
    }

    if (!isValid()) {
        throw std::invalid_argument("The provided puzzle is invalid");
    }
}

void SudokuGrid::setCell(int row, int column, int value) {
    validateRowIndex(row);
    validateColumnIndex(column);

    if (value < 0 || value > SIZE) {
        throw std::invalid_argument("The provided value is invalid");
    }

    this->puzzle[row][column] = value;
}

void SudokuGrid::clearCell(int row, int column) {
    setCell(row, column, EMPTY_CELL);
}

int SudokuGrid::getCell(int row, int column) const {
    validateRowIndex(row);
    validateColumnIndex(column);

    return this->puzzle[row][column];
}

std::ostream &operator<<(std::ostream &os, const SudokuGrid &grid) {
    for (int row = 0; row < grid.SIZE; row++) {
        for (int column = 0; column < grid.SIZE; column++) {
            int value = grid.getCell(row, column);
            if (value != grid.EMPTY_CELL) {
                os << value;
            } else {
                os << ".";
            }

            if (column < grid.SIZE - 1) {
                os << " ";
            }
        }
        os << std::endl;
    }
    return os;
}

void SudokuGrid::validateRowIndex(int row) const {
    if (row < 0 || row >= SIZE) {
        throw std::invalid_argument("The provided row index is out of bounds");
    }
}

void SudokuGrid::validateColumnIndex(int column) const {
    if (column < 0 || column >= SIZE) {
        throw std::invalid_argument("The provided column index is out of bounds");
    }
}

std::vector<int> SudokuGrid::getRow(int row) {
    validateRowIndex(row);

    std::vector<int> result;
    for (int column = 0; column < SIZE; column++) {
        int value = getCell(row, column);
        if (value != EMPTY_CELL) {
            result.push_back(value);
        }
    }
    return result;
}

std::vector<int> SudokuGrid::getColumn(int column) {
    validateColumnIndex(column);

    std::vector<int> result;
    for (int row = 0; row < SIZE; row++) {
        int value = getCell(row, column);

        if (value != EMPTY_CELL) {
            result.push_back(value);
        }
    }
    return result;
}

std::vector<int> SudokuGrid::getBlock(int block) {
    if (block < 0 || block >= SIZE) {
        throw std::invalid_argument("The provided block index is out of bounds");
    }

    std::vector<int> result;
    int rowStartIndex = (block / 3) * 3;
    int columnStartIndex = (block * 3) % SIZE;
    for (int row = rowStartIndex; row < rowStartIndex + 3; row++) {
        for (int column = columnStartIndex; column < columnStartIndex + 3; column++) {
            int value = getCell(row, column);
            if (value != EMPTY_CELL) {
                result.push_back(value);
            }
        }
    }
    return result;
}

std::vector<int> SudokuGrid::getBlock(int row, int column) {
    return getBlock(blockIndex(row, column));
}

bool SudokuGrid::cellIsEmpty(int row, int column) {
    return getCell(row, column) == EMPTY_CELL;
}

bool SudokuGrid::cellIsFilledIn(int row, int column) {
    return getCell(row, column) != EMPTY_CELL;
}

int SudokuGrid::blockIndex(int row, int column) {
    int index = ((row / 3) * 3) + (column / 3);
    return index;
}

bool SudokuGrid::isValid() {
    bool rowValueUsed[SIZE][SIZE];
    bool columnValueUsed[SIZE][SIZE];
    bool blockValueUsed[SIZE][SIZE];

    memset(rowValueUsed, false, sizeof(rowValueUsed));
    memset(columnValueUsed, false, sizeof(columnValueUsed));
    memset(blockValueUsed, false, sizeof(blockValueUsed));

    for (int row = 0; row < SIZE; row++) {
        for (int column = 0; column < SIZE; column++) {
            if (cellIsFilledIn(row, column)) {
                int value = getCell(row, column) - 1;
                int block = blockIndex(row, column);

                if (rowValueUsed[row][value] || columnValueUsed[column][value] || blockValueUsed[block][value]) {
                    return false;
                }

                rowValueUsed[row][value] = columnValueUsed[column][value] = blockValueUsed[block][value] = true;
            }
        }
    }

    return true;
}

