#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

/*
 * Steps:
 * - get string input from user
 * - iterate over string array
 * - check to see if character is either index 0 in the array
 *   or if character follows a space
 * - convert the character to caps and print to std out
 */

void parseString(string s);
void checkCaps(char c);

int main(void)
{
    // printf("Tell me your name please! ");
    string s = GetString();
    parseString(s);
}

// iterates over the string array and looks for 
// what should be characters representing initials
// in a name
void parseString(string s)
{

    for (int i = 0, len = strlen(s); i < len; i++) {
      if (i == 0)
      {
          checkCaps(s[i]);
      }
      else if (isspace(s[i]))
      {
          checkCaps(s[i + 1]);
      }
    }

    printf("\n");
}

// checks if a character is uppercase, if not makes it so
void checkCaps(char c)
{
  if (c >= 'a' && c <= 'z')
  {
      printf("%c", c - ('a' - 'A'));  
  }
  else
  {
      printf("%c", c);
  }
}