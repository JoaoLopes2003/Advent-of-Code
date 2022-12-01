#include <stdio.h>
#include <stdlib.h>

int main ()
{
    int total = 0;
    int max = 0;

    FILE *fp = fopen ("input.txt", "r");

    char linha[100];

    while (fgets (linha,100,fp)!=NULL)
    {
        if (linha[0]=='\n') total = 0;
        else
        {
            total += atoi(linha);
            if (total>max) max = total;
        }
    }

    printf ("%d\n", max);

    return 0;
}