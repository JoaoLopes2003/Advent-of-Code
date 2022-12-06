#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main ()
{
    // Stores the file line

    char* line = NULL;
    ssize_t read;
    size_t len;

    FILE *fp = fopen ("input.txt", "r");

    read = getline (&line, &len, fp);

    // Stores four characters

    char first = line[0], second = line[1], third = line[2], fourth = line[3];

    // Stores de result

    int res = 4;

    // Findes the first start-of-packet

    while (line[res]!='\0' && (first==second||first==third||first==fourth||second==third||second==fourth||third==fourth))
    {
        first = second;
        second = third;
        third = fourth;
        fourth = line[res];
        res++;
    }

    printf ("%d\n", res);

    return 0;
}