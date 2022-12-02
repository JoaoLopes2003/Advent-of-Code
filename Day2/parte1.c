#include <stdio.h>

int main ()
{
    int total = 0;
    char linha[5];

    FILE *fp = fopen ("input.txt", "r");

    while (fgets(linha,5,fp) != NULL)
    {
        if (linha[2] == 'Y')
        {
            total += 2;
            if (linha[0] == 'A') total += 6;
            else if (linha[0] == 'B') total += 3;
        }
        else if (linha[2] == 'X')
        {
            total += 1;
            if (linha[0] == 'A') total += 3;
            else if (linha[0] == 'C') total += 6;
        }
        else
        {
            total += 3;
            if (linha[0] == 'B') total += 6;
            else if (linha[0] == 'C') total += 3;
        }
    }

    printf ("%d\n", total);

    return 0;
}