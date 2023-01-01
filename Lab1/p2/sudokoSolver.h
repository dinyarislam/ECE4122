/*
Author: Dinyar Islam
Class: ECE4122
Last Date Modified: 26 September 2022

Description: Lab 1 Problem 2

What is the purpose of this file?
Header file for sudokoSolver.cpp file
*/

#pragma once
#define N 9

bool isSafe(int grid[N][N], int row, int col, int num);

bool solveSudoku(int grid[N][N], int row, int col);

int sudokuSolverDriver(int grid[9][9], int row, int col);
