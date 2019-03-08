#include <stdio.h>
#include "sudoku.h"

int main()
{
    int puzzle[ROW_MAX][COL_MAX];
    initSudoku(puzzle);

    int statu = solveSudoku(puzzle);
    if (statu == SOLVED)
    {
        display(puzzle);
    }
    else
    {
        printf("\n\nNO SOLUTION\n");
    }
    return 0;
}
