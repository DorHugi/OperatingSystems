#include "VirtualMemory.h"



#define FRAMES_NUM 64

VirtualMemory::VirtualMemory(){

    allocated = 0;

    for(int i = 0; i < FRAMES_NUM ; i++){

        freeFramesList.push(PhysMem::Access().GetFrame(i));
    }
    

}

OurPointer VirtualMemory::OurMalloc(size_t size){ //allocates a pointer, we added the code for your convenience
        if (allocated + size >= (VIRTMEMSIZE >> 2)) {
            throw "We are limited to 4294967296 bytes with our 32 bit address size";
        }		
        OurPointer* ptr=new OurPointer(allocated*4, this);
	    allocated += size;
        return *ptr;
}

//int* VirtualMemory::GetPage(unsigned int adr){

	//return pageTable.GetPage(adr); 
//}
//

int* VirtualMemory::GetAdr(unsigned int adr){ //Given an address, return a pointer to it (to the actual physical memory it points to). 

    //First - get the required page:
    
    PageTableEntry& curPage = pageTable.getPage(adr);

    if (! curPage.is_valid()){
    //Page is not valid - give it some memory!!

    curPage.set_page_address(GetFreeFrame());

    } 
    
    //Now - we know that the page is valid, and that its address is updated.
    int* curPageAddress = curPage.get_page_address();
    //Add the offset:


    int curOffset = getOffset(adr)/4;  //offset is divided by 4 becase increment of int* is by 4 anyway
    return curPageAddress+curOffset ;
}



int* VirtualMemory::GetFreeFrame(){ //Remove one item from the freeFrameList and return it – suggestion, use memset(framePtr, 0, PAGESIZE) before return, might help debugging!

    int* curAvailFrame = freeFramesList.front(); //get first element
    freeFramesList.pop(); //remove it from the queue
    
    //as the suggestion above implies - zero this frame completely to prevent mistakes!
    memset((void*)curAvailFrame,0,PAGE_SIZE);
    
    return curAvailFrame;


}



int& OurPointer::operator*(){

		//*(_vrtlMem->GetPage(_adr));
        
        //get address from virtual memory:
        int* physicalAddress = _vrtlMem->GetAdr(_adr); 
        return *(physicalAddress);
}





