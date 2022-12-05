#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main ()
{
    char line[100];
    char crates[56][9];
    char res[56];

    FILE *fp = fopen ("input.txt", "r");

    // Stores the crates in the right places

    int i = 7;

    while (i>=0)
    {

        fgets (line, 100, fp);

        for (int j = 1, h = 0;j<34;j+=4,h++)
        {
            if (line[j]!=' ')
            {
                crates[i][h] = line[j];
            }
        }

        i--;
    }

    // Skips to lines of the input file

    while (i<1)
    {
        fgets (line, 100, fp);
        i++;
    }

    // Moves the crates

    while (fgets (line, 100, fp)!=NULL)
    {
        int num, from, to;
        char *token;

        // Jumpes the word "move"

        token = strtok (line, " ");

        // Stores the number of crates to be moved

        token = strtok (NULL, " ");
        num = atoi (token);

        // Jumpes the word "from"

        token = strtok (NULL, " ");

        // Stores the location from where the crates are going to be moved

        token = strtok (NULL, " ");
        from = atoi (token) - 1;

        // Jumpes the word "to"

        token = strtok (NULL, " ");

        // Stores the location to where the crates are going to be moved

        token = strtok (NULL, " ");
        to = atoi (token) - 1;

        // Findes the first position without a crate from a specific stack of crates

        int freeFrom = 0;
        while (crates[freeFrom][from]>=65 && crates[freeFrom][from]<=90) freeFrom++;

        int freeTo = 0;
        while (crates[freeTo][to]>=65 && crates[freeTo][to]<=90) freeTo++;

        // Moves the crates

        while (num>0)
        {
            crates [freeTo][to] = crates [freeFrom-1][from];
            crates [freeFrom-1][from] = ' ';
            freeFrom--;
            freeTo++;
            num--;
        }
        
        // Resets the values

        freeFrom = 0;
        freeTo = 0;
    }

    // Stores the result

    int stack;

    // Finds the top crate in each stack

    for (stack = 0;stack<9;stack++)
    {
        int row = 0;

        for (;crates[row][stack]>=65 && crates[row][stack]<=90;row++);

        res[stack] = crates[row-1][stack];
    }

    res[stack] = '\0';

    // Prints the result

    printf ("%s\n", res);

    return 0;
}