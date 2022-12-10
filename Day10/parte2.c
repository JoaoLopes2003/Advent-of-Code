#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Checks if one of the sprite's pixels is being drawn and, if yes, draws a lit pixel in that position

int checkSprite (int column, int resgX)
{
    // Checks if the CRT is drawing any of three pixels of the sprite

    for (int i = -1;i<2;i++)
    {
        if (resgX+i==column)
        {
            return 1;
        }
    }
    return 0;
}

int main ()
{
    // Opens the "input.txt" file

    FILE *fp = fopen ("input.txt", "r");

    // Creates and inicializes the register X, row CRT is at, column CRT is at and the pixels drawn by the CRT

    int resgX = 1;
    int row = 0;
    int column = 0;
    char CRT [6][40];

    // Sets all the pixels of the CRT to dark

    for (int i = 0;i<6;i++)
    {
        for (int j = 0;j<40;j++)
        {
            CRT[i][j] = '.';
        }
    }

    // Goes thorugh every line of the file

    char *line = NULL;
    ssize_t read;
    size_t len;

    while ((read = getline(&line,&len,fp))!=-1)
    {
        // Tokenizes the line into an instruction and a numerical value, if existing

        char *token;
        char inst;
        int num;

        token = strtok (line, " ");
        inst = token[0];

        // Executes if the instruction is a "noop"

        if (inst=='n')
        {
            // Checks if one of the sprite's pixels is being drawn and, if yes, draws a lit pixel in that position

            if (checkSprite (column, resgX))
            {
                CRT[row][column] = '#';
            }

            // Checks if we reacked the end of a row and, if yes, changes the row and resets the column

            if (column==39)
            {
                column = 0;
                row++;
            }

            // Moves the column 1 unit to the right while we dodn't reach the end of the row

            else
            {
                column++;
            }
        }

        // Executes if the instruction is a "addx"

        else
        {
            token = strtok (NULL, "\n");
            num = atoi (token);

            // Gets the number we want to add

            for (int i = 0;i<2;i++)
            {
                // Checks if one of the sprite's pixels is being drawn and, if yes, draws a lit pixel in that position

                if (checkSprite (column, resgX))
                {
                    CRT[row][column] = '#';
                }

                // Checks if we reacked the end of a row and, if yes, changes the row and resets the column

                if (column==39)
                {
                    column = 0;
                    row++;
                }

                // Moves the column 1 unit to the right while we dodn't reach the end of the row

                else
                {
                    column++;
                }
            }
            // Adds the number of the instruction to the register X after the two cycles of waiting

            resgX += num;
        }
    }

    // Prints all the lit and dark pixels drawn by the CRT

    for (int i = 0;i<6;i++)
    {
        for (int j = 0;j<40;j++)
        {
            printf ("%c", CRT[i][j]);
        }
        printf ("\n");
    }

    return 0;
}