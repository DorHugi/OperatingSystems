#ifndef _PAGE_TABLE
#define _PAGE_TABLE

#include <PageDirectoryEntry.h>



//CONSTS:
#define PAGE_DIRECTORY_ENTRIES 1024

class PageTable
{
    public:

    //Your Constructor (and Destructor if you need one) should go here
	PageTable();
    int* GetPage (unsigned int adr); 


    private:
    //Fill the class with the necessary member variables
    PageDirecotryEntry* directoryEntries[PAGE_DIRECTORY_ENTRIES];
};
#endif
