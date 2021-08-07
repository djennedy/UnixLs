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

char* getInodeString(ino_t inode)
{

}
char* getPermissionString(mode_t mode)
{

}
char* getHardLinksString(nlink_t nlink)
{

}
char* getOwnerString(uid_t owner)
{

}
char* getGroupString(gid_t group)
{

}
char* getByteSizeString(off_t size)
{
    intmax_t newSize = (intmax_t) size;
    char* stringSize = sprintf("%jd", newSize);

    return strdup(stringSize);
}
char* getDateString(struct timespec t)
{

}