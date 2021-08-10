#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "dirContent.h"
#include "printDirContent.h"
#include "fileInfo.h"
#include "optionFlags.h"
#include "getDirContent.h"
#include "cleanup.h"
#include "printRecursively.h"

void printRecursively(DirContent* dirContent, char* basePath, bool flags[])
{
    printDirContent(dirContent, flags);
    
    //Check for directories
    FileInfo* trav = dirContent->head;
    while(trav!=NULL)
    {
        // Allocates a string to store our path to pass to getDirContent later
        // The first +1 is to add / if the base path doesn't contain it
        // eg: if we have . , we want ./name not .name
        // The second +1 is for null terminator

        int finalPathLen = strlen(basePath) +1 + strlen(trav->name) + 1;
        char finalPath[finalPathLen];
        memset(finalPath, 0, finalPathLen);

        if(trav->isDir)
        {
            strcat(finalPath, basePath);
            if(finalPath[strlen(basePath)-1]!='/')
            {
                strcat(finalPath,"/");
            }
            strcat(finalPath, trav->name);

            DirContent* recursedDirContent = getDirContent(finalPath);

            printf("\n");
            printf("%s:\n",finalPath);
            printRecursively(recursedDirContent,finalPath, flags);
            cleanupDirContent(recursedDirContent);
        }

        trav=trav->next;
    }
}