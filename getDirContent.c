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
    // To take care of cases where an argument is passed without the directory path
    // Defaults to current directory
    char dirPath[strlen(path)+3];
    memset(dirPath, 0, strlen(path)+2);
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

    DIR* dirStream = opendir(dirPath);
    char* filePath;
    struct stat statbuf;

    DirContent* dirContent = malloc(sizeof(DirContent));
    dirContent->head=NULL;
    dirContent->tail=NULL;
    dirContent->size=0;
    dirent* dirEntry;

    if(dirStream==NULL)
    {
        if(errno==ENOTDIR)
        {
            // If it's not a directory, check if it's a valid file name for stat
            filePath = path;

            if(lstat(filePath, &statbuf)!=0)
            {
                printf("UnixLs: Error in stat\n");
                cleanupDirContent(dirContent);
                dirContent = NULL;
                return NULL;
            }
            FileInfo* fileInfo = malloc(sizeof(FileInfo));

            fileInfo->name = getNameString(path);
            fileInfo->inode = getInodeString(statbuf.st_ino);
            fileInfo->permissions = getPermissionString(statbuf.st_mode);
            fileInfo->hardLinks = getHardLinksString(statbuf.st_nlink);
            fileInfo->owner = getOwnerString(statbuf.st_uid);
            fileInfo->group = getGroupString(statbuf.st_gid);
            fileInfo->date = getDateString(statbuf.st_mtim); 
            fileInfo->byteSize = getByteSizeString(statbuf.st_size);

            // Check for symlinks
            if(S_ISLNK(statbuf.st_mode))
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

        FileInfo* fileInfo = malloc(sizeof(FileInfo));

        // Adding a / to the end of the file, since it's a directory
        // The first +1 is for \0, the second is so we can fit in a / in the end of the path before the file name if the path doesn't contain it
        // eg, if I give the argument . , we want ./filename not .filename
        char buf[strlen(path) + strlen(fileName)+1+1];
        memset(buf, 0,strlen(path) + strlen(fileName)+2);
        strcat(buf, path);
        if(buf[strlen(path)-1]!='/')
        {
            strcat(buf,"/");
        }
        strcat(buf, fileName);
        filePath = buf;

        if(lstat(filePath, &statbuf)!=0)
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
        fileInfo->byteSize = getByteSizeString(statbuf.st_size);
        fileInfo->name = getNameString(fileName);

        // Check for symlinks
        if(S_ISLNK(statbuf.st_mode))
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
        else
        {
            fileInfo->symLinkName = NULL;
        }


        addToDirContent(dirContent, fileInfo);
    }

    closedir(dirStream);
    return dirContent;
}