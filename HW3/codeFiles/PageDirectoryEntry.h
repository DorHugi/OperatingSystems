#ifndef _PAGE_DIRECTORY_ENTRY
#define _PAGE_DIRECTORY_ENTRY
#include "PageTableEntry.h"
#include "AddressManipulation.h"

//CONSTS:
#define TABLE_ENTRIES 1024


class PageDirectoryEntry{
    public:
        
        
     

        //Methods:

        //int* GetPage(unsigned int adr);
        PageTableEntry& getPage(unsigned int adr); 

        


        //Variables: 
        //TODO: Make sure that this works, if not - it needs to be dynamically allocated (with c'tor, d'tor, and new operator).

        PageTableEntry tableEntries[TABLE_ENTRIES];
};
#endif
