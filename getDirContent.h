#ifndef _GET_DIR_CONTENT_H
#define _GET_DIR_CONTENT_H

// Defines the number of information fields we want to extract through our options
#define NUM_INFO_EXTRACTED 9

// Stores the index of the lengths of the information to print
// To be used with the max length of info array defined in dirContent
#define INODE_LEN_IND 0
#define HARD_LINKS_LEN_IND 1
#define OWNER_LEN_IND 2
#define GROUP_LEN_IND 3
#define BYTE_SIZE_LEN_IND 4

// Contains the file information in printable form and the link to the next FileInfo node
typedef struct FileInfo_s FileInfo;
struct FileInfo_s
{
    char* inode;
    char type;
    char permissions[10];
    char* hardLinks; 
    char* owner;
    char* group;
    char* byteSize;
    char date[17];
    char* name;

    FileInfo* next;
};

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

// Returns NULL on error
DirContent* getDirContent(char* path);

#endif