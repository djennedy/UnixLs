#ifndef _PRINT_RECURSIVELY_H
#define _PRINT_RECURSIVELY_H

#include "dirContent.h"

// Prints the content of the directory recursively
// Note, we're not using the flags parameter in any form, it exists to be passed to the printing method
void printRecursively(DirContent* dirContent, char* basePath, bool flags[]);

#endif