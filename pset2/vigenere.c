#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

void errorMsgArgv(void);
char encipherChar(char c, char k, int offset);

int main(int argc, string argv[])
{
    // make sure only one argument is passed to program
    if (argc != 2) {
        errorMsgArgv();
        return 1;
    }

    // variable to hold the vigenere key
    string k = argv[1];
    // length of k, will need this later for a modulo operation
    int l = (int) strlen(k);
    // variable to hold current position of k
    int p = 0;

    // make sure the argument consists of alphabetical characters only
    for (int i = 0, l = strlen(k); i < l; i++)
    {
        if (!isalpha(k[i]))
        {
            errorMsgArgv();
            return 1;
        }

        if (isupper(k[i]))
        {
            k[i] = tolower(k[i]);
        }

        k[i] = k[i] - 97;
    }

    // variable to hold the users message to encrypt
    string s = GetString();
    // variable to hold encrypted message
    char enciphered[l];

    // parse message
    for (int i = 0, len = strlen(s); i < len; i++)
    {
        if (isalpha(s[i]))
        {
            // make sure we don't exceed the bounds of the k char array
            p = p % l;

            // ideally there would be one function for lower and upper case that could take parameters
            // such as the ascii offset, position of k, etc. so as not to repeat the code.
            if (islower(s[i]))
            {
                // do ascii Math for lowercase ascii char
                enciphered[i] = encipherChar(s[i], k[p], 97);
                p++;
            }
            else if (isupper(s[i]))
            {
                // do ascii Math for uppercase char
                enciphered[i] = encipherChar(s[i], k[p], 65);
                p++;
            }
            else
            {
                // nothing else should be here, but if there is something leave it alone
                enciphered[i] = s[i];
            }
        }
        else
        {
            // if the char is not in the alphabet skip it
            enciphered[i] = s[i];
        }

        // print the enciphered character 
        printf("%c", enciphered[i]);
        
        if (i == (len -1))
        {
            // after the last char print a new line
            printf("\n");
        }
    }

}

// message to display to user if program is not called correctly
void errorMsgArgv(void)
{
    printf("Requires a single argument consisting of alphabetical characters only, no spaces or special characters. \n");
}

// function to encipher a character
// takes current char of message, a char of the key, and ascii offset integer
char encipherChar(char c, char k, int offset)
{
    int x = k; // array position in k
    int j = (int) c - offset; // make sure position of s[i] is between 0 - 25
    int shifted = (j + x) % 26;
    char m = (char) (shifted + offset);
    return m;
}