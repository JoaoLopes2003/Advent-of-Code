#include <stdio.h>
#include <stdlib.h>

int main ()
{
    int total = 0;
    int first = 0, second = 0, third = 0;

    FILE *fp = fopen ("input.txt", "r");

    char linha[100];

    while (fgets (linha,100,fp)!=NULL)
    {
        if (linha[0]!='\n') total += atoi(linha);
        else
        {
            if (total>first)
            {
                third = second;
                second = first;
                first = total;
            }
            else if (total>second)
            {
                third = second;
                second = total;
            }
            else if (total>third)
            {
                third = total;
            }
            total = 0;
        }
    }

    printf ("%d\n", first + second + third);

    return 0;
}