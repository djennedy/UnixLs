#ifndef _PRINT_DIR_CONTENT_H
#define _PRINT_DIR_CONTENT_H

#include "dirContent.h"

// Prints the content of the directory according to the flags set
//
// Indices for file information maximum character length:
// INODE_LEN_IND = 0
// HARD_LINKS_LEN_IND = 1
// OWNER_LEN_IND = 2
// GROUP_LEN_IND = 3
// BYTE_SIZE_LEN_IND = 4
//
// Flag options:
// _i_FLAG = 0
// _l_FLAG = 1
// _R_FLAG = 2
void printDirContent(DirContent* dirContent, bool flags[]);

// Prints the content of the directory recursively
void printRecursively(DirContent* dirContent, char* basePath, bool flags[]);

#endif