#include "PageTable.h"



//Implement functions:


PageTable::PageTable(){ //c'tor

	//initialize directoryEntries to NULL

	for(int i =0; i< PAGE_DIRECTORY_ENTRIES; i++)
		directoryEntries[i]= NULL;

}



//int* PageTable::GetPage (unsigned int adr){

    ////int original  = 0b00000001100000010100000000110100;  //For testing purposes.

    //unsigned int dir = getDir(adr);
    //if (!directoryEntries[dir]){
        //directoryEntries[dir] = new PageDirectoryEntry;
    //}

    

    //return directoryEntries[dir].getPage(adr);


//}


//int* PageTable::GetAddress(unsigned int adr){
    
    //int offset = getOffset(adr);     
    //int* page = this->GetPage(adr);
    //offset = offset / 4;


    //return page+offset;
//}



PageTableEntry& PageTable::getPage(unsigned int adr, bool& dirEntryAllocated){



    unsigned int curDir = getDir(adr);

    if (!directoryEntries[curDir]){
        directoryEntries[curDir] = new PageDirectoryEntry;
        dirEntryAllocated = true;
    }

    return directoryEntries[curDir]->getPage(adr);
     
}









