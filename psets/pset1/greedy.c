/**
 * greedy.c
 *
 * Chris Henrick
 * chrishenrick@gmail.com
 * 
 * Calculates the least number of coins using quarters, dimes, nickles, 
 * and pennies that would make up a given U.S. dollar monetary amount.
 */

#include <stdio.h>
#include <cs50.h>
#include <math.h>

// prompt user for amount of change
 // test for input to be a float
 // round to 2 decimal places
 // convert to pennies (cast to integer)
// always use largest coin possible
// variables for amount & number of coins
// print out number of coins used

void promptUser(void);
void processInput(float f);
void makeChange(int n);
void logNumCoins(int n);

int main(void)
{
    promptUser();
}

void promptUser()
{
    printf("How much change do you need? ");
    float f = GetFloat();
    processInput(f);
}

void processInput(float f)
{   
    if (f > 0)
    {
        f = f * 100;
        int x = (int)round(f);
        makeChange(x);
    }
    else
    {
        promptUser(); 
    }
}

void makeChange(int n)
{
    int numCoins = 0;
    int quarters = 0;
    int dimes = 0;
    int nickles = 0;
    int pennies = 0;
    int amount = n;
    
    if (amount % 25 == 0)
    {
        quarters = amount / 25;
        numCoins += quarters;
        amount = 0;
    } 
    else if (amount % 25 < amount)
    {
        quarters += amount / 25;
        numCoins += quarters;
        amount = amount % 25;
    }

    // printf("quarters: %i\n", quarters);

    if (amount % 10 == 0)
    {
        dimes += amount / 10;
        numCoins += dimes;
        amount = 0;
    } 
    else if (amount % 10 < amount)
    {
        dimes = amount / 10;
        numCoins += dimes;
        amount = amount % 10;
    }

    // printf("dimes: %i\n", dimes);

    if (amount % 5 == 0)
    {
        nickles = amount / 5;
        numCoins += nickles;
        amount = 0;
    }
    else if (amount % 5 < amount)
    {
        nickles = amount / 5;
        numCoins += nickles;
        amount = amount % 5;
    }

    // printf("nickles: %i\n", nickles);

    if (amount % 1 == 0)
    {
        pennies = amount;
        numCoins += pennies;
        amount = 0;
    }

    // printf("pennies: %i\n", pennies);

    logNumCoins(numCoins);

}

void logNumCoins(int n)
{
    printf("%i\n", n);
}