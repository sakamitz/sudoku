/**
 * \brief     数独生成与求解的相关常量与函数声明
 * \authors   Group 23
 * \file      sudoku.h
 *
 * \date 2019/03/09
 */
#ifndef SUDOKU_H_
#define SUDOKU_H_

#define PLAN_B       0          /*编译选项：切换数独生成方式*/

#define SUCCEED      1          /*数字能否填入数独*/
#define FAILED       0

#define SOLVED       1          /*数独是否可解*/
#define NO_SOLUTION  0

#define ROW_START    0          /*行索引范围*/
#define ROW_MAX      9

#define COL_START    0          /*列索引范围*/
#define COL_MAX      9

#define MAX_INDEX    8          /*行列最大下标*/
#define BLANK        0          /*未填的格子中的值*/

#define FIRST        1          /*数独元素范围*/
#define LAST         9

#define MAX_REMOVE   70         /*控制生成数独的规模*/
#define MAX_GENERATE 35

typedef int ResultType

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sudoku.c"

/*------------------------------------------------------
 *  \brief  返回一个随机索引值
 *
 */
int getRand(void);


#if PLAN_B
/*------------------------------------------------------
 *  \brief  从已完成的数独中随机取走至多 MAX_REMOVE 个数字
 *
 *  \param[in]  puzzle   数独数组
 */
void removeNum(int puzzle[ROW_MAX][COL_MAX]);

#endif

/*------------------------------------------------------
 *  \brief  将数独所有数字置为空值
 *
 *  \param[in]  puzzle   数独数组
 */
void setToZero(int puzzle[ROW_MAX][COL_MAX]);


/*------------------------------------------------------
 *  \brief  在控制台打印出数独
 *
 *  \param[in]  puzzle   数独数组
 */
void display(int puzzle[ROW_MAX][COL_MAX]);


/*------------------------------------------------------
 *  \brief  检测某个数字能否填入数独的某个特定位置
 *
 *  \param[in]  puzzle      数独数组
 *  \param[in]  row         行坐标
 *  \param[in]  col         列坐标
 *  \param[in]  num         待检测数字
 *  \retval     ResultType  成功返回SUCCEED，否则返回FAILED
 */
ResultType tryNumber(int puzzle[ROW_MAX][COL_MAX], int row, int col, int num);


/*------------------------------------------------------
 *  \brief  从指定位置开始填写数独，直到完成
 *
 *  \param[in]  puzzle      数独数组
 *  \param[in]  row         开始位置行坐标
 *  \param[in]  col         开始位置列坐标
 *  \retval     ResultType  成功返回SOLVED，否则返回NO_SOLUTION
 */
ResultType fillSudoku(int puzzle[ROW_MAX][COL_MAX], int row, int col);


/*------------------------------------------------------
 *  \brief  从第一个数开始填写整个数独
 *
 *  \param[in]  puzzle      数独数组
 *  \retval     ResultType  成功返回SOLVED，否则返回NO_SOLUTION
 */
ResultType solveSudoku(int puzzle[ROW_MAX][COL_MAX]);


/*------------------------------------------------------
 *  \brief  初始化数独
 *
 *  \param[in]  puzzle   数独数组
 */
void initSudoku(int puzzle[ROW_MAX][COL_MAX]);

#endif
