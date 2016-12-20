#include "atm.h"
using namespace std;

int main(int argc, char* argv[]){


    //Program arguements: bank <number of ATMs> <ATM1 input file> <ATM 2 > ..

    
    for (int i = 0; i < argc ; i++) {
        printf("The value of arg %d is %s \n",i,argv[i]);
    }

    // get the number of atms:
    int atmNum = atoi(argv[1]);
    
    //create a thread for each ATM.
    pthread_t atmThreads[atmNum]; //Threads array.
    
    //For each atm - call a different thread.

    for (int i=0;i< atmNum;i++){
        int curAtm = i;
        char* curInputFile = argv[i+2]; //first and second arguments in
                                          // argv aren't input files.

        int err = pthread_create(&atmThreads[curAtm],NULL,createAtm,(void*)(curInputFile));

       if (err){

           cerr << "ERROR: could not create thread for atm " << curAtm << endl;
           exit(1);

       } 
    }     

    //end of for.



 
    for (int i=0; i<atmNum;i++){
        cout << "waiting for atmThread: " << i << endl;
        pthread_join(atmThreads[i],NULL);
    }
    

return 0;
}
