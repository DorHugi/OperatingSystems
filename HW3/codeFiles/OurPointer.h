#include "PageTable.h"


class OurPointer {
	
    public:

    OurPointer(int adr, VirtualMemory*  vrtlMem); //Constructor
    ~OurPointer(); //Destructor
    int& operator*(); //Overload operator*
    OurPointer& operator++(); //Overload ++operator
    OurPointer operator++(int);
    OurPointer& operator--();
    OurPointer operator-- (int);

    private:
    unsigned int _adr; //the virtual address
    VirtualMemory* _vrtlMem; //for requesting translations
};
