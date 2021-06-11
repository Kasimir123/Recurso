#include "list.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Initializes the list
List * initList()
{
    // Mallocs the list
    List * list = (List *)malloc(sizeof(List));

    // Capacity
    list->capacity = 5;
    
    // Count
    list->count = 0;

    // Malloc chars list
    list->list = (char **)malloc(sizeof(char *) * list->capacity);

    // Return list
    return list;
}

// Add element to list
void addElement(List * list, char * element)
{
    // Check if at capacity
    if (list->count >= list->capacity)
    {
        // Double capacity
        list->capacity *= 2;

        // Reallocate the list
        list->list = (char **)realloc(list->list, sizeof(char *) * list->capacity);
    }
    
    // Add the element
    list->list[list->count] = element;

    // Increase counter
    list->count++;
}

// Check if the list contains the element
char getElement(List * list, char * element)
{
    // Loop through list
    for (int i = 0; i < list->count; i++)
        // If in list then return 0
        if (!strcmp(list->list[i], element)) return i;
    return -1;
}

// Free the list
void freeList(List * list)
{
    // free all strings in list
    for (int i = 0; i < list->capacity; i++)
        free(list->list[i]);

    // free string list
    free(list->list);

    // free actual list
    free(list);
}