#include "PageDirectoryEntry.h"



//int* PageTableEntry::GetPage (unsigned int adr){

    //int curTable = getTable(adr);  
     
    //if (!tableEntries[curTable].is_valid()){
       ////TODO: in future - support here swap in.    

        //tableEntries[curTable].set_valid(true);
        
        ////Alocate physical memory. 
        
          
          

    //}

//}



PageTableEntry& PageDirectoryEntry::getPage(unsigned int adr){

    int curPage = getTable(adr);  
    
    return tableEntries[curPage];

}






