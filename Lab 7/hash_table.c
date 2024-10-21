/*
 * CS 11, C Track, lab 7
 *
 * FILE: hash_table.c
 *     Implementation of the hash table functionality.
 *
 */

/*
 * Include the declaration of the hash table data structures
 * and the function prototypes.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_table.h"
#include "memcheck.h"


/*** Hash function. ***/
/* convert string to integer within mod NSLOTS */
int hash(char *s)
{
    int i;
    int sum;
    i = 0;
    sum = 0;
    while(s[i] != 0)
    {
        sum += s[i];
        i++;
    }
    return sum % NSLOTS;
}


/*** Linked list utilities. ***/

/* Create a single node. */
node *create_node(char *key, int value)
{
    node *new_node;
    new_node = (node *)malloc(sizeof(node));
    /* Check that the malloc call succeeded. */
    if(new_node == NULL)
    {
        fprintf(stderr, "ERROR: memory allocation failed!\n");
        exit(1);    /* abort the program */
    }
    new_node->key = key;
    new_node->value = value;
    new_node->next = NULL;

    return new_node;    
}


/* Free all the nodes of a linked list. */
void free_list(node *list)
{
    node *temp;
    while(list != NULL)
    {
        temp = list;
        list = list->next;
        free(temp->key);
        free(temp);
    }
}


/*** Hash table utilities. ***/

/* Create a new hash table. */
hash_table *create_hash_table()
{
    hash_table *new_hash_table;
    new_hash_table = (hash_table *)malloc(sizeof(hash_table));
    /* Check that the malloc call succeeded. */
    if(new_hash_table == NULL)
    {
        fprintf(stderr, "ERROR: memory allocation failed!\n");
        exit(1);    /* abort the program */
    }

    new_hash_table->slot = (node**)calloc(NSLOTS, sizeof(node *));
    /* Check that the calloc call succeeded. */
    if(new_hash_table->slot == NULL)
    {
        fprintf(stderr, "ERROR: memory allocation failed!\n");
        exit(1);    /* abort the program */
    }

    return new_hash_table;
}


/* Free a hash table. */
void free_hash_table(hash_table *ht)
{
    node **temp = ht->slot;
    int i;
    for (i = 0; i < NSLOTS; i++)
    {
        free_list(temp[i]);
        /* each hash table slot is a linked list */
    }
    free(temp);
    free(ht);
}


/*
 * Look for a key in the hash table.  Return 0 if not found.
 * If it is found return the associated value.
 */
int get_value(hash_table *ht, char *key)
{
    node **temp = ht->slot;
    node *target_list;
    int key_value;
    key_value = hash(key);
    target_list = temp[key_value];
    /* the target list with matched hash key */
    while (target_list != NULL)
    {
        if(strcmp(key, target_list->key) == 0)
        /* find the one with matched key */
        {
            return target_list->value;
        }
        target_list = target_list->next;
    }
    /* key not found */
    return 0;
}


/*
 * Set the value stored at a key.  If the key is not in the table,
 * create a new node and set the value to 'value'.  Note that this
 * function alters the hash table that was passed to it.
 */

void set_value(hash_table *ht, char *key, int value)
{
    node **temp = ht->slot;
    node *target_list;
    node *new_node;
    int key_value;
    key_value = hash(key);
    target_list = temp[key_value];
    /* the target list with matched hash key */
    if (ht == NULL || ht->slot == NULL) {
        /* Handle error: hash table or its slots are not initialized */
        return;
    }
    
    while (target_list != NULL)
    {
        if(strcmp(key, target_list->key) == 0)
        /* find the one with matched key */
        {
            target_list->value = value;
            free(key);
            /* since key exists 
             * need to free input key
             * to prevent memory leak
             */
            return;
        }
        target_list = target_list->next;
    }
    /* key not found */
    new_node = create_node(key, value);
    /* add new node to beginning of list */
    new_node->next = temp[key_value];
    /* Note that temp[key_value] can not be 
     * target_list since after the while loop
     * target_list has reached the end of NULL
     */
    temp[key_value] = new_node;
}

/* Print out the contents of the hash table as key/value pairs. */
void print_hash_table(hash_table *ht)
{
    node **temp = ht->slot;
    node *target_list;
    int i;
    for (i = 0; i < NSLOTS; i++)
    {
        target_list = temp[i];
        /* each hash table slot is a linked list */
        while (target_list != NULL)
        {
            printf("%s %d\n", target_list->key, target_list->value);
            target_list = target_list->next;
        }
    }
}
