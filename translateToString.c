#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>

#include "translateToString.h"
#include "fileInfo.h"
#include "infodemo.c"
#include <pwd.h>


char* getInodeString(ino_t inode)
{
   
}

char* getPermissionString(mode_t mode)  // need to makee better
{

    char* convertedString;
    strmode(mode,convertedString); // converts mode into symbolic string 
                            // stored in location referenced by convertetdString

    printf("%11d", convertedString); // 11 spaces, right justified,
    
    return convertedString;
}

char* getHardLinksString(nlink_t nlink)
{
    //nlink similar to size bc is a number too
    intmax_t linkSize = (intmax_t) nlink; // casting it to "long" in everyones compuer
    char* stringSize = sprintf("%jd", linkSize); //prints  output in char

    return strdup(stringSize); //duplicates string to count # of bytes
}

char* getOwnerString(uid_t owner)
{
    /*
    //owner = numrical user ID
    char* ownerName = (char*)owner; 
    return strdup(ownerName);
    */

    // getAndPrintUserName(owner);
    return strdup( getAndPrintUserName(owner) ) ;

}

char* getGroupString(gid_t group)
{
    /*
    char* group = (char*)group; 
    return strdup(group);
    */

    //    getAndPrintGroup(group);
    return strdup( getAndPrintGroup(group) );
    
}

char* getByteSizeString(off_t size)
{
    intmax_t newSize = (intmax_t) size; // casting it to "long"
                // but intmax_t so its "long" in everyones compuer
    char* stringSize = sprintf("%jd", newSize); //instead of printing to console
                //stores output in char

    return strdup(stringSize); //duplicates string to count # of bytes, non-local
}

char* getDateString(struct timespec t)
{
   
}