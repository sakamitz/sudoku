#define SUCCEED      1
#define FAILED       0

#define SOLVED       1
#define NO_SOLUTION  0

#define ROW_START    0
#define ROW_MAX      9

#define COL_START    0
#define COL_MAX      9

#define MAX_INDEX    8
#define BLANK        0

#define FIRST        1
#define LAST         9

#define MAX_REMOVE   70
#define MAX_GENERATE 40

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sudoku.c"

int genRand(void);

void removeNum(int puzzle[ROW_MAX][COL_MAX]);

void setToZero(int puzzle[ROW_MAX][COL_MAX]);

void display(int puzzle[ROW_MAX][COL_MAX]);

int tryNumber(int puzzle[ROW_MAX][COL_MAX], int row, int col, int num);

int fillSudoku(int puzzle[ROW_MAX][COL_MAX], int row, int col);

int solveSudoku(int puzzle[ROW_MAX][COL_MAX]);

void initSudoku(int puzzle[ROW_MAX][COL_MAX]);