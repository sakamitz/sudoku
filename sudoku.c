inline int genRand(void)
{
    return rand() % ROW_MAX;
}

void removeNum(int puzzle[ROW_MAX][COL_MAX])
{
    int i;
    srand((unsigned) time(NULL));

    for (i = 0; i < MAX_REMOVE; ++i)
    {
        puzzle[genRand()][genRand()] = 0;
    }
}

void setToZero(int puzzle[ROW_MAX][COL_MAX])
{
    int i, j;
    for (i = ROW_START; i < ROW_MAX; ++i)
    {
        for (j = COL_START; j < COL_MAX; ++j)
        {
            puzzle[i][j] = 0;
        }
    }
}

void display(int puzzle[ROW_MAX][COL_MAX])
{
    int i, j;
    printf("\n+-----+-----+-----+\n");
    for (i = ROW_START; i < ROW_MAX; ++i)
    {
        for (j = COL_START; j < COL_MAX; ++j)
        {
            printf("|%d", puzzle[i][j]);
        }

        printf("|\n");
        if ((i+1) % 3 == 0)
        {
            printf("+-----+-----+-----+\n");
        }
    }
}

int tryNumber(int puzzle[ROW_MAX][COL_MAX], int row, int col, int num)
{
    int i;
    for (i = ROW_START; i < ROW_MAX; ++i)
    {
        int rowStart = (row/3) * 3;
        int colStart = (col/3) * 3;
        if ((puzzle[row][i] == num) ||
            (puzzle[i][col] == num) ||
            (puzzle[rowStart + (i%3)]
                [colStart + (i/3)] == num))
            return FAILED;
    }
    return SUCCEED;
}

int fillSudoku(int puzzle[ROW_MAX][COL_MAX], int row, int col)
{
    int num;
    if (row < ROW_MAX && col < COL_MAX)
    {
        if (BLANK != puzzle[row][col])
        {
            if (col < MAX_INDEX)
            {
                return fillSudoku(puzzle, row, col+1);
            }
            else if (row < MAX_INDEX)
            {
                return fillSudoku(puzzle, row+1, COL_START);
            }
            else return SOLVED;
        }
        else
        {
            for (num = FIRST; num <= LAST; ++num)
            {
                if (SUCCEED == tryNumber(puzzle, row, col, num))
                {
                    puzzle[row][col] = num;
                    if (col < MAX_INDEX)
                    {
                        if (SOLVED == fillSudoku(puzzle, row, col+1))
                        {
                            return SOLVED;
                        }
                        else
                        {
                            puzzle[row][col] = BLANK;
                        }
                    }
                    else if (row < MAX_INDEX)
                    {
                        if (SOLVED == fillSudoku(puzzle, row+1, COL_START))
                        {
                            return SOLVED;
                        }
                        else
                        {
                            puzzle[row][col] = BLANK;
                        }
                    }
                    else return SOLVED;
                }
            }
        }
        return NO_SOLUTION;
    }
    else return SOLVED;
}

int solveSudoku(int puzzle[ROW_MAX][COL_MAX])
{
    return fillSudoku(puzzle, ROW_START, COL_START);
}

void initSudoku(int puzzle[ROW_MAX][COL_MAX])
{
    int i;
    int randRow, randCol;
    int randNum;
    setToZero(puzzle);
    srand((unsigned) time(NULL));

    for (i = 0; i < MAX_GENERATE; ++i)
    {
        randRow = genRand();
        randCol = genRand();
        randNum = genRand() + 1;
        if (BLANK == puzzle[randRow][randCol])
        {
            if (tryNumber(puzzle, randRow, randCol, randNum))
            {
                puzzle[randRow][randCol] = randNum;
            }

        }
    }
    display(puzzle);
    solveSudoku(puzzle);
    removeNum(puzzle);
}