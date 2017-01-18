#ifndef _VIRTUAL_MEMORY
#define _VIRTUAL_MEMORY

#include <queue>
#include <cstring>


#include "OurPointer.h"
#include "PhysMem.h"
#include <unordered_set>
#include "PageTable.h"
#include "SwapDevice.h"


class OurPointer;
using namespace std;
class VirtualMemory{
    friend class PageTable;
   
    public:

    VirtualMemory(); //Initialize freeFramesList to contain all 64 frame pointers as given by PhysMem Class, initialize the PageTable, give the pageTable a pointer to this object so it can utilize GetFreeFrame and ReleaseFrame
    //~VirtualMemory(){};
    int* GetFreeFrame(); //Remove one item from the freeFrameList and return it – suggestion, use memset(framePtr, 0, PAGESIZE) before return, might help debugging!
    void ReleaseFrame(int* framePointer); //releases the frame pointed by the framePointer, make sure you only use this function with a pointer to the beginning of the Frame! it should be the same pointer as held in the PTE.
    OurPointer OurMalloc(size_t size);
    //int* GetPage(unsigned int adr);
    int* GetAdr(unsigned int adr); //Given an address, return a pointer to it (to the actual physical memory it points to). 

    

    private:
	size_t allocated; //The number of ints already allocated, ((allocated * 4) = (number of bytes already allocated)), this can also be used as the next address to be allocated.
    queue<int*> freeFramesList;
    queue<unsigned int> pageQueue;
    PageTable pageTable;
    SwapDevice swapDevice;

};

#endif
