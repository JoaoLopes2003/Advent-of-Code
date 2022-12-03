#include <stdio.h>
#include <string.h>

int main ()
{
    int sum = 0;
    char line1[100];
    char line2[100];
    char line3[100];
    int stop = 0;

    FILE *fp = fopen ("input.txt", "r");

    while (fgets (line1, 100, fp) != NULL)
    {
        fgets (line2, 100, fp);
        fgets (line3, 100, fp);

        for (int i = 0;line1[i]!='\0' && !stop;i++)
        {
            for (int j = 0;line2[j]!='\0' && !stop;j++)
            {
                if (line1[i] == line2[j])
                {
                    for (int h = 0;line3[h]!='\0' && !stop;h++)
                    {
                        if (line2[j] == line3[h])
                        {
                            if (line2[j] >= 97) sum += line2[j] - 96;
                            else sum += line2[j] - 38;
                            stop = 1;
                        }
                    }
                }
            }
        }
        stop = 0;
    }
    
    printf ("%d\n", sum);

    return 0;
}