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
 * Implements a "binary search" algorithm
 * requires values to be sorted before searching 
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    printf("n value: %i\n", n);
    
    if (n <= 0)
    {
        return 1;
    }

    // while length of list > 0
      // look at middle of list
      // if number is found, return true
      // else if number is higher search left
      // else if number is lower search right
      // call self
    // return false

    int* p; 
    int* q = malloc(sizeof(int));

    if (q == NULL)
    {
        return 1;
    }

    p = values;
    *q = value;

    /* view the contents of our array */
    // printf("searching values: \n");
    // for (int i = 0; i < n; i++)
    // {
    //     printf("%i\n", values[i]);
    // }

    // current value to search against
    int cur = *(p + (n/2));

    // printf("current value to search against: %i\n", cur);
    
    if (n > 0)
    {
        if (cur == *q) {
            printf("found %i!\n", *q);
            return true;
        }
        else if (cur != *q && n == 1)
        {
            return false;
        }
        else if (cur > *q)
        {
            // modify n to exclude top half of array
            return search(value, values, n/2);
        }
        else if (cur < *q)
        {
            // reassign values to exclude bottom half
            int new_start = (n/2);
            
            printf("new start: %i\n", new_start);

            values = values + (new_start);
            int new_n = n - (n/2);
            return search(value, values, new_n);
        } 
    }

    return false;

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
    for (int i=0; i<n; i++)
    {
        printf("%i\n", values[i] );
    }
    printf("\n");

    return;
    
}
