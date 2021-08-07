#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>

#include "getDirContent.h"
#include "translateToString.h"
#include "fileInfo.h"
#include "dirContent.h"
#include "cleanup.h"

typedef struct dirent dirent;


// Returns NULL on error
DirContent* getDirContent(char* path)
{
    DIR* dirStream = opendir(path);
    char* filePath;
    struct stat statbuf;

    // TODO: free this and all other malloc/strdup uses, change all return null to shutdown first
    DirContent* dirContent = malloc(sizeof(DirContent));
    FileInfo* fileInfo;
    dirent* dirEntry;
    fileInfo->next = NULL;

    if(dirStream==NULL)
    {
        if(errno==ENOTDIR)
        {
            // If it's not a directory, check if it's a valid file name for stat
            filePath = path;

            if(stat(filePath, &statbuf)==0)
            {
                printf("UnixLs: Error in stat\n");
                cleanupDirContent(dirContent);
                dirContent = NULL;
                return NULL;
            }
            
            fileInfo->inode = getInodeString(statbuf.st_ino);
            fileInfo->permissions = getPermissionString(statbuf.st_mode);
            fileInfo->hardLinks = getHardLinksString(statbuf.st_nlink);
            fileInfo->owner = getOwnerString(statbuf.st_uid);
            fileInfo->group = getGroupString(statbuf.st_gid);
            fileInfo->date = getDateString(statbuf.st_mtim);

            addToDirContent(dirContent, fileInfo);

            return dirContent;

        }
        else if(errno==ENOENT)
        {
            printf("UnixLs: cannot access '%s': No such file or directory\n",path);
            cleanupDirContent(dirContent);
            dirContent = NULL;
            return NULL;
        }
        else
        {
            printf("UnixLs: opendir error\n");
            cleanupDirContent(dirContent);
            dirContent = NULL;
            return NULL;
        }
    }

    
    do
    {
        dirEntry = readdir(dirStream);
        char* fileName = dirEntry->d_name;

        // Skip hidden files
        if(fileName[0]=='.')
        {
            continue;
        }

        fileInfo = malloc(sizeof (FileInfo));
        fileInfo->name = strdup(fileName);

        char buf[strlen(path) + strlen(fileName)+1];
        strcat(buf, path);
        strcat(buf, fileName);
        filePath = buf;

        if(stat(filePath, &statbuf)==0)
        {
            printf("UnixLs: Error in stat\n");
            cleanupDirContent(dirContent);
            dirContent = NULL;
            return NULL;
        }


        // TODO: (later) seperate -i from -l
        fileInfo->inode = getInodeString(statbuf.st_ino);
        fileInfo->permissions = getPermissionString(statbuf.st_mode);
        fileInfo->hardLinks = getHardLinksString(statbuf.st_nlink);
        fileInfo->owner = getOwnerString(statbuf.st_uid);
        fileInfo->group = getGroupString(statbuf.st_gid);
        fileInfo->date = getDateString(statbuf.st_mtim);


        addToDirContent(dirContent, fileInfo);
        
    } while (dirEntry!=NULL);

    closedir(dirStream);
    return dirContent;
}