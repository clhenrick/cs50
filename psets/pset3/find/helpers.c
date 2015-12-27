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
 * Sorts array of n values using the "selection sort",
 *  an O(n^2) sorting algorithm
 */
void sort(int values[], int n)
{
    
    int* min = malloc(sizeof(int));

    for (int i = 0; i < n - 1; i ++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (values[i] > values[j])
            {
                // if the next value is bigger than the previous,
                // swap the values
                *min = values[j];
                values[j] = values[i];
                values[i] = *min;
                printf("swapped: %i\n", values[i]);
                // recursively iterate over values again
                sort(values, n);
            }
        }
    }

    /* Double check to make sure our array is sorted correctly */
    // for (int i=0; i<n; i++)
    // {
    //     printf("%i\n", values[i] );
    // }

    return;
    
}
