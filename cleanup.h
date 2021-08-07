#ifndef _CLEANUP_H
#define _CLEANUP_H

#include "dirContent.h"
#include "fileInfo.h"

// Frees every fileInfo in the dirContent linked list and sets it to null. Also frees the dirContent itself (doesn't set to null)
// Remember to set dirContent to null after this function is called
void cleanupDirContent(DirContent* dirContent);

// Frees every malloc-ed char in fileInfo and sets it to null, and also frees fileInfo itself (doesn't set to null)
// Remember to set fileIndo to null after this function is called
void cleanupFileInfo (FileInfo* fileInfo);

#endif