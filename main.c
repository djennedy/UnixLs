#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "optionFlags.h"
#include "dirContent.h"
#include "fileInfo.h"
#include "printDirContent.h"

int main(int argc, char const *argv[])
{
    bool flags[NUM_OF_OPTIONS];
    
    // Where argv[pathIndex] contains the first reference to the path
    int pathIndex = 1;
    
    // Check for options
    if(argc > 1)
    {
        // Loop through argv
        for (pathIndex=1;pathIndex<argc;pathIndex++)
        {
            // Check if contains a flag
            if(argv[pathIndex][0] == '-')
            {
                int flagLength = strlen(argv[pathIndex]);

                for (int j=1;j<flagLength;j++)
                {
                    if (argv[pathIndex][j] == 'i')
                    {
                        flags[_i_FLAG] = true;
                    }
                    else if (argv[pathIndex][j] == 'l')
                    {
                        flags[_l_FLAG] = true;
                    }
                    else if (argv[pathIndex][j] == 'R')
                    {
                        flags[_R_FLAG] = true;
                    }
                    else
                    {
                        printf("ERROR: Unknown option: %c for ls\n", argv[pathIndex][j]);
                        return 0;
                    }
                }
            }
            // If no flag, break
            else
            {
                break;
            }
        }
    }

    int numPaths = argc - pathIndex;

    char* paths[numPaths==0? 1 : numPaths];

    // Checks if no path is given
    if(numPaths==0)
    {
        paths[0] = ".";
    }
    // If a path is given
    else 
    {
        // REMINDER: Remember that if we put more than 1 path argument, the path needs to be printed before listing (similar to -R)

        for(int i=pathIndex;i<argc;i++)
        {
            paths[i-pathIndex] = argv[i];
        }
    }

    // TODO: do the ls stuff here
    //  1. Get info
    //  2. Print

    // TODO: Finish this clause, add -R option in main

    getDateString(); // for testing purposes 
    
    return 0;
}