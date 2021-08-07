#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "cleanup.h"
#include "dirContent.h"
#include "fileInfo.h"

void cleanupDirContent(DirContent* dirContent)
{
    if(dirContent == NULL)
    {
        return;
    }

    FileInfo* trav = dirContent->head;
    while (trav!=NULL)
    {
        FileInfo* cur = trav;
        trav = trav->next;
        cleanupFileInfo(cur);
        cur = NULL;
    }
    
    free(dirContent);
}

void cleanupFileInfo (FileInfo* fileInfo)
{
    if(fileInfo == NULL)
    {
        return;
    }
    
    free(fileInfo->inode);
    fileInfo->inode = NULL;
    free(fileInfo->permissions);
    fileInfo->permissions = NULL;
    free(fileInfo->hardLinks);
    fileInfo->hardLinks = NULL;
    free(fileInfo->owner);
    fileInfo->owner = NULL;
    free(fileInfo->group);
    fileInfo->group = NULL;
    free(fileInfo->byteSize);
    fileInfo->byteSize = NULL;
    free(fileInfo->date);
    fileInfo->date = NULL;
    free(fileInfo->name);
    fileInfo->name = NULL;

    free(fileInfo);
}