#include "VirtualMemory.h"
#include "PageTable.h"
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
        OurPointer* ptr=new OurPointer(allocated, this);
	    allocated += size;
        return *ptr;
}
