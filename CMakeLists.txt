cmake_minimum_required(VERSION 3.6)
project(sudoku_solver)

set(CMAKE_CXX_STANDARD 14)

find_library(getopt REQUIRED)

set(SOURCE_FILES src/main.cpp src/SudokuGrid.cpp src/SudokuGrid.h src/BacktrackingSolver.cpp src/BacktrackingSolver.h)
add_executable(sudoku_solver ${SOURCE_FILES})