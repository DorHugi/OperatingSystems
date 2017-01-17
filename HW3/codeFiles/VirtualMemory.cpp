#include "VirtualMemory.h"

VirtualMemory::VirtualMemory(){

    if (elementsNum > 0){
        cerr << "Another instnace of VirtualMemory was tried to be created, even though it's a singletone." << endl;
        exit(1);
    }
    elementsNum++; 

};
