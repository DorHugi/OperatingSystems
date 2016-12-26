#ifndef BANK_H
#define BANK_H
#include "atm.h"
//#include <pthread.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <vector>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <sstream>
#include <string.h>
#include <sstream>



void* takeCommissions(void*);
void* printStatus(void*);

class bankAccount{
	public:
    int money;
	pthread_mutex_t readersLock; 
    pthread_mutex_t writersLock;  
    int readersCount;
    bankAccount(): money(0),readersCount(0){
		pthread_mutex_init(&readersLock,NULL);         
        pthread_mutex_init(&writersLock,NULL);
	};
    //readersWriters functions:
	
	void enterRead();
	void leaveRead();
	void enterWrite();
    void leaveWrite();			
};

#endif