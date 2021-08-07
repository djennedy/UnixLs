#ifndef _FILE_INFO_H
#define _FILE_INFO_H

// Contains the file information in printable form and the link to the next FileInfo node
typedef struct FileInfo_s FileInfo;
struct FileInfo_s
{
    char* inode;
    unsigned char type;
    char* permissions; //done?
    char* hardLinks; 
    char* owner;
    char* group;
    char* byteSize;
    char* date;
    char* name;

    // Next fileInfo in the dirContent linked list
    FileInfo* next;
};

#endif