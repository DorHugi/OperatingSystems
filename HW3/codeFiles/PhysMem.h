#include <stdlib.h>
#include <iostream>


using namespace std;

#define PHYSMEMSZ 262144

class PhysMem {

    friend class VirtualMemory;

    public:

        static PhysMem& Access();
        PhysMem(PhysMem const&) = delete;
        void operator=(PhysMem const&) = delete;
        int* GetFrame(int frameNumber);

    private:

        PhysMem() {}
        static int* physMem;
};
