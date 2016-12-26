//This file contains the implementation of the ATM.


//I'll arrage the header later.
#include "atm.h"
#include <typeinfo>

#define NOT_FOUND -1
using namespace std;


//Globals:

extern logger logFile;
extern accounts accountsData;

//Private functions

int readFileToVec(vector<string> &linesVec, string strFile);
vector<string> parseLine (string line);
int strToInt(string str);    


void* createAtm(void* atmArgs){ //file name is actually char*

printf("debug print entered createAtm\n");
	
    char* fileName = ((char**)(atmArgs))[0];
    int atmNum = atoi((((char**)(atmArgs))[1]));
printf("debug print create atm before str\n");

    string strFile(fileName);
printf("debug print after weird string thing\n");

    atm curAtm(strFile); vector<string> linesVec;
    readFileToVec(linesVec,strFile);
    //Now we have a new vecor of lines!
    
    //Now, iterate through lines of instructions, 
    //and perform each inst.    
printf("debug print create atm before parser loop\n");

    for (int i = 0; i< linesVec.size();i++){
        string line = linesVec[i];
        //Parse string: 
	printf("debug print atm parser new line\n");
        
        vector<string> parsedLine = parseLine(line); //Now parsedLine 
        //contains the parsed line.
        //parseLine contains logic that checks thaat there are at 
        //least two arguements.
        
        string cmd = parsedLine[0];


        if (cmd == "O"){
            
            int accountNum = strToInt(parsedLine[1]);
            int pass = strToInt(parsedLine[2]);
            int initial = strToInt(parsedLine[3]);

            accountsData.createAccount(accountNum,pass,initial,atmNum); //success
			printf("debug print argument O\n");

        }
        else if (cmd == "L"){ 
            
            int accountNum = strToInt(parsedLine[1]);
            int pass = strToInt(parsedLine[2]);
            accountsData.lockAccount(accountNum,pass,atmNum);
			printf("debug print argument L\n");

        }


        else if (cmd == "U"){ 
            int accountNum = strToInt(parsedLine[1]);
            int pass = strToInt(parsedLine[2]);
            accountsData.unlockAccount(accountNum,pass,atmNum);
			printf("debug print argument U\n");

        }
        else if (cmd == "D"){ 
            int accountNum = strToInt(parsedLine[1]);
            int pass = strToInt(parsedLine[2]);
            int amount = strToInt(parsedLine[3]);
            accountsData.depositAccount(accountNum,pass,atmNum,amount);
			printf("debug print argument D\n");

        }
        else if (cmd == "W"){ 
            int accountNum = strToInt(parsedLine[1]);
            int pass = strToInt(parsedLine[2]);
            int amount = strToInt(parsedLine[3]);
            accountsData.withdrawAccount(accountNum,pass,atmNum,amount);
			printf("debug print argument W\n");

        }

        else if (cmd == "B"){ 
            int accountNum = strToInt(parsedLine[1]);
            int pass = strToInt(parsedLine[2]);
            accountsData.balanceAccount(accountNum,pass,atmNum);
			printf("debug print argument B\n");

        }

        else if (cmd == "T"){ 
            int from = strToInt(parsedLine[1]);
            int pass = strToInt(parsedLine[2]);
            int to = strToInt(parsedLine[3]);
            int amount = strToInt(parsedLine[4]);

            accountsData.transferFromTo(atmNum,from,to,pass,amount);
			printf("debug print argument T\n");

        }
        else {

        cout << "Unrecognized ATM command: " << cmd << " line is: " << line << endl;
        }
    }
    pthread_exit(NULL);
    return NULL;
}



int readFileToVec(vector<string> &linesVec, string strFile){

    //Now read file line by line. 
    //First - check that file exists.
    
    if (access (strFile.c_str(),F_OK) == -1 ){ //c_str returns char*
       cout << "File " << strFile << " doesn't exists" << endl; 
       exit(1);
    }

    ifstream ifs(strFile.c_str());
    string line;


    while (getline (ifs,line)){
        linesVec.push_back(line);
    }


    return 1;
}



vector<string> parseLine (string line){
      
    vector<string> splited;

    stringstream ss(line);
    string item;
    char delim =' ';

    while (getline(ss,item,delim))
        splited.push_back(item); //parse line.

    if (splited.size() < 2){
        cout << "parsing eror on line " << line << "exiting" << endl;
        exit(1);
    }


    return splited;    
}

//Class methods implementation:

int accounts::findAccount(int accountNum){  //Check if account exists.
    

    //Function assumes that it has read permissions. i.e - enterread was set before.
    

    for (int i=0; i < accountsVec.size(); i++) {
        if (accountsVec[i].number == accountNum){
            return(i); //return matching account
        }
    }


    return(NOT_FOUND);
} 

//Accounts data:

void accounts::enterRead(){
    pthread_mutex_lock(&readersLock);
    if (readersCount == 0)
        pthread_mutex_lock(&writersLock);
    readersCount++;
    pthread_mutex_unlock(&readersLock);
}

void accounts::leaveRead(){

    pthread_mutex_lock(&readersLock);
    if (readersCount == 1) //You're the last one!
        pthread_mutex_unlock(&writersLock);
    readersCount--;
    pthread_mutex_unlock(&readersLock);
}


void accounts::enterWrite(){

    pthread_mutex_lock(&writersLock);
}


void accounts::leaveWrite(){
    pthread_mutex_unlock(&writersLock);


}



bool accounts::createAccount(int accountNum, int pass, int initialAmount,int atmNum){ //Returns true on success.

    stringstream line;
    enterWrite();
    int accountIdx =findAccount(accountNum);
    if (accountIdx !=NOT_FOUND){ //wasn't found
        line << "Error " << atmNum << ": Your transcation failed - account with\
            the same id exists" << endl;
        logFile.writeLog(line.str());
        return false; //Can't write, accounts exists already.
    }

    //Critical part: Add new elem while keeping vec sorted.
    //Find matching place:  
    int i=0 ; //i is the place to insert.

    if (accountsVec.size() ==0)
        i = 0; //insert at the first place.
    else{
        while (i < accountsVec.size() && i < accountsVec[i].number)    
            i++;
    }

    //insert the place i 

    account temp(initialAmount,accountNum,pass);
    accountsVec.insert(accountsVec.begin()+ i,temp); 


    leaveWrite();//Exit critical part

    //Create log line string.
    line << atmNum << ": New account id is " << accountNum << " with password " <<
            pass << " and initial balance " << initialAmount << endl;
    logFile.writeLog(line.str());
    return true;

}



int strToInt(string str){

    return atoi(str.c_str());

}



void logger::writeLog(string line){

    ofstream fh;  //file handler

    pthread_mutex_lock(&writeLock);

    fh.open(name.c_str(),ios::app); //logger name
    fh << line;
    fh.close(); 
    
    pthread_mutex_unlock(&writeLock);
}


bool account::lock(int _pass){
       
    //since the password can't change, there is no need of doing read write
    //before checking it.
    
    
    if (_pass != pass){
        return false;
    } 

    //else:
    enterWrite();
    isLocked = true;
    leaveWrite();
    return true;
}

bool account::unlock(int _pass){
       
    //since the password can't change, there is no need of doing read write
    //before checking it.
    

    if (_pass != pass){
        return false;
    } 

    //else:
    enterWrite();
    isLocked = false;
    leaveWrite();
    return true;
}

void accounts::lockAccount (int accountNum, int pass,int atmNum){

    int accountIdx = findAccount(accountNum);  
    stringstream line;
    
    if (accountIdx == NOT_FOUND){
        cout << "ERR: you've asked me to lock account " 
             << accountNum << "but I can't find it" << endl;
        return;
    }
    
    //try to lock account.
    if (!accountsVec[accountIdx].lock(pass) ){ //wrong password.
        line << "ERROR: " << atmNum <<": Your transcation failed - password for account id" << accountNum << " is incorrect" << endl; 
        logFile.writeLog(line.str());

    }


}


void accounts::unlockAccount (int accountNum, int pass,int atmNum){

    int accountIdx = findAccount(accountNum);  
    stringstream line;
    
    if (accountIdx == NOT_FOUND){
        cout << "ERR: you've asked me to unlock account " 
             << accountNum << "but I can't find it" << endl;
        return;
    }
    
    //try to unlock account.

    if (!accountsVec[accountIdx].unlock(pass) ){ //wrong password.
        line << "ERROR: " << atmNum <<": Your transcation failed - password for account id" << accountNum << " is incorrect" << endl; 
        logFile.writeLog(line.str());

    }


}

bool account::deposit (int _pass,int amount,int atmNum){
    stringstream line;
    int tempBalance;
    if (_pass != pass || isAccountLocked() ){
            line << "ERROR: " << atmNum <<": Your transcation failed - password for account id " << number  << " is incorrect" << endl; 
            logFile.writeLog(line.str());
        return false;
    }
    
    enterWrite();
    balance+=amount;
    tempBalance = balance;
    leaveWrite();

    line << atmNum << ": Account " << number << " new balance is " << tempBalance << " after " << amount << " was deposited" << endl;
    logFile.writeLog(line.str());
    return true;

}


void accounts::depositAccount(int accountNum,int pass,int atmNum, int amount){

    
    int accountIdx = findAccount(accountNum);
    

    if (accountIdx == NOT_FOUND){
        cout << "ERR: you've asked me to unlock account " 
             << accountNum << "but I can't find it" << endl;
        return;
    }

    accountsVec[accountIdx].deposit(pass,amount,atmNum);

}

bool account::isAccountLocked(){
    enterRead();
    bool temp;
    temp = isLocked;
    leaveRead();
    return temp;
}
bool account::withdraw (int _pass,int amount,int atmNum){
    stringstream line;

    if (_pass != pass || isAccountLocked() ){
            line << "ERROR: " << atmNum <<": Your transcation failed - password for account id " << number  << " is incorrect" << endl; 
            logFile.writeLog(line.str());

        return false;
    }
    
    enterWrite();
    if (amount > balance){
            leaveWrite();
            line << "ERROR: " << atmNum <<": Your transcation failed - account id " << number  << " balance is lower than " << amount << endl; 
        logFile.writeLog(line.str());
    return false;
    }

    else{ //everything is ok.
        balance-=amount;
        int tempBalance = balance;
        leaveWrite();
        line << atmNum << ": Account " << number << " new balance is " << tempBalance << " after " << amount << " was withdrew" << endl;
        logFile.writeLog(line.str());
        return true;
    }

}


void accounts::withdrawAccount(int accountNum,int pass,int atmNum, int amount){

    
    int accountIdx = findAccount(accountNum);
    

    if (accountIdx == NOT_FOUND){
        cout << "ERR: you've asked me to unlock account " 
             << accountNum << "but I can't find it" << endl;
        return;
    }

    accountsVec[accountIdx].withdraw(pass,amount,atmNum);

}


void account::enterRead(){
    pthread_mutex_lock(&readersLock);
    if (readersCount == 0)
        pthread_mutex_lock(&writersLock);
    readersCount++;
    pthread_mutex_unlock(&readersLock);
}

void account::leaveRead(){

    pthread_mutex_lock(&readersLock);
    if (readersCount == 1) //You're the last one!
        pthread_mutex_unlock(&writersLock);
    readersCount--;
    pthread_mutex_unlock(&readersLock);
}


void account::enterWrite(){

    pthread_mutex_lock(&writersLock);
}


void account::leaveWrite(){
    pthread_mutex_unlock(&writersLock);


}



bool account::checkBalance(int _pass,int atmNum){
    
    stringstream line;

    if (_pass != pass ){
            line << "ERROR: " << atmNum <<": Your transcation failed - password for account id " << number  << " is incorrect" << endl; 
            logFile.writeLog(line.str());

        return false;
    }

    //else:
    enterRead();
    int tempBalance = balance;
    leaveRead();
    line << atmNum <<": Account " << number  << " balance is " 
        << tempBalance << endl; 
    logFile.writeLog(line.str());

return false;
    
}



void accounts::balanceAccount(int accountNum,int pass,int atmNum){

    
    int accountIdx = findAccount(accountNum);
    

    if (accountIdx == NOT_FOUND){
        cout << "ERR: you've asked me to check account balance " 
             << accountNum << "but I can't find it" << endl;
        return;
    }

    accountsVec[accountIdx].checkBalance(pass,atmNum);

}


void accounts::transferFromTo(int atmNum, int from, int to, int pass, int amount){
    //first- check input: both accounts are found, and password is correct.

    stringstream line; 
    int fromIdx = findAccount(from);
    int toIdx = findAccount(to);
    
    if (fromIdx == NOT_FOUND || toIdx == NOT_FOUND ){
        cout << "ERR: you've asked me to make a transfer but I can't find it" <<
            endl;
        return;
    }

    //now - check that password is correct.
    
    if (accountsVec[fromIdx].pass != pass){

            line << "ERROR: " << atmNum <<": Your transcation failed - password for account id " << from  << " is incorrect" << endl; 
            logFile.writeLog(line.str());
            return;

    }

    //about the enter critical part - lock in a sorted manner,
    //to prevent deadlock.   

    int min = fromIdx < toIdx? fromIdx :toIdx;
    int max = fromIdx < toIdx? toIdx : fromIdx;
   
    //assign by reference to make life a bit easier. 
    account &minAccount = accountsVec[min];
    account &maxAccount = accountsVec[max];
    account &fromAccount = accountsVec[fromIdx];
    account &toAccount = accountsVec[toIdx];
    
    //lock both accounts for writing.
    minAccount.enterWrite();
    maxAccount.enterWrite();
    //Critical part.
    if (amount > fromAccount.balance){ //not enough money in account.
   
        line << "ERROR: " << atmNum <<": Your transcation failed - " 
             << "account " << from << " balance is lower than " << amount << endl; 
    } 

    //IF I WANT TO CHECK THAT BOTH ACCOUNT ARENT LOCKED HERE IS THE PLACE

    else{ // there's enough money.
        fromAccount.balance-=amount;
        toAccount.balance+=amount;    

        line << atmNum << ": Transfer " << amount << " from account " << from
             << " to account " << to << " new account balance is " 
             << fromAccount.balance << " new target account balance is " 
             << toAccount.balance << endl;
    }

    //end of critical part.
    maxAccount.leaveWrite();
    minAccount.leaveWrite();
    
    //write line to log.

    logFile.writeLog(line.str());
    return;
}











