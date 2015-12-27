/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include <stdio.h>
#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    
    if (n <= 0)
        return 1;

    int* p;
    int* q = malloc(sizeof(int));

    if (q == NULL)
        return 1;

    *q = value;
    p = values;
    
    for (int i = 0; i < n; i++)
    {
        if (*(p + i) == *q) {
            return 1;
        }
    }

    return 0;
    
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // TODO: implement an O(n^2) sorting algorithm
    return;
}
