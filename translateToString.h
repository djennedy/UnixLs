#ifndef _TRANSLATE_TO_STRING_H
#define _TRANSLATE_TO_STRING_H

#include <sys/types.h>
#include <time.h>

char* getInodeString(ino_t inode);
char* getPermissionString(mode_t mode);
char* getHardLinksString(nlink_t nlink);
char* getOwnerString(uid_t owner);
char* getGroupString(gid_t group);
char* getByteSizeString(off_t size);
char* getDateString(struct timespec time);

#endif