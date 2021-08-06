#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>

int main(int argc, char const *argv[])
{
    bool hasFlags = false;

    // It's better practice to change these to an array later on
    bool i_flag = false;
    bool l_flag = false;
    bool R_flag = false;

    // To check if we allocated memory in getcwd
    bool needFree = false;
    
    // Check for options
    if(argc > 1)
    {
        if(argv[1][0] == '-')
        {
            hasFlags = true;
            int flagLength = strlen(argv[1]);
            if(flagLength > 4 || flagLength ==1)
            {
                printf("ERROR: Bad options");
            }

            for (int i=1;i<flagLength;i++)
            {
                if (argv[1][i] == 'i')
                {
                    i_flag = true;
                }
                else if (argv[1][i] == 'l')
                {
                    l_flag = true;
                }
                else if (argv[1][i] == 'R')
                {
                    R_flag = true;
                }
                else
                {
                    printf("ERROR: Unknown option: %c for ls\n", argv[1][i]);
                    return 0;
                }
            }
        }
    }

    int numPaths=1;
    if (hasFlags)
    {
        numPaths = argc > 2? argc-2 : 1;
    }
    else
    {
        numPaths = argc > 1? argc-1 : 1;
    }

    char* paths[numPaths];

    // Checks if no path is given
    if(hasFlags && argc == 2 || !hasFlags && argc == 1)
    {
        // Note: We're trying to avoid using PATH_MAX using this method

        needFree = true;

        paths[0] = getcwd(NULL, 0);
        if(paths[0] == NULL)
        {
            printf("ERROR: getcwd failed\n");
            return 0;
        }
    }
    // If a path is given
    else 
    {
        // REMINDER: Remember that if we put more than 1 path argument, the path needs to be printed before listing (similar to -R)

        if (hasFlags)
        {
            for (int i=0;i<argc-2;i++)
            {
                paths[i] = argv[i+2];
            }
        }
        else
        {
            for (int i=0;i<argc-1;i++)
            {
                paths[i] = argv[i+1];
            }
        }
    }

    // TODO: do the ls stuff here
    

    if(needFree)
    {
        free(paths[0]);
    }
    return 0;
}


// TODO: Look into printing module