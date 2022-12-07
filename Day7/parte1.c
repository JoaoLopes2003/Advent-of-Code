#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct file
{
    int fileSize;                               // Size of the respective file
    char *name;                                 // Name of the file
} File;

typedef struct dir
{
    char *name;                                 // Directory's name

    int spFiles;                                // Number of files in the directory
    int sizeAlocFiles;                          // Space alocated for the this directory's files
    struct file **files;                        // Directory's files

    struct dir *prevDir;                        // Directory that contains the directory we are checking
    int spDir;                                  // Number of directories in the directory
    int sizeAlocDir;                            // Space alocated for the this directory's directories
    struct dir **proxDir;                       // Directories this directory contains

    int size;                                  // Size of the directory
} Dir;



// Inicializes the outermost directory

Dir *initDir ()
{
    Dir *dir = malloc (sizeof(struct dir));

    // Creating array of files for this directory

    dir->spFiles = 0;
    dir->sizeAlocFiles = 4;
    dir->files = malloc (dir->sizeAlocFiles * sizeof(File*));

    // Creating array of directories for this directory

    dir->spDir = 0;
    dir->sizeAlocDir = 4;
    dir->proxDir = malloc(dir->sizeAlocDir * sizeof(Dir*));

    // Sets the size of the directory to NULL as it has no files yet

    dir->size = 0;

    // Sets the directory that contains this directory to NULL as it is the outermost directory

    dir->prevDir = NULL;

    // Stores the directory's name

    dir->name = malloc(2 * sizeof(char));
    dir->name = "/\n";

    return dir;
}

// Creates a new directory

Dir *newDir (Dir *aux, char *name)
{
    Dir *dir = malloc (sizeof(struct dir));

    // Creating array of files for this directory

    dir->spFiles = 0;
    dir->sizeAlocFiles = 4;
    dir->files = malloc (dir->sizeAlocFiles * sizeof(File*));

    // Creating array of directories for this directory

    dir->spDir = 0;
    dir->sizeAlocDir = 4;
    dir->proxDir = malloc(dir->sizeAlocDir * sizeof(Dir*));

    // Sets the size of the directory to NULL as it has no files yet

    dir->size = 0;

    // Sets the directory that contains this directory to NULL as it is the outermost directory

    dir->prevDir = aux;

    // Stores the directory's name

    dir->name = strdup (name);

    return dir;
}

// Creates a new file

File *newFile (int size, char *name)
{
    // Allocates space for a file

    File *file = malloc (sizeof(struct file));

    // Stores the size of the file and the name

    file->fileSize = size;
    file->name = strdup (name);

    return file;
}

// Inserts a file or directory in an already existent directory

void insertFileDir (Dir *dir, char *info, char *name)
{
    // Checks if its a directory or a file

    if (!strcmp(info,"dir"))
    {
        if (dir->spDir==dir->sizeAlocDir)
        {
            dir->sizeAlocDir *= 2;
            dir->proxDir = realloc (dir->proxDir, dir->sizeAlocDir * sizeof(Dir*));
        }

        // Creates the new directory

        dir->proxDir[dir->spDir] = newDir (dir, name);
        dir->spDir += 1;
    }
    else
    {
        if (dir->spFiles==dir->sizeAlocFiles)
        {
            dir->sizeAlocFiles *= 2;
            dir->files = realloc (dir->files, dir->sizeAlocFiles * sizeof(File*));
        }

        // Stores the size of the file in a local variable

        int size = atoi(info);

        // Creates the new file

        dir->files[dir->spFiles] = newFile (size, name);
        dir->spFiles += 1;
    }
}

// Stores the sizes of each directory

int sizeFillDir (Dir *dir)
{
    int size = 0;

    // Executes when theres no more directories inside of directories

    if (dir->spDir==0)
    {
        for (int i = 0;i<dir->spFiles;i++)
        {
            size += dir->files[i]->fileSize;
        }
        dir->size = size;
    }

    // Finds the innermost directories and from there sumes the sizes of each directory
    // inside a directory stopping when it calculates the size of the outermost directory 

    else
    {
        for (int i = 0;i<dir->spFiles;i++)
        {
            size += dir->files[i]->fileSize;
        }
        for (int j = 0;j<dir->spDir;j++)
        {
            size += sizeFillDir (dir->proxDir[j]);
        }
        dir->size = size;
    }

    return size;
}

// Claculates the sum of the sizes of the directories with at most size 100000

int sumSizes (Dir *dir)
{
    int sum = 0;

    // Adds the size of the respective directory if it has at most size 100000

    if (dir->size<=100000)
    {
    sum += dir->size;
    }

    // Goes through every directory

    for (int i = 0;i<dir->spDir;i++)
    {
        sum += sumSizes (dir->proxDir[i]);
    }

    return sum;
}

int main ()
{
    // Stores the file line

    char* line = NULL;
    ssize_t read;
    size_t len;

    // Opens the input file

    FILE *fp = fopen ("input.txt", "r");

    // Creates the outermost directory

    getline(&line,&len,fp);
    Dir *dir = initDir ();

    // Changes based on the directory we wanna check

    Dir *aux = dir;

    // Reads every line of the file and stores the directories and respective files

    while ((read = getline(&line,&len,fp)) !=- 1)
    {
        // Tokens to travel through one line

        char *token;

        token = strtok (line, " ");

        // Checks if its a command

        if (token[0]=='$')
        {
            // Checks whats the command being executed

            token = strtok (NULL, " ");

            if (!strcmp(token,"cd"))
            {
                // Checks the directory to change to

                token = strtok (NULL, " ");

                // Sets the directory back to the outermost directory if de command to be executed is "$ cd /"

                if (token[0]=='/')
                {
                    aux = dir;
                }

                // Moves the directory out one level if the command to be executed is "% cd .."

                else if (!strcmp(token,"..\n"))
                {
                    aux = aux->prevDir;
                }

                // Moves the directory in one level to the respective directory (x) if the command to be executed is "$ cd x"

                else
                {
                    for (int i = 0;i<aux->spDir;i++)
                    {
                        if (!strcmp(token,aux->proxDir[i]->name))
                        {
                            aux = aux->proxDir[i];
                            i = aux->prevDir->spDir;
                        }
                    }
                }
            }

            // Nothing happens if the command to be executed is "$ ls"

        }
        else
        {
            // Stores either the size of a file or the string "dir"

            char *info = token;

            // Stores the name of the file or directory

            char *name;
            token = strtok (NULL, " ");
            name = token;

            // Inserts a file or a directory in a directory

            insertFileDir (aux, info, name);
        }
    }

    // Stores the size of each directory

    aux = dir;
    sizeFillDir (aux);

    // Findes all the directories that have at most size 100000 and returns the sum of the sizes of those directories

    int size;
    size = sumSizes (aux);

    // Prints the result to the problem

    printf ("%d\n", size);

    return 0;
}