/**
 * mario.c
 *
 * Chris Henrick
 * chrishenrick@gmail.com
 * 
 * Creates a right aligned half-pyramid of hashes
 * height dependent upon size of an integer
 */

#include <stdio.h>
#include <cs50.h>

void promptUser(void);
void checkInput(int n);
void printChar(string s, int n);
void makePyramid(int n);

int main(void)
{
  // start the program by prompting our user
  promptUser();
}

void promptUser()
{   
    // prompt the user for a positive int less than 24
    printf("Please give a positive number less than 24: ");
    int n = GetInt();
    checkInput(n);
}

void checkInput(int n)
{
    // check the value of the user's input
    if (n > 0 && n < 24)
    {   
        // upon receiving a correct number, make the pyramid
        makePyramid(n);
    }
    else
    {   
        // otherwise prompt the user again
        promptUser();
    }
}

void printChar(string s, int n)
{
    // prints a char a specified number of times
    for (int i = 0; i < n; i++)
    {
        printf("%s", s);
    }

}

void makePyramid(int n)
{
    // makes the half-pyramid of hashes based on a given integer value
    for (int i = 0; i < n; i++)
    {
      // print spaces
      printChar(" ", n - 1 - i);
      // print hashes
      printChar("#", 2 + i);
      // print newline
      printf("\n");
    }
}


