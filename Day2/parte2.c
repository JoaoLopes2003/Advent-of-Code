#include <stdio.h>

int main ()
{
    int total = 0;
    char linha[5];

    FILE *fp = fopen ("input.txt", "r");

    while (fgets(linha,5,fp) != NULL)
    {
        if (linha[2] == 'Y')                                // Need to draw
        {
            total += 3;
            if (linha[0] == 'A') total += 1;
            else if (linha[0] == 'B') total += 2;
            else total += 3;
        }
        else if (linha[2] == 'X')                           // Need to lose
        {
            if (linha[0] == 'A') total += 3;
            else if (linha[0] == 'B') total += 1;
            else total += 2;
        }
        else                                                // Need to win
        {
            total += 6;
            if (linha[0] == 'A') total += 2;
            else if (linha[0] == 'B') total += 3;
            else total += 1;
        }
    }

    printf ("%d\n", total);

    return 0;
}