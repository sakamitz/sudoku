#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sudoku.h"

int main()
{
    int puzzle[ROW_MAX][COL_MAX];
    initSudoku(puzzle);

    printf("Generated sudoku:\n");
    display(puzzle);
    printf("\nPress Enter to solve.\n");
    getchar();

    if (SOLVED == solveSudoku(puzzle))
    {
    	printf("Solution:\n");
        display(puzzle);
    }
    else
    {
        printf("NO SOLUTION\n");
    }

    return 0;
}
