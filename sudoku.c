/**
 * \brief     函数定义
 * \external  display, solveSudoku, initSudoku
 * \authors   Group 23
 * \file      sudoku.c
 *
 * 数独生成与求解的相关函数具体定义
 *
 * \date 2019/03/09
 *
 */


/*------------------------------------------------------
 *  \brief  返回一个随机索引值
 *  \retval int (0~9)
 */
int getRand(void)
{
    return rand() % ROW_MAX;
}

/*------------------------------------------------------
 *  \brief  从已完成的数独中随机取走至多 MAX_REMOVE 个数字
 *
 *  \param[in]  puzzle   数独数组
 */
#if PLAN_B
void removeNum(int puzzle[ROW_MAX][COL_MAX])
{
    int i;

    for (i = 0; i < MAX_REMOVE; ++i)
    {
        puzzle[getRand()][getRand()] = 0;
    }
}
#endif

/*------------------------------------------------------
 *  \brief  将数独所有数字置为空值
 *
 *  \param[in]  puzzle   数独数组
 */
void setToZero(int puzzle[ROW_MAX][COL_MAX])
{
    int i, j;
    for (i = ROW_START; i < ROW_MAX; ++i)
    {
        for (j = COL_START; j < COL_MAX; ++j)
        {
            puzzle[i][j] = BLANK;
        }
    }
}


/*------------------------------------------------------
 *  \brief  在控制台打印出数独
 *
 *  \param[in]  puzzle   数独数组
 */
void display(int puzzle[ROW_MAX][COL_MAX])
{
    int i, j;
    printf("+---------------+---------------+---------------+\n");
    for (i = ROW_START; i < ROW_MAX; ++i)
    {
        printf("|   ");
        for (j = COL_START; j < COL_MAX; ++j)
        {
            printf("%-4d", puzzle[i][j]);
            if ((j + 1) % 3 == 0)
            {
                printf("|   ");
            }
        }
        printf("\n|               |               |               |\n");
        if ((i + 1) % 3 == 0)
        {
            printf("+---------------+---------------+---------------+\n");
            if (i < 8)
            {
                printf("|               |               |               |\n");
            }
        }
    }
}


/*------------------------------------------------------
 *  \brief  检测某个数字能否填入数独的某个特定位置
 *
 *  \param[in]  puzzle      数独数组
 *  \param[in]  row         目标位置的行坐标
 *  \param[in]  col         目标位置的列坐标
 *  \param[in]  num         待检测数字
 *  \retval     ResultType  成功返回SUCCEED，否则返回FAILED
 */
ResultType tryNumber(int puzzle[ROW_MAX][COL_MAX], int row, int col, int num)
{
    int i;
    for (i = ROW_START; i < ROW_MAX; ++i)
    {
        int rowStart = (row/3) * 3;         /*九宫格起始位置*/
        int colStart = (col/3) * 3;
        if ((puzzle[row][i] == num) ||      /*检查行*/
            (puzzle[i][col] == num) ||      /*检查列*/
            (puzzle[rowStart + (i%3)]       /*检查九宫格*/
                [colStart + (i/3)] == num))
            return FAILED;
    }
    return SUCCEED;
}


/*------------------------------------------------------
 *  \brief  从指定位置开始填写数独，直到完成
 *
 *  \param[in]  puzzle          数独数组
 *  \param[in]  row             开始位置行坐标
 *  \param[in]  col             开始位置列坐标
 *  \retval     ResultType      成功返回SOLVED，否则返回NO_SOLUTION
 */
ResultType fillSudoku(int puzzle[ROW_MAX][COL_MAX], int row, int col)
{
    int num;
    if (row < ROW_MAX && col < COL_MAX)
    {
        if (BLANK != puzzle[row][col])     /*当前格不为空，则递归填写下一格*/
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
        else   /*尝试填入，根据能否有解来决定是否回溯*/
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


/*------------------------------------------------------
 *  \brief  从第一个数开始填写整个数独
 *
 *  \param[in]  puzzle      数独数组
 *  \retval     ResultType  成功返回SOLVED，否则返回NO_SOLUTION
 */
ResultType solveSudoku(int puzzle[ROW_MAX][COL_MAX])
{
    return fillSudoku(puzzle, ROW_START, COL_START);
}


/*------------------------------------------------------
 *  \brief  初始化数独
 *
 *  \param[in]  puzzle   数独数组
 */
void initSudoku(int puzzle[ROW_MAX][COL_MAX])
{
    int i;
    int randRow, randCol;
    int randNum;

    setToZero(puzzle);
    srand((unsigned) time(NULL));

    for (i = 0; i < MAX_GENERATE; ++i)
    {
        randRow = getRand();
        randCol = getRand();
        randNum = getRand() + 1;
        if (BLANK == puzzle[randRow][randCol])
        {
            if (tryNumber(puzzle, randRow, randCol, randNum))
            {
                puzzle[randRow][randCol] = randNum;
            }

        }
    }
#if PLAN_B
    solveSudoku(puzzle);
    removeNum(puzzle);
#endif
}
