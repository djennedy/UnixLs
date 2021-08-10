#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include <pwd.h>
#include <grp.h>
#include <time.h> 

#include "translateToString.h"
#include "fileInfo.h"

// Buf is always of size 11
static char* customStrMode(mode_t mode,char* buf)
{

    // First, we find the file type
    if(S_ISDIR(mode))
    {
        buf[0]='d';
    }
    else if(S_ISCHR(mode))
    {
        buf[0]='c';
    }
    else if(S_ISBLK(mode))
    {
        buf[0]='b';
    }
    else if(S_ISLNK(mode))
    {
        buf[0]='l';
    }
    else if(S_ISFIFO(mode))
    {
        buf[0]='p';
    }
    else
    {
        buf[0]='-';
    }

    // Setting up permissions for owner
    if((mode & S_IRUSR) == 0) //read
    {
        buf[1] = '-';
    }
    else
    {
        buf[1] = 'r';
    }
    
    if((mode & S_IWUSR) == 0) //write
    {
        buf[2] = '-';
    }
    else
    {
        buf[2] = 'w';
    }

    if((mode & S_IXUSR) == 0) //execute
    {
        buf[3] = '-';
    }
    else
    {
        buf[3] = 'x'; 
    }

    // Setting up permissions for group

    if((mode & S_IRGRP) == 0) //read
    {
        buf[4] = '-';
    }
    else
    {
        buf[4] = 'r';
    }

    if((mode & S_IWGRP) == 0) // write
    {
        buf[5] = '-';
    }
    else
    {
        buf[5] = 'w';
    }

    if((mode & S_IXGRP) == 0) // execute
    {
        buf[6] = '-';
    }
    else
    {
        buf[6] = 'x';
    }

    // Setting up permissions for others

    if((mode & S_IROTH) == 0) // read
    {
        buf[7] = '-';
    }
    else
    {
        buf[7] = 'r';
    }

    if((mode & S_IWOTH) == 0) // write
    {
        buf[8] = '-';
    }
    else
    {
        buf[8] = 'w';
    }

    if((mode & S_IXOTH) == 0) // execute
    {
        buf[9] = '-';
    }
    else
    {
        buf[9] = 'x'; 
    }

    buf[10]='\0';

    return buf;
}

char* getInodeString(ino_t inode)
{
    //inode is unsigned char --> ju

    uintmax_t sizeInode = (uintmax_t)inode;

    // Note: uintmax_t has a maximum of 20 digits in CSIL, but we're allocating more just to be safe
    char inodeConvert[64]; 
    if ( sprintf(inodeConvert,"%ju",sizeInode) < 0 ){
        inodeConvert[0] = '\0';
    }
    return strdup(inodeConvert);
   
}

char* getPermissionString(mode_t mode) 
{
    // commented out for testing purposes

    char convertedString[11];
    customStrMode(mode,convertedString); // converts mode into symbolic string 
                            // stored in location referenced by convertetdString
    
    return strdup(convertedString);

}

char* getHardLinksString(nlink_t nlink)
{
    //nlink similar to size bc is a number too
    uintmax_t newLink = (uintmax_t) nlink;

    // Note: uintmax_t has a maximum of 20 digits, but we're allocating more just to be safe
    char stringLink[64];
    if(sprintf(stringLink, "%jd", newLink)<0)
    {
        stringLink[0] = '\0';
    }

    return strdup(stringLink); //duplicates string to count # of bytes
}

char* getOwnerString(uid_t owner)
{
    struct passwd *pw = NULL;
    pw = getpwuid(owner);
    char* ownerString;

    if(pw==NULL)
    {
        ownerString = "";
    }
    else
    {
        ownerString = pw->pw_name;
    }

    return strdup(ownerString);
}

char* getGroupString(gid_t group)
{
    struct group *grp;
    grp = getgrgid(group);
    char* groupString;

    if(grp ==NULL)
    {
        groupString = "";
    }
    else
    {
        groupString = grp->gr_name;
    }
    
    return strdup(groupString);
}

char* getByteSizeString(off_t size)
{
    intmax_t newSize = (intmax_t) size; // casting it to "long"
                // but intmax_t so its "long" in everyones compuer

    // Note: intmax_t has a maximum of 20 digits, but we're allocating more just to be safe
    char byteSizeString[64];
    if(sprintf(byteSizeString,"%jd", newSize)<0)
    {
        byteSizeString[0] = '\0';
    }

    return strdup(byteSizeString); //duplicates string to count # of bytes, non-local
}

char* getDateString(struct timespec t)
{
    struct tm* curTime = localtime(&t.tv_sec);

    // We only need size 18 here (17 char + 1 null terminator), but we use 20 to be safe
    char stringDate[20];
    strftime(stringDate, 20, "%b %m %Y %H:%M",curTime);


    return strdup(stringDate);
}

char* getNameString (char* name)
{
    return strdup(name);
}

char* getSymLinkString(char* symLink)
{
    return strdup(symLink);
}

