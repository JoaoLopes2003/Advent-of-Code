#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Counts all the inside trees that are visible from outside of the grid

int insideT (int **grid, int rows, int columns)
{
    // Creates an auxiliar grid that stores if a tree is visible or not

    int auxGrid [rows] [columns];

    // Sets every tree to 0 (not visible)

    for (int i = 0;i<rows;i++)
    {
        for (int j = 0;j<columns;j++)
        {
            auxGrid [i][j] = 0;
        }
    }

    // Stores the number of trees visible from outside of the grid

    int vTrees = 0;
    
    // Stores the max height in each column and sets it initially to the height of the first and last row trees of the grid

    int mHeightLeft, mHeightRight;

    // Stores the max height in each column, counting from the top and bottom

    int maxUp [columns], maxDown [columns];

    // Sets initially the arrays to the heights of the trees in the first row (maxUp) and last row (maxDown)

    for (int i = 1;i<columns-1;i++)
    {
        maxUp [i] = grid [0][i];
        maxDown [i] = grid [rows-1][i];
    }

    // Goes through every row

    for (int i = 1;i<rows-1;i++)
    {
        // Initializes to variables that represent the first inside tree counting
        // from the left (l) and the first inside tree counting from the right (r)

        int l = 1, r = columns-2;

        // While going through a row, stores the maximum height of a tree checked to that point, counting from the left

        mHeightLeft = grid [i][0];

        // While going through a row, stores the maximum height of a tree checked to that point, counting from the right

        mHeightRight = grid [i][columns-1];

        // Goes through a row from left to right

        for (;l<columns-1;l++)
        {
            // Stores the height of the tree we are checking

            int treeL = grid [i][l];

            // Checks if its heigher than the heighest tree when looking from the left of the grid or from the top of the grid

            if (treeL>mHeightLeft || treeL>maxUp[l])
            {
                // Updates the height of the heighst tree seen from the left if the tree we are checking is higher

                if (treeL>mHeightLeft)
                {
                    mHeightLeft = treeL;
                }

                // Updates the height of the heighst tree seen from the top if the tree we are checking is higher

                if (treeL>maxUp[l])
                {
                    maxUp[l] = treeL;
                }

                // Adds 1 to the trees that can be seen from the outside 

                vTrees++;

                // Sets the tree to 1 in the auxGrid to prevent counting this tree as visible again,
                // in case we can also see it from the right or bottom of the grid

                auxGrid [i][l] = 1;
            }
        }

        // Goes through a row from right to left

        for (;r>0;r--)
        {
            // Stores the height of the tree we are checking

            int treeR = grid [i][r];

            // Checks if its heigher than the heighest tree when looking from the right of the grid

            if (treeR>mHeightRight || treeR>maxUp[r])
            {
                // Updates the height of the heighst tree seen from the right if the tree we are checking is higher

                if (treeR>mHeightRight)
                {
                    mHeightRight = treeR;
                }

                // Checks if the tree was already counted as visible and if not adds 1 to the number of visible trees
                // and sets the tree in the auxGrid to 1 to prevent counting this tree as visible again, in case it is also visible from the bottom

                if (!auxGrid[i][r])
                {
                vTrees++;
                auxGrid [i][r] = 1;
                }
            }
        }
    }

    // Goes through every row and column from left to right and bottom to top,
    // counting the trees that are visible from the bottom, if not counted yet

    for (int i = rows-2;i>0;i--)
    {
        for (int j = 1;j<columns-1;j++)
        {
            // Stores the height of the tree we are checking

            int treeD = grid [i][j];

            // Checks if its heigher than the heighest tree when looking from the bottom of the grid

            if (treeD>maxDown[j])
            {
                // Updates the height of the heighst tree seen from the bottom

                maxDown[j] = treeD;

                // Checks if the tree was already counted as visible and if not adds 1 to the number of visible trees

                if (!auxGrid[i][j])
                {
                    vTrees++;
                    auxGrid [i][j] = 1;
                }
            }
        }
    }

    // Returns the number of inside trees visible from the outside

    return vTrees;
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

    // Counts the number of trees in the edge of the grid

    int vTrees = 2*rows + 2*(columns-2);

    // Sums all the inside trees that are visible from outside of the grid

    vTrees += insideT (grid, rows, columns);

    // Prints the numbers of trees that are visible from the outside

    printf ("%d\n", vTrees);

    // Frees the memory alocated for the grid

    freeGrid (grid, rows, columns);

    return 0;
}