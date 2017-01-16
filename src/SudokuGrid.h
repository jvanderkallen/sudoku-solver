#ifndef SUDOKU_SOLVER_SUDOKUGRID_H
#define SUDOKU_SOLVER_SUDOKUGRID_H


#include <ostream>
#include <vector>

class SudokuGrid {

public:
    SudokuGrid(const char *puzzle);

    void setCell(int row, int column, int value);
    void clearCell(int row, int column);

    int getCell(int row, int column) const;
    std::vector<int> getRow(int row);
    std::vector<int> getColumn(int column);
    std::vector<int> getBlock(int block);

    bool cellIsEmpty(int row, int column);
    bool cellIsFilledIn(int row, int column);

    friend std::ostream &operator<<(std::ostream &os, const SudokuGrid &grid);

    const int EMPTY_CELL = 0;
    const size_t SIZE = 9;
private:
    int puzzle[9][9];

    void validateRowIndex(int row) const;
    void validateColumnIndex(int column) const;
};


#endif //SUDOKU_SOLVER_SUDOKUGRID_H
