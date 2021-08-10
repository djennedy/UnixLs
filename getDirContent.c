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
#include "optionFlags.h"

typedef struct dirent dirent;

static void fillSymLinkName (FileInfo* fileInfo, char* filePath)
{
    char symLinkbuf[257];
    int symLinkLen = readlink(filePath,symLinkbuf, 256);
    if(symLinkLen==-1)
    {
        printf("UnixLs: Error with symlinks\n");
        fileInfo->symLinkName = NULL;
    }
    else
    {
        symLinkbuf[symLinkLen]='\0';
        fileInfo->symLinkName  = getSymLinkString(symLinkbuf);
    }
}

static void fillInfoFromStat (FileInfo* fileInfo, char* filePath,struct stat statbuf)
{
    fileInfo->permissions = getPermissionString(statbuf.st_mode);
    fileInfo->hardLinks = getHardLinksString(statbuf.st_nlink);
    fileInfo->owner = getOwnerString(statbuf.st_uid);
    fileInfo->group = getGroupString(statbuf.st_gid);
    fileInfo->date = getDateString(statbuf.st_mtim);
    fileInfo->byteSize = getByteSizeString(statbuf.st_size);

}

// Returns NULL on error
DirContent* getDirContent(char* path,bool flags[])
{
    // To take care of cases where an argument is passed without the directory path
    // Defaults to current directory
    int dirPathLen = strlen(path)+3;
    char dirPath[dirPathLen];
    memset(dirPath, 0, dirPathLen);
    if(strstr(path,"/")==NULL)
    {
        dirPath[0]='.';
        dirPath[1]='/';
        dirPath[2]='\0';
        strcat(dirPath,path);
    }
    else
    {
        strcpy(dirPath, path);
    }

    // First, we open  the directory
    DIR* dirStream = opendir(dirPath);
    char* filePath;
    struct stat statbuf;

    // Create a new dirContent to store the contents of our directory
    DirContent* dirContent = malloc(sizeof(DirContent));
    dirContent->head=NULL;
    dirContent->tail=NULL;
    dirContent->size=0;
    dirent* dirEntry;

    // Error checking dirStream
    if(dirStream==NULL)
    {
        if(errno==ENOTDIR)
        {
            // If it's not a directory, check if it's a valid file name for stat
            filePath = path;

            // Creating a FileInfo object to store our file information
            FileInfo* fileInfo = malloc(sizeof(FileInfo));
            fileInfo->name  = getNameString(path);
            fileInfo->isDir = false; // caught by ENOTDIR, so not directory

            if(lstat(filePath, &statbuf)!=0)
            {
                printf("UnixLs: Error in stat\n");
                cleanupDirContent(dirContent);
                dirContent = NULL;
                return NULL;
            }

            if(flags[_i_FLAG])
            {
                fileInfo->inode = getInodeString(statbuf.st_ino);
            }
            
            if(flags[_l_FLAG])
            {
                fillInfoFromStat(fileInfo, filePath, statbuf);
            }

            // Check for symlinks
            if(S_ISLNK(statbuf.st_mode))
            {
                fillSymLinkName(fileInfo, filePath);
            }
            else
            {
                fileInfo->symLinkName = NULL;
            }

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

    // Looping through  the directory stream
    while(true)
    {
        dirEntry = readdir(dirStream);
        if(dirEntry == NULL)
        {
            break;
        }
        char* fileName = dirEntry->d_name;

        // Skip hidden files
        if(fileName[0]=='.')
        {
            continue;
        }

        // Adding a / to the end of the file, since it's a directory
        // The first +1 is so we can fit in a / in the end of the path before the file name if the path doesn't contain it
        // eg, if I give the argument . , we want ./filename not .filename
        // The second +1 is for the null terminator
        int bufLen = strlen(path) +1 + strlen(fileName) +1;
        char buf[bufLen];
        memset(buf, 0,bufLen);
        strcat(buf, path);
        if(buf[strlen(path)-1]!='/')
        {
            strcat(buf,"/");
        }
        strcat(buf, fileName);
        filePath = buf;

        // Creating a FileInfo object to store our file information
        FileInfo* fileInfo = malloc(sizeof(FileInfo));
        memset(fileInfo, 0, sizeof(FileInfo));
        fileInfo->name = getNameString(fileName);
        fileInfo->isDir=true; // must be true since not caught by ENOTDIR error

        if(flags[_i_FLAG])
        {
            fileInfo->inode= getInodeString(dirEntry->d_ino);
        }

        // Check for symlinks
        if(dirEntry->d_type==DT_LNK)
        {
            fillSymLinkName(fileInfo, filePath);
        }
        else
        {
            fileInfo->symLinkName=NULL;
        }

        if(flags[_l_FLAG])
        {
            if(lstat(filePath, &statbuf)!=0)
            {
                printf("UnixLs: Error in stat\n");
                cleanupDirContent(dirContent);
                dirContent = NULL;
                return NULL;
            }
            fillInfoFromStat(fileInfo, filePath, statbuf);
        }

        addToDirContent(dirContent, fileInfo);
    }

    closedir(dirStream);
    return dirContent;
}