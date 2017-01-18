#include "PageDirectoryEntry.h"


int* PageTableEntry::getPage (unsigned int adr){

    int entry = getTable(adr);  
    return tableEntries[entry].get_page_address()
}

