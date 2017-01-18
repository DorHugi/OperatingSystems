#include "SwapDevice.h"

using namespace std;


void SwapDevice::WriteFrameToSwapDevice(int pageNumber, int* pageOut) {
    if (_data[pageNumber] == NULL) {
        if (++_size > 1048576) {
            cerr << "The swap device seems to be using too much space worth investigating" << endl;
        }
        _data[pageNumber] = (int*)malloc(PAGESIZE);
    }
    memcpy(_data[pageNumber], pageOut, PAGESIZE);
}



int SwapDevice::ReadFrameFromSwapDevice(int pageNumber, int* pageIn) {
    if (_data[pageNumber] == NULL) {
        cerr << "DEBUG: You tried to access a page that doens't exists." << endl;
        exit(1);
        return -1;
        return -1;
    }
    memcpy(pageIn, _data[pageNumber], PAGESIZE);
    return 0;
}
