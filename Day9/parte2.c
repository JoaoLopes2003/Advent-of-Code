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

// Checks if we need to move the knot and, if yes, moves the knot to the respective position

int movKnot (Coords *knot1, Coords *knot2)
{
    // Stores if we need to move the knot or not

    int stop = 0;

    // Checks if we need to move the knot

    for (int i = -1;i<2 && !stop;i++)
    {
        for (int j = -1;j<2 && !stop;j++)
        {
            if (knot2->y+i==knot1->y && knot2->x+j==knot1->x)
            {
                stop++;
            }
        }
    }

    // Executes if we need to move the knot

    if (!stop)
    {
        // Moves the knot to the respective location depending on the other knot's new location

        if (knot2->y==knot1->y && knot2->x+2==knot1->x) (knot2->x)++;
        else if (knot2->y==knot1->y && knot2->x-2==knot1->x) (knot2->x)--;
        else if (knot2->x==knot1->x && knot2->y+2==knot1->y) (knot2->y)++;
        else if (knot2->x==knot1->x && knot2->y-2==knot1->y) (knot2->y)--;
        else
        {
            if ((knot2->x-1==knot1->x && knot2->y+2==knot1->y) || (knot2->x-2==knot1->x && knot2->y+1==knot1->y))
            {
                (knot2->x)--;
                (knot2->y)++;
            }
            else if ((knot2->x+1==knot1->x && knot2->y+2==knot1->y) || (knot2->x+2==knot1->x && knot2->y+1==knot1->y))
            {
                (knot2->x)++;
                (knot2->y)++;
            }
            else if ((knot2->x+2==knot1->x && knot2->y-1==knot1->y) || (knot2->x+1==knot1->x && knot2->y-2==knot1->y))
            {
                (knot2->x)++;
                (knot2->y)--;
            }
            else if ((knot2->x-2==knot1->x && knot2->y-1==knot1->y) || (knot2->x-1==knot1->x && knot2->y-2==knot1->y))
            {
                (knot2->x)--;
                (knot2->y)--;
            }
            else if (knot2->x-2==knot1->x && knot2->y-2==knot1->y)
            {
                (knot2->x)--;
                (knot2->y)--;
            }
            else if (knot2->x-2==knot1->x && knot2->y+2==knot1->y)
            {
                (knot2->x)--;
                (knot2->y)++;
            }
            else if (knot2->x+2==knot1->x && knot2->y+2==knot1->y)
            {
                (knot2->x)++;
                (knot2->y)++;
            }
            else
            {
                (knot2->x)++;
                (knot2->y)--;
            }
        }
        return 1;
    }

    return 0;
}

// Moves one knot in relation to the movimentaion of another, if needed, one step at a time

void moveK (Coords *knot1, Coords *knot2, Visited *visited, int nKnot)
{
    // Checks if we need to move the knot and, if yes, moves the knot to the respective position.
    // Also checks if the knot we checking is the tail of the rope and, if yes, adds its
    // new position to the array if it's the first time it visits that position

    if (movKnot (knot1, knot2) && nKnot==9)
    {
        // Adds the tails's new position to the array if it's the first time the tail visits that position

        addTailPos (visited, knot2);
    }
}

// Moves the head of the rope to its new position

void moveHead (char dir, Coords *head)
{
    // Moves the head in the respective direction 1 step

    if (dir=='U') (head->y)++;
    else if (dir=='D') (head->y)--;
    else if (dir=='R') (head->x)++;
    else (head->x)--;
}

// Prints the rope in a map to viasualize it

void printRope (Coords **rope)
{
    char map [50][50];

    for (int j = 0;j<50;j++)
    {
        for (int h = 0;h<50;h++)
        {
            map[j][h] = ' ';
        }
    }

    for (int j = 0;j<10;j++)
    {
        map[rope[j]->y+25][rope[j]->x+25] = j+48;
    }

    for (int j = 0;j<50;j++)
    {
        for (int h = 0;h<50;h++)
        {
            printf ("%c", map[j][h]);
        }
        printf ("\n");
    }
    printf ("\n");
    printf ("--------------------------------\n");
    printf ("\n");
}

int main ()
{
    Coords **rope = malloc(10 * sizeof(Coords));

    for (int i = 0;i<10;i++)
    {
        rope[i] = malloc(sizeof(Coords));
        rope[i]->x = 0;
        rope[i]->y = 0;
    }

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

        // Moves the rope, accordingly to movimentation of the its head

        for (int i = steps;i>0;i--)
        {
            // Moves the head of the rope to its new position

            moveHead (dir, rope[0]);

            // Moves the rest of the rope to its respective new positions, if needed

            for (int j = 0;j<9;j++)
            {
                moveK (rope[j], rope[j+1], visited, j+1);
            }
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

    for (int i = 0;i<10;i++)
    {
        free (rope[i]);
    }

    free (rope);

    return 0;
}