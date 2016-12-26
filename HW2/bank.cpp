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
printf("debug print 0\n");
    
    // get the number of atms:
    int atmNum = atoi(argv[1]);
	printf("debug print 1\n");
    //create a thread for each ATM.
    pthread_t atmThreads[atmNum]; //Threads array.
    printf("debug print 2\n");
    //For each atm - call a different thread.
    char* atmArgs[2];
    char tempAtmNum[100];
	pthread_t commissions;
	pthread_t curBankStatus;
	printf("debug print 3\n");
	for (int i=0;i< atmNum+1;i++){
        printf("debug print 5\n");

		int curAtm = i+1; //atm numbers starts from 1
        char* curFile = argv[i+2]; //first and second arguments in
                                          // argv aren't input files.
        sprintf(tempAtmNum,"%d",curAtm); //Apperantely this is the
        //way to change from int to char* in C :( 
        atmArgs[0] = curFile;
        atmArgs[1] = tempAtmNum; 

        int err = pthread_create(&atmThreads[i],NULL,createAtm,
                                 (void*)(atmArgs));
		printf("debug print 7\n");
		
       if (err){

		std::cerr << "ERROR: could not create thread for atm " 
                << curAtm << endl;
           exit(1);
       } 
    }//end of for.	
	atmsRunning=true;
	printf("debug print atmsRunning=true\n");
	//	thread takeCommissions(commissions,NULL);
	int errCom=pthread_create(&commissions,NULL,takeCommissions,NULL);
	if (errCom){
		std::cerr << "ERROR: could not create thread for commissions " << endl;
           exit(1);
       }
	commisionsRunning=true;
	printf("debug print commisionsRunning=true\n");
	
	//	thread curBankStatus(commissions,NULL);
	int errStatus=pthread_create(&curBankStatus,NULL,printStatus,NULL);
	if (errStatus){
		std::cerr << "ERROR: could not create thread for printing the bank status " << endl;
           exit(1);
     }	
	//joining atm threads
    for (int i=0; i<atmNum;i++){
        cout << "waiting for atmThread: " << i << endl;
        pthread_join(atmThreads[i],NULL);
    }
	atmsRunning=false;
	printf("debug print atmsRunning=false\n");
	
	pthread_join(commissions,NULL);
    commisionsRunning=false;
	printf("debug print commisionsRunning=false\n");
	
	pthread_join(curBankStatus,NULL);
    return 0;
}

void* printStatus(void*){
	while(commisionsRunning){			
		printf("debug print entered printStatus\n");
		usleep(0.5*(10^6));
		printf("debug print passed usleep in printStatus\n");
		//printf("\033[2J");
		printf("debug print passed clean screen print in printStatus\n");
		//printf("\033[1;1H");
		printf("debug print passed move left print in printStatus\n");
		printf("Current Bank Status\n");
		for(int i=0; i < accountsData.accountsVec.size(); i++){
			accountsData.accountsVec[i].enterRead();
			printf("Account %d: Balance - %d $ , Account Password - %d\n",accountsData.accountsVec[i].number,
			accountsData.accountsVec[i].balance, accountsData.accountsVec[i].pass);
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
	printf("debug print entered take commissions- befor string\n");
	stringstream log;
	while(atmsRunning){
		printf("debug print entered takeCommissions loop\n");
		fflush(stdout);
		usleep(3000000);
		printf("debug print passed usleep in takeCommissions\n");
		commissionRate=rand() % 100;
		commissionRate=(commissionRate/100)+3;
	    tmp=0;
		for(int i=0; i < accountsData.accountsVec.size(); i++){
			printf("debug print entered commissions for loop\n");
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
			printf("debug print commissions before log\n");
			
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

