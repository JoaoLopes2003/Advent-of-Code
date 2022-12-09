#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct coords
{
    int x;                                  // Position in the x axis
    int y;                                  // Position in the y axis
} Coords;

typedef struct visited
{
    int size;                               // Memory allocated for the array of positions visited by the tail at least once
    int sp;                                 // Positions the tail visited at least once
    struct coords **positions;              // Array of positions visited by the tail at least once
} Visited;

// Adds the tails's new position to the array if it's the first time the tail visits that position

void addTailPos (Visited *visited, Coords *tail)
{
    // Stores the position of the array we are checking

    int i = 0;

    // Checks if the new position his already in the array

    for (;i<visited->sp && (visited->positions[i]->x!=tail->x || visited->positions[i]->y!=tail->y);i++);

    // Adds the position to the array in case it wasn't already in it

    if (i==visited->sp)
    {
        // Expands the memory allocated for the array in case it's already full

        if (visited->size==visited->sp)
        {
            visited->size *= 2;
            visited->positions = realloc (visited->positions, visited->size * sizeof(sizeof(Coords*)));
        }

        // Adds the new position to the array

        visited->positions[visited->sp] = malloc(sizeof(struct coords));
        visited->positions[visited->sp]->x = tail->x;
        visited->positions[visited->sp]->y = tail->y;
        (visited->sp)++;
    }
}

// Checks if we need to move the tail and, if yes, moves the tail to the respective position

int movTail (char dir, Coords *head, Coords *tail)
{
    // Stores if we need to move the tail or not

    int stop = 0;

    // Checks if we need to move the tail

    for (int i = -1;i<2 && !stop;i++)
    {
        for (int j = -1;j<2 && !stop;j++)
        {
            if (tail->y+i==head->y && tail->x+j==head->x)
            {
                stop++;
            }
        }
    }

    // Executes if we need to move the tail

    if (!stop)
    {
        // Moves the tail to the respective location depending on the head's new location

        if (tail->y==head->y && dir=='R') (tail->x)++;
        else if (tail->y==head->y && dir=='L') (tail->x)--;
        else if (tail->x==head->x && dir=='U') (tail->y)++;
        else if (tail->x==head->x && dir=='D') (tail->y)--;
        else
        {
            if ((tail->x-1==head->x && tail->y+2==head->y) || (tail->x-2==head->x && tail->y+1==head->y))
            {
                (tail->x)--;
                (tail->y)++;
            }
            else if ((tail->x+1==head->x && tail->y+2==head->y) || (tail->x+2==head->x && tail->y+1==head->y))
            {
                (tail->x)++;
                (tail->y)++;
            }
            else if ((tail->x+2==head->x && tail->y-1==head->y) || (tail->x+1==head->x && tail->y-2==head->y))
            {
                (tail->x)++;
                (tail->y)--;
            }
            else
            {
                (tail->x)--;
                (tail->y)--;
            }
        }
        return 1;
    }

    return 0;
}

// Moves the head and tail, if needed, one step at a time

void moveHT (char dir, Coords *head, Coords *tail, Visited *visited)
{
    // Moves the head in the respective direction 1 step

    if (dir=='U') (head->y)++;
    else if (dir=='D') (head->y)--;
    else if (dir=='R') (head->x)++;
    else (head->x)--;

    // Checks if we need to move the tail and, if yes, moves the tail to the respective position

    if (movTail (dir, head, tail))
    {
        // Adds the tails's new position to the array if it's the first time the tail visits that position

        addTailPos (visited, tail);
    }
}

int main ()
{
    // Inicilaizes the coordinates of the head of the rope

    Coords *head = malloc(sizeof(Coords));
    head->x = 0;
    head->y = 0;

    // Inicilaizes the coordinates of the tail of the rope

    Coords *tail = malloc(sizeof(Coords));
    tail->x = 0;
    tail->y = 0;

    // Creates a array that stores the positions that the tail of the rope already visited

    Visited *visited = malloc(sizeof(Visited));
    visited->sp = 0;
    visited->size = 4;
    visited->positions = malloc(visited->size * sizeof(Coords*));

    // Adds the starting position to the array of visited coordinates by the tail of the rope

    visited->positions[0] = malloc (sizeof(struct coords));
    visited->positions[0]->x = 0;
    visited->positions[0]->y = 0;
    (visited->sp)++;

    // Opens the "input.txt" file

    FILE *fp = fopen ("input.txt", "r");

    // Reads every line of the file

    char *line = NULL;
    ssize_t read;
    size_t len;

    while ((read = getline(&line,&len,fp))!=-1)
    {
        // Stores the direction and steps the head is moving, respectively

        char dir;
        int steps;

        // Tokenizes the line to find in which direction the head is moving and how many steps is moving in that direction

        char *token;

        token = strtok (line, " ");
        dir = token[0];

        token = strtok (NULL,"\n");
        steps = atoi (token);

        // Moves the head and tail, if needed, one step at a time

        for (int i = steps;i>0;i--)
        {
            moveHT (dir, head, tail, visited);
        }
    }

    // Frees the memory alocated for the variable line

    free (line);

    // Stores the number of positions that the tail of the rope visited at least once

    int positions = visited->sp;

    // Prints the number of positions that the tail of the rope visited at least once

    printf ("%d\n", positions);

    // Frees the space alocated for all the variables

    for (int i = visited->size-1;i>=0;i--)
    {
        free (visited->positions[i]);
    }

    free (visited);

    free (head);

    free (tail);

    return 0;
}