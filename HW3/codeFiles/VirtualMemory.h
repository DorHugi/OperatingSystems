#include <queue>
#include "OurPointer.h"
#include "PhysMem.h"
#include <unordered_set>
#include "PageTable.h"


#define PAGESIZE 4096
#define VIRTMEMSIZE 4294967296
#define NUMOFFRAMES 64

using namespace std;

class VirtualMemory {
    friend class PageTable;
    
   
    public:

    VirtualMemory(); //Initialize freeFramesList to contain all 64 frame pointers as given by PhysMem Class, initialize the PageTable, give the pageTable a pointer to this object so it can utilize GetFreeFrame and ReleaseFrame
    ~VirtualMemory();
    int* GetFreeFrame(); //Remove one item from the freeFrameList and return it – suggestion, use memset(framePtr, 0, PAGESIZE) before return, might help debugging!
    void ReleaseFrame(int* framePointer); //releases the frame pointed by the framePointer, make sure you only use this function with a pointer to the beginning of the Frame! it should be the same pointer as held in the PTE.
    OurPointer OurMalloc(size_t size) { //allocates a pointer, we added the code for your convenience
        if (allocated + size >= (VIRTMEMSIZE >> 2)) {
            throw "We are limited to 4294967296 bytes with our 32 bit address size";
            }

        OurPointer ptr(allocated, this);
        allocated += size;
        return ptr;
    }
    int* GetPage(unsigned int adr) { return pageTable.GetPage(adr); }

    private:

    static elementsNum = 0;  //Total number of VirtualMemory elements that were created so far. Needed to make sure it's a singletone.
    size_t allocated; //The number of ints already allocated, ((allocated * 4) = (number of bytes already allocated)), this can also be used as the next address to be allocated.
    queue<int*> freeFramesList;
    PageTable pageTable;
};


