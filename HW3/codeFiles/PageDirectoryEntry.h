#ifndef _PAGE_DIRECTORY_ENTRY
#define _PAGE_DIRECTORY_ENTRY
#include "PageTableEntry.h"
#include "AddressManipulation.h"

//CONSTS:
#define TABLE_ENTRIES 1024


class PageDirectoryEntry{
    public:
        
        //Methods:
        int* getPage(unsigned int adr);

        //Variables: 
        PageTableEntry tableEntries[TABLE_ENTRIES];
};
#endif
