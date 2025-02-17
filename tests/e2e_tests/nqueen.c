#include "print.h"
#define N 16

void printSolution(int board[N][N])
{
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            char cell[3] = ". ";
            if (board[i][j] == 1) {
                cell[0] = 'Q';
            }
            printString(cell, 3);
        }
        printString("\n", sizeof("\n"));
    }
}

int isSafe(int board[N][N], int row, int col)
{
    int i, j;

    for (i = 0; i < col; i++)
        if (board[row][i])
            return 0;

    for (i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j])
            return 0;

    for (i = row, j = col; j >= 0 && i < N; i++, j--)
        if (board[i][j])
            return 0;

    return 1;
}

int solveNQUtil(int board[N][N], int col)
{
    if (col >= N)
        return 1;

    for (int i = 0; i < N; i++) {
        if (isSafe(board, i, col)) {
            board[i][col] = 1;

            if (solveNQUtil(board, col + 1))
                return 1;
            board[i][col] = 0;
        }
    }

    return 0;
}

int main()
{
    int board[N][N];

    if (solveNQUtil(board, 0) == 1) {
        printSolution(board);
    }
    return 0;
}
