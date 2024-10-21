#include <stdio.h>
#include <stdlib.h>
#include "triangle_routines.h"

#define NMOVES 36
#define BOARD_SIZE 15 /* board consists of 15 integers */

int moves[NMOVES][3] = /* all legal moves */
{
    {0, 1, 3},
    {3, 1, 0},
    {1, 3, 6},
    {6, 3, 1},
    {0, 2, 5},
    {5, 2, 0},
    {3, 4, 5},
    {5, 4, 3},
    {6, 7, 8},
    {8, 7, 6},
    {7, 8, 9},
    {9, 8, 7},
    {2, 5, 9},
    {9, 5, 2},
    {2, 4, 7},
    {7, 4, 2},
    {1, 4, 8},
    {8, 4, 1},
    {3, 6, 10},
    {10, 6, 3},
    {4, 7, 11},
    {11, 7, 4},
    {3, 7, 12},
    {12, 7, 3},
    {4, 8, 13},
    {13, 8, 4},
    {5, 8, 12},
    {12, 8, 5},
    {5, 9, 14},
    {14, 9, 5},
    {10, 11, 12},
    {12, 11, 10},
    {11, 12, 13},
    {13, 12, 11},
    {12, 13, 14},
    {14, 13, 12}
};

/* Return the number of pegs on the board. */
int npegs(int board[]);

/* Return 1 if the move is valid on this board, otherwise return 0. */
int valid_move(int board[], int move[]);

/* Make this move on this board. */
void make_move(int board[], int move[]);

/* Unmake this move on this board. */
void unmake_move(int board[], int move[]);

/*
 * Solve the game starting from this board.  Return 1 if the game can
 * be solved; otherwise return 0.  Do not permanently alter the board passed
 * in. Once a solution is found, print the boards making up the solution in
 * reverse order.
 */
int solve(int board[]);

int npegs(int board[])
{
    int i;
    int n_pegs = 0;
    for(i = 0; i < BOARD_SIZE; i++)
    {
        if (board[i])
        /* board is represented as a 1D array of integers
         * value of 0 means that there is no peg and
         * 1 means that there is a peg at that location
         */
        {
            n_pegs++;
        }
    }
    return n_pegs;
}

int valid_move(int board[], int move[])
{
    return (board[move[0]] == 1) && 
           (board[move[1]] == 1) && 
           (board[move[2]] == 0);
    /* 0 and 1 have pegs, and jumps into 3 as an empty space */
}

void make_move(int board[], int move[])
{
    board[move[0]] = 0;
    board[move[1]] = 0;
    board[move[2]] = 1;
}

void unmake_move(int board[], int move[])
{
    board[move[0]] = 1;
    board[move[1]] = 1;
    board[move[2]] = 0;
}

/* Return 1 if the game can be solved; otherwise return 0 */
int solve(int board[])
{
    int i;

    if (npegs(board) == 1) /* base case when there is only one peg left */
    {
        triangle_print(board); /* print out the solution */
        return 1;
    }

    for (i = 0; i < NMOVES; i++) /* loop through all possible moves */
    {
        if (valid_move(board, moves[i])) /* if move is valid */
        {
            int solved;
            make_move(board, moves[i]);
            solved = solve(board);
            unmake_move(board, moves[i]);
            if (solved) /* if the board is solvable */
            {
                triangle_print(board); /* print out the solution */
                return 1;
            }
        }
    }
    return 0;
}

int main(void)
{
    int board[BOARD_SIZE];
    int solved;
    triangle_input(board);
    solved = solve(board);

    if (!solved) /* board is not solvable */
    {
        printf("No such set of moves exist, board is not solvable. \n");
        exit(0);
    }
    return 0;
}
