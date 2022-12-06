#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool verifyMessage (char *message)
{
    for (int i = 0; message[i+1]!='\0';i++)
    {
        for (int j = i+1;message[j]!='\0';j++)
        {
            if (message[i] == message[j]) return 0;
        }
    }
    return 1;
}

int main ()
{
    // Stores the file line

    char* line = NULL;
    ssize_t read;
    size_t len;

    FILE *fp = fopen ("input.txt", "r");

    read = getline (&line, &len, fp);

    // Stores four characters

    char message[15];

    // Stores de result

    int res = 14;

    // Initializes the array with the first 14 characters

    strncpy (message, line, 14);
    message[14] = '\0';

    // Findes the first start-of-packet

    while (line[14]!='\0' && !verifyMessage(message))
    {
        line++;
        strncpy (message, line, 14);
        message[14] = '\0';
        res++;
    }

    printf ("%d\n", res);

    return 0;
}