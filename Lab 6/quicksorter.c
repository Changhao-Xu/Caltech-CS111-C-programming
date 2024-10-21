/*
 * CS 111 Lab 6: This program aims to
 * apply quicksort algorithm using linked lists.
 */

#include <stdio.h>
#include "memcheck.h"
#include "linked_list.h"
#include <stdlib.h> /* required for malloc etc. */
#include <string.h>
#include <assert.h>

void usage(char *program_name);
node *quicksort(node *list);

void usage(char *program_name)
{
    fprintf(stderr, "usage: %s [-q] number1 [number2 ... ]\n", program_name);
    /* print the error message to stderr using fprintf */
    exit(1);
}

node *quicksort(node *list)
{
    node *reference, *rest_list,
         *small, *large, *small_list, *large_list, *sorted_list;

    /* if list empty or one node, copy the list as-is and return it */
    if (list == NULL || list->next == NULL) {
        return copy_list(list);
    }

    reference = list; /* create a copy of the first node of the list */
    small = NULL;
    large = NULL;
    for (rest_list = list->next; rest_list != NULL; rest_list = rest_list->next)
    {
        if (rest_list->data < reference->data)
        {
            small = create_node(rest_list->data, small);
            /* a list of all values smaller than the value of the first node */
        }
        else
        {
            large = create_node(rest_list->data, large);
            /* a list of all values greater than
             * or equal to the value of the first node
             */
        }
    }
    
    /* sort these two new lists using
     * a recursive call to the quicksort function
     */
    small_list = quicksort(small);
    large_list = quicksort(large);

    /* append everything together in order */
    large_list = create_node(reference->data, large_list);
    sorted_list = append_lists(small_list, large_list);

    free_list(small);
    free_list(large);
    free_list(small_list);
    free_list(large_list);

    assert(is_sorted(sorted_list));      /* check that the list is sorted */
    return sorted_list;
}

int main(int argc, char *argv[])
{
    int q_arg = 0; /* optional command line arguments "-q" */
    int i;
    node *list, *sorted_list; /* create the original list */

    list = NULL;

    for (i = 1; i < argc; i++)  /* Skip argv[0] (program name) */
    {
        if (strcmp(argv[i], "-q") == 0)
        {
            q_arg = 1;
        }
        else
        {
            list = create_node(atoi(argv[i]), list);
        }
    }
    /* no command-line arguments, or none that represent numbers to be sorted */
    if(list == NULL)
    {
        usage(argv[0]);
    }

    sorted_list = quicksort(list);

    if (!q_arg) /* q_arg == 1 suppresses the output i.e. nothing gets printed */
    {
        print_list(sorted_list);
    }

    free_list(list);
    free_list(sorted_list);
    print_memory_leaks(); /* print out all memory leaks */
    return 0;
}
