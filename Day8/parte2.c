#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Findes the highest scenic score from all the trees

int maxScenic (int **grid, int nRows, int nColumns)
{
    // Stores the max Scenic score, the scenic score of any tree
    // and the distance of any tree in any direction

    int maxScenic = 0;
    int scenic = 1;
    int distance = 0;

    // Goes through every tree in the grid

    for (int row = 0;row<nRows;row++)
    {
        for (int column = 0;column<nColumns;column++)
        {
            // Variable i is used to navigate through the grid, starting at the tree we are at
            // and going to the left till we find a tree with the same height or heigher than the tree
            // we are checking

            int i = 1;

            // Stores the height of the tree we are checking

            int tree = grid [row][column];

            // Increases the distance in 1 if the tree immediately on the left of the tree we are checking
            // is higher or iqual to the height of the tree we are checking

            if (column-i>=0 && tree<=grid[row][column-i])
            {
                distance++;
            }

            // Counts the number of trees we can see from the tree we are checking (moving to the left)
            // and stops when findes a tree of the same height or higher or theres no more trees

            for (;column-i>=0 && tree>grid[row][column-i];i++)
            {
                distance++;

                // Checks if the height of the next tree to the left is equal or higher to the height of the tree we are checking,
                // and increments the distance by 1 if it is

                if (column-i-1>=0 && tree<=grid[row][column-i-1])
                {
                    distance++;
                }
            }

            // Multiplies the scenic of the tree by the distance (left only)

            scenic *= distance;

            // Resets the value of the variable distance and i

            distance = 0;
            i = 1;

            // Increases the distance in 1 if the tree immediately on the right of the tree we are checking
            // is higher or iqual to the height of the tree we are checking

            if (column+i<nColumns && tree<=grid[row][column+i])
            {
                distance++;
            }

            // Counts the number of trees we can see from the tree we are checking (moving to the right) and stops when
            // findes a tree of the same height or higher or theres no more trees

            for (;column+i<nColumns && tree>grid[row][column+i];i++)
            {
                distance++;

                // Checks if the height of the next tree moving up is equal or higher to the height of the tree we are checking,
                // and increments the distance by 1 if it is

                if (column+i+1<nColumns && tree<=grid[row][column+i+1])
                {
                    distance++;
                }
            }

            // Multiplies the scenic of the tree by the distance (right only)

            scenic *= distance;

            // Resets the value of the variable distance and i

            distance = 0;
            i = 1;

            // Increases the distance in 1 if the tree immediately on the top of the tree we are checking
            // is higher or iqual to the height of the tree we are checking

            if (row-i>=0 && tree<=grid[row-i][column])
            {
                distance++;
            }

            // Counts the number of trees we can see from the tree we are checking (moving up) and stops when
            // findes a tree of the same height or higher or theres no more trees

            for (;row-i>=0 && tree>grid[row-i][column];i++)
            {
                distance++;
                if (row-i-1>=0 && tree<=grid[row-i-1][column])
                {
                    distance++;
                }
            }

            // Multiplies the scenic of the tree by the distance (up only)

            scenic *= distance;

            // Resets the value of the variable distance and i
            
            distance = 0;
            i = 1;

            // Increases the distance in 1 if the tree directly below of the tree we are checking
            // is higher or iqual to the height of the tree we are checking

            if (row+i<nRows && tree<=grid[row+i][column])
            {
                distance++;
            }

            // Counts the number of trees we can see from the tree we are checking (moving down) and stops when
            // findes a tree of the same height or higher or theres no more trees

            for (;row+i<nRows && tree>grid[row+i][column];i++)
            {
                distance++;
                if (row+i+1<nRows && tree<=grid[row+i+1][column])
                {
                    distance++;
                }
            }

            // Multiplies the scenic of the tree by the distance (down only)

            scenic *= distance;

            // Checks if the scenic score of the tree we are checking is higher than the max scenic score we have at the moment,
            // and if it is, substitutes it by the scenic score of the tree we are checking

            if (scenic>maxScenic)
            {
                maxScenic = scenic;
            }

            // Resets the value of the variable scenic and distance

            scenic = 1;
            distance = 0;
        }
    }

    // Returns the highest scenic score from all the trees

    return maxScenic;
}

// Frees the memory alocated for a grid

void freeGrid (int **grid, int rows, int columns)
{
    // Frees the memory alocated for the columns of each row

    for (int i = 0;i<rows;i++)
    {
        free (grid[i]);
    }

    // Frees the memory alocated for every row

    free (grid);
}

int main ()
{
    // Inicializes two local variables that are going to store the number of rows and columns of the grid

    int rows = 0, columns = 0;

    // Opens the "input.txt" file

    FILE *fp = fopen ("input.txt", "r");

    // Discovers the number of rows and columns of the grid

    char *line = NULL;
    ssize_t read;
    size_t len;

    // Number of columns

    getline (&line,&len,fp);
    columns = strlen (line) - 1;

    // Number of rows

    while ((read = getline(&line,&len,fp)!=-1))
    {
        rows++;
    }
    rows++;

    // Creates and alocates space for the grid

    int **grid = malloc(rows * sizeof(int*));
    for (int i = 0;i<rows;i++)
    {
        grid[i] = (int*) malloc(columns * sizeof(int));
    }

    // Sets the file pointer back to the start of the file

    rewind (fp);

    // Fills the grid

    for (int i = 0;(read = getline(&line,&len,fp)!=-1);i++)
    {
        for (int j = 0;line[j]!='\n';j++)
        {
            grid [i][j] = line[j]-48;
        }
    }

    // Frees the memory alocated for the variable line

    free (line);

    // Findes the highest scenic score from all the trees

    int maxScenicScore = maxScenic (grid,rows,columns);

    // Prints the highest scenic score from all the trees

    printf ("%d\n", maxScenicScore);

    // Frees the memory alocated for the grid

    freeGrid (grid, rows, columns);

    return 0;
}