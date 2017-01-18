#ifndef OUR_POINTER
#define OUR_POINTER

//#include "VirtualMemory.h"
#include "PageTable.h"


//#define PAGESIZE 4096 //Remove - it's defined at the page class (PageTableEntry);
#define VIRTMEMSIZE 4294967296
#define NUMOFFRAMES 64
#define MAX_ADR 2,147,483,647

using namespace std;

class VirtualMemory;



class OurPointer{
    friend class VirtualMemory;
	
	public:

    OurPointer(int adr, VirtualMemory* vrtlMem):_adr(adr),_vrtlMem(vrtlMem){}; //Constructor
	
	
    //~OurPointer(){}; //Destructor

    int& operator*();
    OurPointer& operator++(); 
    OurPointer operator++(int);
    OurPointer& operator--();
    OurPointer operator--(int);

	private:

    unsigned int _adr; //the virtual address
    VirtualMemory* _vrtlMem; //for requesting translations

};


#endif
