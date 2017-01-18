#include "AddressManipulation.h"

unsigned int getDir(unsigned int adr){

    int dirMask = 0b11111111110000000000000000000000;
    int dir = (adr & dirMask)  >> 22;
    return dir;
}

unsigned int getTable(unsigned int adr){

    int tableMask = 0b00000000001111111111000000000000;
    int table = (adr & tableMask) >> 12;
    return table;
}

unsigned int getOffset(unsigned int adr){

    int offsetMask = 0b111111111111;
    int offset = (adr & offsetMask);
    return offset;
}
