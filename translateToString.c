#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
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
// #include "infodemo.c"



char* getInodeString(ino_t inode)
{
    //inode is unsigned char --> ju

   uintmax_t sizeInode = (uintmax_t)inode;
   char* inodeConvert; 
   if ( sprintf(inodeConvert,"%ju",sizeInode) < 0 ){

   }
    return strdup(inodeConvert);
   
}

char* getPermissionString(mode_t mode) 
{
    /*
    char* convertedString;
    strmode(mode,convertedString); // converts mode into symbolic string 
                            // stored in location referenced by convertetdString

    //should do an error check? <---- NOWWWWWWW <---------- <--
    
    return strdup(convertedString);
    */
   char* dum;
   return dum;
}

char* getHardLinksString(nlink_t nlink)
{
    //nlink similar to size bc is a number too
    intmax_t newLink = (intmax_t) nlink; // casting it to "long" in everyones compuer
    char* stringLink;
    if(sprintf(stringLink, "%jd", newLink)<0)
    {
        stringLink = "";
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
    char* byteSizeString;
    if(sprintf(byteSizeString,"%jd", newSize)<0)
    {
        byteSizeString = "";
    }

    return strdup(byteSizeString); //duplicates string to count # of bytes, non-local
}

char* getDateString(struct timespec t)
{

    //approach to usee 

    // gets the seconds from Jan 1 1970
    time_t seconds;
    seconds = time(NULL);
    // printf("time converted is: %ld\n", seconds);

    time_t     now;
    struct tm  ts;
    char       buf[80];

    // Get current time
    time(&now);

    ts = *localtime(&now);
    strftime(buf, sizeof(buf), "%m-%d %Y %H:%M:%S", &ts); // formatst the time 
                // as we specified and places in array (buf) of max size (80)
                //m=month 0-12, d=day 0 -31, Y=year as decimal, H=hour 00-23,
                // M=minute 00-59, S=second 00-60,   

    printf("%s\n", buf); // for testing purposes 
    
    return strdup(buf);

}
