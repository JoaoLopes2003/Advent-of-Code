#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main ()
{
    // Opens the "input.txt" file

    FILE *fp = fopen ("input.txt", "r");

    // Creates and inicializes the register X, the cycle counter, and the total strenght of the sinal

    int cycles = 1;
    int resgX = 1;
    int strenght = 0;

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
            // Checks if it's one of the cycles we want to add to the total strenght of the signal

            if (cycles==20 || cycles==60 || cycles==100 || cycles==140 || cycles==180 || cycles==220)
            {
                strenght += cycles * resgX;
            }
            cycles++;
        }

        // Executes if the instruction is a "addx"

        else
        {
            // Gets the number we want to add

            token = strtok (NULL, "\n");
            num = atoi (token);

            // Runs tow cycles as this instruction takes to cycles to execute

            for (int i = 0;i<2;i++)
            {
                // Checks if it's one of the cycles we want to add to the total strenght of the signal

                if (cycles==20 || cycles==60 || cycles==100 || cycles==140 || cycles==180 || cycles==220)
                {
                    strenght += cycles * resgX;
                }
                cycles++;
            }
            // Adds the number of the instruction to the register X after the two cycles of waiting

            resgX += num;
        }
    }

    // Prints the total strenght of the signal

    printf ("%d\n", strenght);

    return 0;
}