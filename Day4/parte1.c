#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main ()
{
    int fullyCont = 0;
    char line[100];

    FILE *fp = fopen ("input.txt","r");

    while (fgets(line,100,fp)!=NULL)
    {
        int min1, max1, min2, max2;
        char *token;

        token = strtok (line, "-");
        min1 = atoi (token);

        token = strtok (NULL, ",");
        max1 = atoi (token);

        token = strtok (NULL, "-");
        min2 = atoi (token);

        token = strtok (NULL, "-");
        max2 = atoi (token);

        if ((min2>=min1 && max2<=max1) || (min1>=min2 && max1<= max2)) fullyCont++;
    }

    printf ("%d\n", fullyCont);

    return 0;
}