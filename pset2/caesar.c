#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int k = 0; // variable to store key from argv
char enciphered[0]; // empty array to store encrypted message

void getUserInput(void);
void errorMsgArgv(void);
void parseInput(string s);
char mapChar(char c, int offset);
int printEncipherText(void);

int main(int argc, string argv[])
{
  if (argc == 2)
  {
    k = atoi(argv[1]);
    if (k > 0)
    {
        // printf("%i\n", k);
        getUserInput();
    }
    else
    {
        errorMsgArgv();
        return 1;
    }
  }
  else
  {
      errorMsgArgv();
      return 1;
  }
}

void errorMsgArgv(void)
{
    printf("Error: run this program by passing it a single positive integer. \n For example: ./caesar 3 \n");
}

// prompt the user to input a message to encrypt
void getUserInput(void)
{
    // printf("Message to encrypt: ");
    string s = GetString();

    // check to make sure user entered a string of text
    if (strlen(s) > 0)
    {
      parseInput(s);
    }
    else
    {
      getUserInput();
    }
}

// parse the user's input, checking for alpha chars, then checking for upper or lowercase chars
// if not an alpha pass it to our enciphered array
void parseInput(string s)
{
    for (int i = 0, len = strlen(s); i < len; i++)
    {
        if (isalpha(s[i]))
        {
            if (islower(s[i]))
            {
                // do Math for lowercase ascii char
                enciphered[i] = mapChar(s[i], 97);
            }
            else if (isupper(s[i]))
            {
                // do math for uppercase ascii char
                enciphered[i] = mapChar(s[i], 65);
            }
            else
            {
                // nothing else should be here, but if there is something leave it alone
                enciphered[i] = s[i];
            }
        }
        else
        {
            enciphered[i] = s[i];
        }
    }

    printEncipherText();
}

// map char to new ascii position using key
char mapChar(char c, int offset)
{
    int i = (int) c - offset;
    int shifted = (i + k) % 26;
    char cmod = (char) (shifted + offset);
    return cmod;
}

int printEncipherText()
{
    printf("%s\n", enciphered);
    return 0;
}