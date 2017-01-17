#include "VirtualMemory.h"

VirtualMemory::VirtualMemory(){
	
    

};
OurPointer VirtualMemory::OurMalloc(size_t size){ //allocates a pointer, we added the code for your convenience
        if (allocated + size >= (VIRTMEMSIZE >> 2)) {
            throw "We are limited to 4294967296 bytes with our 32 bit address size";
        }		
        OurPointer* ptr=new OurPointer(allocated, this);
	    allocated += size;
        return *ptr;
};
int* VirtualMemory::GetPage(unsigned int adr){
	return pageTable.GetPage(adr); 
}