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

        dirContent->maxLengthOfInfo[INODE_LEN_IND] = strlen(fileInfo->inode);
        dirContent->maxLengthOfInfo[HARD_LINKS_LEN_IND] = strlen(fileInfo->hardLinks);
        dirContent->maxLengthOfInfo[OWNER_LEN_IND] = strlen(fileInfo->owner);
        dirContent->maxLengthOfInfo[GROUP_LEN_IND] = strlen(fileInfo->group);
        dirContent->maxLengthOfInfo[BYTE_SIZE_LEN_IND] = strlen(fileInfo->byteSize);

        fileInfo->next = NULL;

        return;
    }
    
    FileInfo* temp = dirContent->tail;
    temp->next = fileInfo;

    dirContent->tail = fileInfo;

    dirContent->size++;

    dirContent->maxLengthOfInfo[INODE_LEN_IND] = max(dirContent->maxLengthOfInfo[INODE_LEN_IND], strlen(fileInfo->inode));
    dirContent->maxLengthOfInfo[HARD_LINKS_LEN_IND] = max(dirContent->maxLengthOfInfo[HARD_LINKS_LEN_IND], strlen(fileInfo->hardLinks));
    dirContent->maxLengthOfInfo[OWNER_LEN_IND] = max(dirContent->maxLengthOfInfo[OWNER_LEN_IND], strlen(fileInfo->owner));
    dirContent->maxLengthOfInfo[GROUP_LEN_IND] = max(dirContent->maxLengthOfInfo[GROUP_LEN_IND], strlen(fileInfo->group));
    dirContent->maxLengthOfInfo[BYTE_SIZE_LEN_IND] = max(dirContent->maxLengthOfInfo[BYTE_SIZE_LEN_IND], strlen(fileInfo->byteSize));

    fileInfo->next=NULL;

    return;
}
