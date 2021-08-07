#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <errno.h>

// #define INODE_LEN_IND 0
// #define HARD_LINKS_LEN_IND 1
// #define OWNER_LEN_IND 2
// #define GROUP_LEN_IND 3
// #define BYTE_SIZE_LEN_IND 4

#include "getDirContent.h"

static int max(int a, int b)
{
    return a>=b? a : b;
}

static void addToDirContent(DirContent* dirContent, FileInfo* fileInfo)
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

    return;
}

typedef struct dirent dirent;
// Returns NULL on error
DirContent* getDirContent(char* path)
{
    DIR* dirStream = opendir(path);
    char* filePath;
    if(dirStream==NULL)
    {
        if(errno==ENOTDIR)
        {
            // TODO: Check if file
        }
        else if(errno==ENOENT)
        {
            printf("UnixLs: cannot access '%s': No such file or directory\n",path);
            return NULL;
        }
        else
        {
            printf("UnixLs: opendir error\n");
            return NULL;
        }
    }

    // TODO: free this and all other malloc/strdup uses, change all return null to shutdown first
    DirContent* dirContent = malloc(sizeof(DirContent*));
    FileInfo* fileInfo;

    dirent* dirEntry;
    do
    {
        dirEntry = readdir(dirStream);
        char* fileName = dirEntry->d_name;

        // Skip hidden files
        if(fileName[0]=='.')
        {
            continue;
        }

        fileInfo = malloc(sizeof (FileInfo*));
        fileInfo->name = strdup(fileName);
        fileInfo->type = dirEntry->d_type;

        char buf[strlen(path) + strlen(fileName)+1];
        strcat(buf, path);
        strcat(buf, fileName);
        filePath = buf;

        struct stat statbuf;
        if(stat(filePath, &statbuf)==0)
        {
            printf("UnixLs: Error in stat\n");
            return NULL;
        }

        // TODO: fill in the fileInfo from information we know in statbuf


        addToDirContent(dirContent, fileInfo);
        
    } while (dirEntry!=NULL);

    closedir(dirStream);
    return dirContent;
}