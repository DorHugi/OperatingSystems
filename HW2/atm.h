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
#define ERROR -2 


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
        
        //Variabels: 

        int balance;
        int number;
        int pass;
        bool isLocked;
        pthread_mutex_t readersLock; 
        pthread_mutex_t writersLock;  
        int readersCount;
        //Methods:
        account(int _balance,int _number,int _pass) :balance(_balance),
                number(_number),pass(_pass),isLocked(false),readersCount(0) {
            pthread_mutex_init(&readersLock,NULL);         
            pthread_mutex_init(&writersLock,NULL);         
                
        }; //c'tor
        
        
        //readersWriters functions:
        
        void enterRead();
        void leaveRead();
        void enterWrite();
        void leaveWrite();

        bool lock (int pass);
        bool unlock (int pass);
        bool deposit (int pass,int amount,int atmNum);
        bool withdraw (int pass,int amount,int atmNum);
        bool isAccountLocked();
        bool checkBalance(int pass,int atmNum);

        int getBalance();



};

class accounts{ //This is a singleton!

    public:
    //Methods:
    accounts():readersCount(0){
        //initialize mutexes:
        pthread_mutex_init(&readersLock,NULL);
        pthread_mutex_init(&writersLock,NULL);
            
    }; //c'tor

    int findAccount(int accountNum);  //Check if account exists.
    //This function assumes that you already set the read/write permissons.
    //if account was found it returns its index, and if not it returns NOT_FOUND
    bool createAccount(int accountNum, int pass,
    int initialAmount,int atmNum); //Returns true on success.
    //Readers writers functions
    void enterRead();
    void leaveRead();
    void enterWrite();
    void leaveWrite();
    void lockAccount (int accountNum, int pass,int atmNum);
    void unlockAccount (int accountNum, int pass,int atmNum);
    void depositAccount(int accountNum,int pass,int atmNum, int amount);
    void withdrawAccount(int accountNum,int pass,int atmNum, int amount);
    void balanceAccount(int accountNum,int pass,int atmNum);
    void transferFromTo(int atmNum, int from, int to,
            int pass, int amount);
    
      

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
            
            pthread_mutex_init(&writeLock,NULL); //init mutex.

            std::ofstream fh; 
            
            fh.open(name.c_str()); //Wipe the file.
            fh.close(); 


        }

        void writeLog(std::string line); 
         

};






