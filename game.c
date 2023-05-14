#include "Nokia5110.h"
#include "common.h"
#include <string.h>

extern unsigned char SCORE[2];
extern unsigned char GAME_GRID[3][3];
extern const unsigned char OShape[];
extern const unsigned char XShape[];
extern unsigned int current_player;
void update_score(unsigned char board[3][3], unsigned char *score);
void has_winner(void);

void DrawScore(void)
{
    char player[5] = "-P*-";
    update_score(GAME_GRID, SCORE);

    player[2] = current_player == 0 ? '1' : '2';

    Nokia5110_SetCursor(8, 1);
    Nokia5110_OutString(player);
    Nokia5110_SetCursor(8, 3);

    strcpy(player, "P1:0");
    player[3] = (int)SCORE[0] == 0 ? '0' : (int)SCORE[0];
    Nokia5110_OutString(player);

    Nokia5110_SetCursor(8, 5);

    strcpy(player, "P2:0");
    player[3] = (int)SCORE[1] == 0 ? '0' : (int)SCORE[1];
    Nokia5110_OutString(player);
}

void DrawGrid(void)
{
    int rows = 0, cols = 0;
    for (rows = 1; rows < 6; rows++)
    {
        for (cols = 2; cols < 6; cols += 3)
        {
            Nokia5110_SetCursor(cols, rows);
            Nokia5110_OutChar('|');
        }
    }

    for (rows = 2; rows < 6; rows += 2)
    {
        for (cols = 0; cols <= 7; cols++)
        {
            Nokia5110_SetCursor(cols, rows);
            Nokia5110_OutChar('-');
        }
    }
    DrawScore();
}

void DrawPlayedGrid(void)
{
    int i = 0, j = 0;

    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            if (GAME_GRID[j][i] == 1)
            {
                Nokia5110_PrintBMP(5 + 20 * i, 13 + 17 * j, XShape, 0);
            }
            else if (GAME_GRID[j][i] == 2)
            {
                Nokia5110_PrintBMP(5 + 20 * i, 13 + 17 * j, OShape, 0);
            }
        }
    }
}
void has_winner(void)
{
    int i = 0, j = 0;

    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            GAME_GRID[j][i] = 0;
        }
    }
    current_player = 0;
}

void update_score(unsigned char board[3][3], unsigned char *score)
{
    int row, col, winner;
    // Check rows
    for (row = 0; row < 3; row++)
    {
        if (board[row][0] != 0 && board[row][0] == board[row][1] && board[row][1] == board[row][2])
        {
            winner = board[row][0];
            if (winner == 1)
            {
                (*score)++;
                has_winner();
            }
            else if (winner == 2)
            {
                (*(score + 1))++;
                has_winner();
            }
        }
    }

    // Check columns
    for (col = 0; col < 3; col++)
    {
        if (board[0][col] != 0 && board[0][col] == board[1][col] && board[1][col] == board[2][col])
        {
            winner = board[0][col];
            if (winner == 1)
            {
                (*score)++;
                has_winner();
            }
            else if (winner == 2)
            {
                (*(score + 1))++;
                has_winner();
            }
        }
    }

    // Check diagonals
    if (board[0][0] != 0 && board[0][0] == board[1][1] && board[1][1] == board[2][2])
    {
        winner = board[0][0];
        if (winner == 1)
        {
            (*score)++;
            has_winner();
        }
        else if (winner == 2)
        {
            (*(score + 1))++;
            has_winner();
        }
    }

    if (board[0][2] != 0 && board[0][2] == board[1][1] && board[1][1] == board[2][0])
    {
        winner = board[0][2];
        if (winner == 1)
        {
            (*score)++;
            has_winner();
        }
        else if (winner == 2)
        {
            (*(score + 1))++;
            has_winner();
        }
    }

    // No winner found
    return;
}
