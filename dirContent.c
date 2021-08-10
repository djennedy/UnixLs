#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>

#include "fileInfo.h"
#include "dirContent.h"

static int max(int a, int b)
{
    return a>=b? a : b;
}

void addToDirContent(DirContent* dirContent, FileInfo* fileInfo)
{
    if (dirContent->size==0)
    {
        dirContent->head = fileInfo;
        dirContent->tail = fileInfo;

        dirContent->size++;

        dirContent->maxLengthOfInfo[INODE_LEN_IND] = fileInfo->inode!=NULL ? strlen(fileInfo->inode) : 0;
        dirContent->maxLengthOfInfo[HARD_LINKS_LEN_IND] = fileInfo->hardLinks!=NULL ? strlen(fileInfo->hardLinks) : 0;
        dirContent->maxLengthOfInfo[OWNER_LEN_IND] = fileInfo->owner!=NULL ? strlen(fileInfo->owner) : 0;
        dirContent->maxLengthOfInfo[GROUP_LEN_IND] = fileInfo->group!=NULL ? strlen(fileInfo->group) : 0;
        dirContent->maxLengthOfInfo[BYTE_SIZE_LEN_IND] = fileInfo->byteSize!=NULL ? strlen(fileInfo->byteSize) : 0;

        fileInfo->next = NULL;

        return;
    }
    
    FileInfo* temp = dirContent->tail;
    temp->next = fileInfo;

    dirContent->tail = fileInfo;

    dirContent->size++;

    if(fileInfo->inode!=NULL)
    {
        dirContent->maxLengthOfInfo[INODE_LEN_IND] = max(dirContent->maxLengthOfInfo[INODE_LEN_IND], strlen(fileInfo->inode));
    }
    if(fileInfo->hardLinks!=NULL)
    {
        dirContent->maxLengthOfInfo[HARD_LINKS_LEN_IND] = max(dirContent->maxLengthOfInfo[HARD_LINKS_LEN_IND], strlen(fileInfo->hardLinks));
    }
    if(fileInfo->owner!=NULL)
    {
        dirContent->maxLengthOfInfo[OWNER_LEN_IND] = max(dirContent->maxLengthOfInfo[OWNER_LEN_IND], strlen(fileInfo->owner));
    }
    if(fileInfo->group!=NULL)
    {
        dirContent->maxLengthOfInfo[GROUP_LEN_IND] = max(dirContent->maxLengthOfInfo[GROUP_LEN_IND], strlen(fileInfo->group));
    }
    if(fileInfo->byteSize!=NULL)
    {
        dirContent->maxLengthOfInfo[BYTE_SIZE_LEN_IND] = max(dirContent->maxLengthOfInfo[BYTE_SIZE_LEN_IND], strlen(fileInfo->byteSize));
    }

    fileInfo->next=NULL;

    return;
}
