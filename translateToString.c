#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "translateToString.h"
#include "fileInfo.h"
#include <pwd.h>


char* getInodeString(ino_t inode)
{
   
}

char* getPermissionString(mode_t mode)
{

    char* convertedString;
    strmode(mode,convertedString); // converts mode into symbolic string 
                            // stored in location referenced by convertetdString

    printf("%11d", convertedString); // 11 spaces, right justified,
    
    return convertedString;
}

char* getHardLinksString(nlink_t nlink)
{

    
    char* convertedLinkString;
    strmode(nlink, convertedLinkString);

    printf("%11d", convertedLinkString);
    return convertedLinkString;

}

char* getOwnerString(uid_t owner)
{
 
    //use functions from <pwd.h>  and <grp.h>  // st_uid
    // use filedemo if needed
}

char* getGroupString(gid_t group)
{

    //use functions from <pwd.h>  and <grp.h> // st_gid
    // use filedemo
    group = (gid_t)malloc(sizeof(gid_t)); 

    printf("%d", group);



    

}

char* getByteSizeString(off_t size)
{
    
}

char* getDateString(struct timespec time)
{
   
}