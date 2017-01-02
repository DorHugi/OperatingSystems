#include "bank.h"
#define MAX_ARG_SIZE 5

using namespace std;


bankAccount bank;
//globals
accounts accountsData; //Create the only instance of accounts
logger logFile("log.txt");
bool commisionsRunning;
bool atmsRunning;


int main(int argc, char* argv[]){
    //Program arguements: bank <number of ATMs> <ATM1 input file> <ATM 2 > ..
    
    // get the number of atms:
    int atmNum = atoi(argv[1]);
    //create a thread for each ATM.
    pthread_t atmThreads[atmNum]; //Threads array.
    //For each atm - call a different thread.
    
	
    //char tempAtmNum[100];
	pthread_t commissions;
	pthread_t curBankStatus;
	atmArg argArray[atmNum];
	for (int i=0;i< atmNum;i++){
		int curAtm = i+1; //atm numbers starts from 1
        char* curFile = argv[i+2]; //first and second arguments in
                                          // argv aren't input files.
        argArray[i].num=curAtm;
		strcpy(argArray[i].file,curFile);
		//way to change from int to char* in C :( 
		
        //atmArgs[0] = curFile;
        //atmArgs[1] = tempAtmNum; 
		

        int err = pthread_create(&atmThreads[i],NULL,createAtm,
                                 (void*)(&argArray[i]));
		
       if (err){

		std::cerr << "ERROR: could not create thread for atm " 
                << curAtm << endl;
           exit(1);
       } 
    }//end of for.	
	atmsRunning=true;
	//	thread takeCommissions(commissions,NULL);
	int errCom=pthread_create(&commissions,NULL,takeCommissions,NULL);
	if (errCom){
		std::cerr << "ERROR: could not create thread for commissions " << endl;
           exit(1);
       }
	commisionsRunning=true;
	
	//	thread curBankStatus(commissions,NULL);
	int errStatus=pthread_create(&curBankStatus,NULL,printStatus,NULL);
	if (errStatus){
		std::cerr << "ERROR: could not create thread for printing the bank status " << endl;
           exit(1);
     }	
	//joining atm threads
    for (int i=0; i<atmNum;i++){
        pthread_join(atmThreads[i],NULL);
    }
	atmsRunning=false;
	pthread_join(commissions,NULL);
    commisionsRunning=false;
	pthread_join(curBankStatus,NULL);
    return 0;
}

void* printStatus(void*){
	string suffToPass;
	
	while(commisionsRunning){			
		usleep(0.5*(1000000));
		printf("\033[2J");
		printf("\033[1;1H");
		printf("Current Bank Status\n");
		for(unsigned int i=0; i < accountsData.accountsVec.size(); i++){
			accountsData.accountsVec[i].enterRead();
			
			if(accountsData.accountsVec[i].pass>999){
			suffToPass="";
			}else if(accountsData.accountsVec[i].pass>99){
			suffToPass="0";
			}else if(accountsData.accountsVec[i].pass>9){
			suffToPass="00";
			}else if(accountsData.accountsVec[i].pass>0){
			suffToPass="000";
			}else{
			suffToPass="0000";
			}
			cout <<"Account: "<<accountsData.accountsVec[i].number<<" Balance - "
			<< accountsData.accountsVec[i].balance<<" $"<<", Account Password - "<<suffToPass
			<<accountsData.accountsVec[i].pass<<endl;	
			accountsData.accountsVec[i].leaveRead();			
		}
		bank.enterRead();
		printf("The Bank has %d $\n",bank.money);
		bank.leaveRead();
	}
	pthread_exit(NULL);
    return NULL;		
}



void* takeCommissions(void*){
	double tmp;
	double ammount=0;
	double commissionRate; 
	stringstream log;
	while(atmsRunning){
		fflush(stdout);
		usleep(3000000);
		commissionRate=rand() % 100;
		commissionRate=(commissionRate/100)+3;
	    tmp=0;
		for(unsigned int i=0; i < accountsData.accountsVec.size(); i++){
			accountsData.accountsVec[i].enterRead();
			tmp=accountsData.accountsVec[i].balance;
			accountsData.accountsVec[i].leaveRead();
			accountsData.accountsVec[i].enterWrite();
			accountsData.accountsVec[i].balance=accountsData.accountsVec[i].balance*(1-(commissionRate/100));
			accountsData.accountsVec[i].leaveWrite();
			ammount=(tmp*(commissionRate/100));
			bank.enterWrite();
			bank.money=bank.money+ammount;
			bank.leaveWrite();
			
			log<<"Bank: commissions of "<<commissionRate<<" % were charged, the bank gained: "<<ammount<<
			"$ from account "<<	accountsData.accountsVec[i].number<<endl;
			logFile.writeLog(log.str());		
		}
	}		
	pthread_exit(NULL);
    return NULL;

}

void bankAccount::enterRead(){
    pthread_mutex_lock(&readersLock);
    if (readersCount == 0)
        pthread_mutex_lock(&writersLock);
    readersCount++;
    pthread_mutex_unlock(&readersLock);
}

void bankAccount::leaveRead(){
    pthread_mutex_lock(&readersLock);
    if (readersCount == 1) //You're the last one!
        pthread_mutex_unlock(&writersLock);
    readersCount--;
    pthread_mutex_unlock(&readersLock);
}

void bankAccount::enterWrite(){
    pthread_mutex_lock(&writersLock);
}

void bankAccount::leaveWrite(){
    pthread_mutex_unlock(&writersLock);
}

