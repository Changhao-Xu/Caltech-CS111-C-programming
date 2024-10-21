/*
 * CS 111 Lab 3: This program aims to
 * sort an array of numbes using
 * either the minimum element sort
 * or the bubble sort algorithm.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX_INT 32
/* accept up to 32 numbers (integers) on the command line to sort */

/* min_sort is the func of the minimum element sort algorithm */
void min_sort(int array[], int num_elements);
/* bubble_sort is the func of the bubble sort algorithm */
void bubble_sort(int array[], int num_elements);

int main(int argc, char *argv[])
{
    int i;
    int b_arg = 0; /* optional command line arguments b */
    int q_arg = 0; /* optional command line arguments q */
    int wrong_arg = 0; /* optional command line arguments is wrong */
    int array_to_sort[MAX_INT]; /* array to sort */
    int count = 0; /* number of elements */

    
    for (i = 1; i < argc; i++)  /* Skip argv[0] (program name) */
    {
        if (strcmp(argv[i], "-b") == 0)
        {
            b_arg = 1;
        }
        else if (strcmp(argv[i], "-q") == 0)
        {
            q_arg = 1;
        }
        else if (count <= MAX_INT)
        {
            array_to_sort[count] = atoi(argv[i]); /* count = i - 1 */
            count++;
        }
        else
        {
            wrong_arg = 1;
        }
    }
    if (count <= 0 || count > 32 || wrong_arg)
    /* more than 32 numbers or no numbers at all, or wrong argument */
    {
        fprintf(stderr, "usage: %s [-b] [-q] number1 [number2 ... ] "
                        "(maximum 32 numbers)\n", argv[0]);
        exit(1);
    }
    if (b_arg)
    {
        bubble_sort(array_to_sort, count);
    }
    else
    {
        min_sort(array_to_sort, count);
    }
    if (!q_arg)
    /* q_arg == 1 suppresses the output i.e. nothing gets printed */
    {
        for (i = 0; i < count; i++) {
            printf("%d\n", array_to_sort[i]);
        }        
    }
   return 0;
}

void min_sort(int array[], int num_elements)
{
    int start, i, temp;

    for(start = 0; start < num_elements; start++) {
        int smallest = start; /* index for smallest elem in array */

        for (i = start; i < num_elements; i++) {
            if (array[i] < array[smallest]) {
                smallest = i;
            }
        }
        temp = array[smallest]; /* swap array[start] and array[smallest] */
        array[smallest] = array[start];
        array[start] = temp;
    }
    
    /* Check that the array is sorted correctly. */
    for (i = 1; i < num_elements; i++)
    {
        assert(array[i] >= array[i - 1]);
    }
}

void bubble_sort(int array[], int num_elements)
{
    int start, i, temp;

    for (start = 0; start < num_elements - 1; start++) {
        for (i = 0; i < num_elements - start - 1; i++) {
            if (array[i] > array[i + 1]) {
                /* swap the elements */ 
                temp = array[i];
                array[i] = array[i + 1];
                array[i + 1] = temp;
            }
        }
    }

    /* Check that the array is sorted correctly. */
    for (i = 1; i < num_elements; i++)
    {
        assert(array[i] >= array[i - 1]);
    }
}
