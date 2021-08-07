#ifndef _DIR_CONTENT_H
#define _DIR_CONTENT_H

#include "fileInfo.h"

// Defines the number of information fields we want to extract through our options
#define NUM_INFO_EXTRACTED 9

// Stores the index of the lengths of the information to print
// To be used with the max length of info array defined in dirContent
#define INODE_LEN_IND 0
#define HARD_LINKS_LEN_IND 1
#define OWNER_LEN_IND 2
#define GROUP_LEN_IND 3
#define BYTE_SIZE_LEN_IND 4

typedef struct DirContent_s DirContent;
struct DirContent_s
{
    // Contains a singly linked list of each file's information in printable form
    FileInfo* head;
    FileInfo* tail;

    // Number of files in the directory
    int size;

    // Stores the length of the characters of the information that we're trying to print
    // We need this for formatting purposes later on
    // We don't need to store the length of:
    // - File type (fixed at 1 char)
    // - 9 bit permissions (fixed at 9 chars)
    // - Dates (fixed at format mmm dd yyyy hh:mm -> 16 chars)
    // - File name (last thing to print, no need to be fixed)
    int maxLengthOfInfo[NUM_INFO_EXTRACTED-4];
};

// Adds a fileInfo node to the dirContent linked list
void addToDirContent(DirContent* dirContent, FileInfo* fileInfo);

#endif