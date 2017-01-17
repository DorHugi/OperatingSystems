#ifndef _PAGE_TABLE
#define _PAGE_TABLE

#include "PageDirectoryEntry.h"



//CONSTS:
#define PAGE_DIRECTORY_ENTRIES 1024

class PageTable
{
	friend class VirtualMemory;
	
    public:
  
    //Your Constructor (and Destructor if you need one) should go here
    int* GetPage (unsigned int adr){};
		PageTable(){};
		~PageTable(){};


    private:
    //Fill the class with the necessary member variables
    PageDirectoryEntry* directoryEntries[PAGE_DIRECTORY_ENTRIES];
};
#endif
