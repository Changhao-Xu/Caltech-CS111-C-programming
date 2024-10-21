/*
 * CS 111 Lab 5: This program aims to
 * simulate a simple 1D cellular automaton.
 */

#include <stdio.h>
#include "memcheck.h"
#include <stdlib.h> /* required for malloc etc. */
#include <time.h> /* time is used for random seed here */

void usage(char *program_name); /* if wrong arg, exit with a usage message */
void print_gen(int *cell, int length); /* print the given generation */
void update_cell(int *cell, int *next_gen, int length); /* update current gen */
void random_initialize(int *cell, int length);

void usage(char *program_name)
{
    fprintf(stderr,
            "usage: %s number of cells, number of generations\n",
            program_name);
    /* print the error message to stderr using fprintf */
    exit(1);
}

void print_gen(int *cell, int length)
{
    int i;
    for (i = 0; i < length; i++)
    {
        if (cell[i] == 0)
        {
            printf("."); /* if 0, i.e. empty, print . */
        }
        else
        {
            printf("*"); /* if 1, i.e. full, print * */
        }
    }
    printf("\n");
}

void update_cell(int *cell, int *next_gen, int length)
{
    /*
     * Update rule: If the current cell is empty,
     * and one of the two adjacent cells is full (but not both),
     * set the current cell to be full.
     * Otherwise set the current cell to be empty.
     * In this rule, first and last elements are always 0.
     */
    int i;
    next_gen[0] = 0;
    next_gen[length - 1] = 0;

    /* Process elements, skipping the first and last */
    for (i = 1; i < length - 1; i++)
    {
        if (cell[i] == 0 && ((cell[i - 1] + cell[i + 1]) == 1))
        {
            next_gen[i] = 1;
        }
        else
        {
            next_gen[i] = 0;
        }
    }

    /* Assigns all next_gen elements to the current cell */
    for (i = 0; i < length; i++)
    {
        cell[i] = next_gen[i];
    }
}

void random_initialize(int *cell, int length)
{
    int i;

    srand(time(0)); /* Random seed with time. */

    /* Fill each index with 0 or 1 with about 50% each */
    for (i = 0; i < length; i++)
    {
        cell[i] = rand() % 2;
    }
}

int main(int argc, char *argv[])
{
    int *cell, *next_gen, length, gen, i;

    if (argc != 3)
    {
        /* correct number of arguments == 3, program, int, int */
        usage(argv[0]);
    }

    length = atoi(argv[1]); /* length is numbers of cells in the 1dCA */
    gen = atoi(argv[2]); /* gen is number of generations to compute */

    cell = (int *) calloc(length, sizeof(int));
    next_gen = (int *) calloc(length, sizeof(int));

    /* Check that the calloc call succeeded. */
    if (cell == NULL || next_gen == NULL)
    {
        fprintf(stderr, "Error! Memory allocation failed!\n");
        exit(1);  /* abort the program */
    }

    random_initialize(cell, length);
    print_gen(cell, length);

    for (i = 0; i < gen; i++)
    {
        update_cell(cell, next_gen, length);
        print_gen(cell, length);
    }

    free(cell);
    free(next_gen);
    print_memory_leaks(); /* print out all memory leaks */

    return 0;
}