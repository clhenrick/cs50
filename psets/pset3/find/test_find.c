#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

bool int_compare(int* a, int* b);

int main(void)
{   
    printf("two integers please...\n");
    int n = GetInt();
    int x = GetInt();
    printf("comparing %i, and %i\n", n, x );

    if (int_compare(&n, &x))
    {
        printf("same!\n");
    }
    else
    {
        printf("not same!\n");
    }
}

bool int_compare(int* a, int* b)
{
    if (*a == *b)
    {
        return true;
    }
    else
    {
        return false;
    }
}