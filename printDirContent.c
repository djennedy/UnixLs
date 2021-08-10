#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "dirContent.h"
#include "printDirContent.h"
#include "fileInfo.h"
#include "optionFlags.h"


void printDirContent(DirContent* dirContent, bool flags[])
{
    FileInfo* trav = dirContent->head;

    // If no options
    if(!flags[_i_FLAG] && !flags[_l_FLAG])
    {
        while(trav!=NULL)
        {
            printf("%s \n", trav->name);
            trav = trav->next;
        }
    }
    // If i option only
    else if(flags[_i_FLAG] && !flags[_l_FLAG])
    {
        while(trav!=NULL)
        {
            int offsetInode = dirContent->maxLengthOfInfo[INODE_LEN_IND] - strlen(trav->inode);
            char whiteSpaceInode [offsetInode+1];
            memset(whiteSpaceInode, ' ', offsetInode);
            whiteSpaceInode[offsetInode] = '\0';

            printf("%s%s %s\n", whiteSpaceInode,trav->inode,trav->name);

            trav = trav->next;
        }
    }
    // If l option only
    else if(!flags[_i_FLAG] && flags[_l_FLAG])
    {
        while(trav!=NULL)
        {
            int offsetHardLinks = dirContent->maxLengthOfInfo[HARD_LINKS_LEN_IND] - strlen(trav->hardLinks);
            char whiteSpaceHardLinks [offsetHardLinks+1];
            memset(whiteSpaceHardLinks, ' ', offsetHardLinks);
            whiteSpaceHardLinks[offsetHardLinks] = '\0';

            int offsetOwner = dirContent->maxLengthOfInfo[OWNER_LEN_IND] - strlen(trav->owner);
            char whiteSpaceOwner [offsetOwner+1];
            memset(whiteSpaceOwner, ' ', offsetOwner);
            whiteSpaceOwner[offsetOwner] = '\0';

            int offsetGroup = dirContent->maxLengthOfInfo[GROUP_LEN_IND] - strlen(trav->group);
            char whiteSpaceGroup [offsetGroup+1];
            memset(whiteSpaceGroup, ' ', offsetGroup);
            whiteSpaceGroup[offsetGroup] = '\0';

            int offsetByteSize = dirContent->maxLengthOfInfo[BYTE_SIZE_LEN_IND] - strlen(trav->byteSize);
            char whiteSpaceByteSize [offsetByteSize+1];
            memset(whiteSpaceByteSize, ' ', offsetByteSize);
            whiteSpaceByteSize[offsetByteSize] = '\0';

            printf("%s %s%s %s%s %s%s %s%s %s %s",
                trav->permissions,
                whiteSpaceHardLinks, trav->hardLinks,
                trav->owner, whiteSpaceOwner,
                trav->group, whiteSpaceGroup, 
                whiteSpaceByteSize, trav->byteSize,
                trav->date,
                trav->name);

            if(trav->symLinkName!=NULL)
            {
                printf(" -> %s\n",trav->symLinkName);
            }
            else
            {
                printf("\n");
            }

            trav = trav->next;
        }
    }
    // If both options
    else
    {
        while (trav!=NULL)
        {
            int offsetInode = dirContent->maxLengthOfInfo[INODE_LEN_IND] - strlen(trav->inode);
            char whiteSpaceInode [offsetInode+1];
            memset(whiteSpaceInode, ' ', offsetInode);
            whiteSpaceInode[offsetInode] = '\0';

            int offsetHardLinks = dirContent->maxLengthOfInfo[HARD_LINKS_LEN_IND] - strlen(trav->hardLinks);
            char whiteSpaceHardLinks [offsetHardLinks+1];
            memset(whiteSpaceHardLinks, ' ', offsetHardLinks);
            whiteSpaceHardLinks[offsetHardLinks] = '\0';

            int offsetOwner = dirContent->maxLengthOfInfo[OWNER_LEN_IND] - strlen(trav->owner);
            char whiteSpaceOwner [offsetOwner+1];
            memset(whiteSpaceOwner, ' ', offsetOwner);
            whiteSpaceOwner[offsetOwner] = '\0';

            int offsetGroup = dirContent->maxLengthOfInfo[GROUP_LEN_IND] - strlen(trav->group);
            char whiteSpaceGroup [offsetGroup+1];
            memset(whiteSpaceGroup, ' ', offsetGroup);
            whiteSpaceGroup[offsetGroup] = '\0';

            int offsetByteSize = dirContent->maxLengthOfInfo[BYTE_SIZE_LEN_IND] - strlen(trav->byteSize);
            char whiteSpaceByteSize [offsetByteSize+1];
            memset(whiteSpaceByteSize, ' ', offsetByteSize);
            whiteSpaceByteSize[offsetByteSize] = '\0';

            printf("%s%s %s %s%s %s%s %s%s %s%s %s %s",
                whiteSpaceInode, trav->inode, 
                trav->permissions,
                whiteSpaceHardLinks, trav->hardLinks,
                trav->owner, whiteSpaceOwner,
                trav->group, whiteSpaceGroup, 
                whiteSpaceByteSize, trav->byteSize,
                trav->date,
                trav->name);

            if(trav->symLinkName!=NULL)
            {
                printf(" -> %s\n",trav->symLinkName);
            }
            else
            {
                printf("\n");
            }

            trav = trav->next;
        }
    }
    
}