#include <iostream>
#include <fstream>

#include <getopt.h>

#include "SudokuGrid.h"
#include "BacktrackingSolver.h"

#define PROGRAM_NAME "sudoku_solver"

static char *puzzle;
static std::string filePath;

static bool gotPuzzle = false;
static bool gotFilePath = false;

void usage(int status) {
    std::cout << "Usage: " << PROGRAM_NAME << " [OPTION]" << std::endl
              << "Solve a Sudoku." << std::endl
              << std::endl
              << "Options:" << std::endl
              << "-h" << "\t\t\tshow this help information" << std::endl
              << "-s sudoku" << "\t\tsolve the provided Sudoku" << std::endl
              << "-f filepath" << "\t\tsolve the Sudokus in the provided file (file must contain one Sudoku per line)"
              << std::endl
              << std::endl
              << "Examples:" << std::endl
              << PROGRAM_NAME << " -s 003020600900305001001806400008102900700000008006708200002609500800203009005010300"
              << std::endl
              << PROGRAM_NAME << " -f ./sudokus.txt" << std::endl;
    exit(status);
}

void parseArgs(int argc, char **argv) {
    int opt;
    while ((opt = getopt(argc, argv, "s:f:h")) != -1) {
        switch (opt) {
            case 's': {
                puzzle = optarg;
                gotPuzzle = true;

                break;
            }
            case 'f': {
                filePath = optarg;
                gotFilePath = true;

                break;
            }
            case '?':
                usage(1);
            case 'h': {
                usage(0);
            }
        }
    }
}

int main(int argc, char *argv[]) {
    parseArgs(argc, argv);

    if (gotPuzzle) {
        SudokuGrid grid(puzzle);

        BacktrackingSolver solver;
        solver.solve(grid);

        std::cout << grid;
    } else if (gotFilePath) {
        std::ifstream ifs(filePath);
        std::string puzzle;

        while (std::getline(ifs, puzzle)) {
            SudokuGrid grid(puzzle.c_str());

            BacktrackingSolver solver;
            solver.solve(grid);

            std::cout << grid << std::endl;
        }
    }

    return 0;
}