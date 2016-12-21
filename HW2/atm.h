#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <pthread.h>
#include <unistd.h>
#include <vector>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <sstream>


class atm {

    public:
        atm(std::string file):inputFile(file) {} ; //c'tor

    private:
        std::string inputFile;

};

void* createAtm(void*); //This function creates and runs a new atm
                      // from void* (this is usefull for the pthread_create
                      // function.



