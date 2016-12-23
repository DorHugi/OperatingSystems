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
#include <string.h>



//Global variables/mutexes.


//Classes

class atm {

    public:
        atm(std::string file):inputFile(file) {} ; //c'tor

    private:
        std::string inputFile;

};

void* createAtm(void*); //This function creates and runs a new atm
                      // from void* (this is usefull for the pthread_create
                      // function.


class account{

        
    public:
        account(int _balance,int _number,int _pass) :balance(_balance),
                number(_number),pass(_pass),isLocked(false) {}; //c'tor
         
        int balance;
        int number;
        int pass;
        bool isLocked;
};

class accounts{ //This is a singleton!

    public:
    //Methods:
    accounts():readersCount(0){
        //initialize mutexes:
        pthread_mutex_init(&readersLock,NULL);
        pthread_mutex_init(&writersLock,NULL);
            
    }; //c'tor

    bool accountExists(int accountNum);  //Check if account exists.
    bool createAccount(int accountNum, int pass,
            int initialAmount,int atmNum); //Returns true on success.


    //Variables:
    
    std::vector<account> accountsVec;  //This vector holds the account data.

    //readers writers mechanism:
    //This mecahnism is only for adding a new account,
    //or checking if accounts exists.

    int readersCount;
    pthread_mutex_t readersLock; 
    pthread_mutex_t writersLock;  



};

class logger{
    public:
        //variables:
        std::string name;//file name
        pthread_mutex_t writeLock; 


        //methods:
    
        logger(std::string _name):name(_name){ //c'tor
            
        //if (access (name.c_str(),F_OK) != -1 ){ //check that file exists.
            //std::cerr << "Error. Couldn't find logfile " << name 
                      //<< "exiting." << std::endl;
            //exit(-1);

        //}
        
        pthread_mutex_init(&writeLock,NULL); //init mutex.
        }

        void writeLog(std::string line); 
         

};






