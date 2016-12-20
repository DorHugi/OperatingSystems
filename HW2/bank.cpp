#include "atm.h"
using namespace std;

int main(int argc, char* argv[]){


    //Program arguements: bank <number of ATMs> <ATM1 input file> <ATM 2 > ..

    
    for (int i = 0; i < argc ; i++)
        printf("The value of arg %d is %s \n",i,argv[i]);

    // get the number of atms:
    int atmNum = atoi(argv[1]);

    //create a thread for each ATM.
    pthread_t atmThreads[atmNum];
    
    char* x = "hello"; 
    void* vx = (void*)(x);
    createAtm(vx);

return 0;
}
