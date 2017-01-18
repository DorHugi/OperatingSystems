#ifndef _PAGE_TABLE
#define _PAGE_TABLE

#include "PageDirectoryEntry.h"


//CONSTS:
#define PAGE_DIRECTORY_ENTRIES 1024

class PageTable
{
	friend class VirtualMemory;
	
    public:
  
    PageTable();
    PageTableEntry& getPage(unsigned int adr, bool& dirEntryAllocated);
    


    //~PageTable(){};

    //int* GetPage (unsigned int adr);
    //int* GetAddress(unsigned int adr); 




    private:
    //Fill the class with the necessary member variables
    PageDirectoryEntry* directoryEntries[PAGE_DIRECTORY_ENTRIES];
};
#endif
