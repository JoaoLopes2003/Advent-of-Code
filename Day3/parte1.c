#include <stdio.h>
#include <string.h>

int main ()
{
    int sum = 0;
    char line[100];
    int stop = 0;

    FILE *fp = fopen ("input.txt", "r");

    while (fgets (line, 100, fp) != NULL)
    {
        int size = strlen (line);

        for (int i = 0;i<size/2 && !stop;i++)
        {
            for (int j = size/2;j<size && !stop;j++)
            {
                if (line[i] == line[j])
                {
                    if (line[i] >= 97) sum += line[i] - 96;
                    else sum += line[i] - 38;
                    stop = 1;
                }
            }
        }
        stop = 0;
    }
    printf ("%d\n", sum);

    return 0;
}