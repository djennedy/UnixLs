#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include <pwd.h>
// #include <bsd/string.h>
#include <grp.h>
#include <time.h> 

#include "translateToString.h"
#include "fileInfo.h"

// Buf is always of size 11
static char* customStrMode(mode_t mode,char* buf)
{
// use the printf from stack overflow
// concatinate printf to a buf instead
// put mode into bug?

 
    char buf[15]; //always 11 but to be safe we use 15
    strdup(buf, (S_ISDIR(fileStat.st_mode)) ? "d" : "-" ) ); 
    strcat(buf, (fileStat.st_mode & S_IRUSR) ? "r" : "-"  ); 
    // strcat(buf, (fileStat.st_mode & S_IWUSR) ? "w" : "-"  );
    // strcat(buf, (fileStat.st_mode & S_IXUSR) ? "x" : "-"  );
    // strcat(buf, (fileStat.st_mode & S_IRGRP) ? "r" : "-"  );
    // strcat(buf, (fileStat.st_mode & S_IWGRP) ? "w" : "-"  );
    // strcat(buf, (fileStat.st_mode & S_IXGRP) ? "x" : "-"  ); 
    // strcat(buf, (fileStat.st_mode & S_IROTH) ? "r" : "-"  );
    // strcat(buf, (fileStat.st_mode & S_IWOTH) ? "w" : "-"  );
    // strcat(buf, (fileStat.st_mode & S_IXOTH) ? "x" : "-"  );


    // printf( (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
    // printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-"  );
    // printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-"  );
    // printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-"  );
    // printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-"  );
    // printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-"  );
    // printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-"  );
    // printf( (fileStat.st_mode & S_IROTH) ? "r" : "-"  );
    // printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-"  );
    // printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-"  );

    return buf;
}

char* getInodeString(ino_t inode)
{
    //inode is unsigned char --> ju

    uintmax_t sizeInode = (uintmax_t)inode;

    // Note: uintmax_t has a maximum of 20 digits, but we're allocating more just to be safe
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
    strmode(mode,convertedString); // converts mode into symbolic string 
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

