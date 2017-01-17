#ifndef OUR_POINTER
#define OUR_POINTER

#include "VirtualMemory.h"
#include "PageTable.h"


#define PAGESIZE 4096
#define VIRTMEMSIZE 4294967296
#define NUMOFFRAMES 64
using namespace std;

class VirtualMemory;

class OurPointer{
    friend class VirtualMemory;
	
	public:

    OurPointer(int adr, VirtualMemory* vrtlMem){
		_adr=adr;
		_vrtlMem=vrtlMem;
	}; //Constructor
	
	
    ~OurPointer(){}; //Destructor
    int& operator*();
    OurPointer& operator++(){//Overload ++operator
		OurPointer ptr(_adr+4,_vrtlMem);
		return ptr;
	}; 
    OurPointer operator++(int){
		OurPointer ret(_adr,_vrtlMem);
		operator++();
		return (*this);
	};
    OurPointer& operator--(){};
    OurPointer operator--(int){};
	private:

    unsigned int _adr; //the virtual address
    VirtualMemory* _vrtlMem; //for requesting translations

};


#endif