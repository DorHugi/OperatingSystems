//This file contains the implementation of the ATM.


//I'll arrage the header later.
#include "atm.h"
 
using namespace std;

//Private functions

int readFileToVec(vector<string> &linesVec, string strFile);
vector<string> parseLine (string line);
int strToInt(string str);    


void* createAtm(void* atmArgs){ //file name is actually char*


    char* fileName = ((char**)(atmArgs))[0];
    int atmNum = atoi((((char**)(atmArgs))[1]));

    cout << "filename is: " << fileName << " atm num is: " << atmNum
        << endl;
    string strFile(fileName);
    atm curAtm(strFile); vector<string> linesVec;
    readFileToVec(linesVec,strFile);
    //Now we have a new vecor of lines!
    
    //Now, iterate through lines of instructions, and perform each inst.    
    for (int i = 0; i< linesVec.size();i++){
        string line = linesVec[i];
        //Parse string: 
        
        vector<string> parsedLine = parseLine(line); //Now parsedLine 
        //contains the parsed line.
        //parseLine contains logic that checks thaat there are at 
        //least two arguements.
        
        string cmd = parsedLine[0];



        if (cmd == "O"){
            
            int accountNum = strToInt(parsedLine[1]);
            int pass = strToInt(parsedLine[2]);
            int initial = strToInt(parsedLine[3]);

            if (accountsData.createAccount(accountNum,
                        pass,initial)) //success
                cout << "Success" << endl;
            else
                cout << "Failed" << endl;


        }
        else if (cmd == "L"){ 
            cout << "else" << endl;
        }

        else if (cmd == "U"){ 
            cout << "else" << endl;
        }
        else if (cmd == "D"){ 
            cout << "else" << endl;
        }
        else if (cmd == "W"){ 
            cout << "else" << endl;
        }

        else if (cmd == "B"){ 
            cout << "else" << endl;
        }

        else if (cmd == "T"){ 
            cout << "else" << endl;
        }
        else {

        cout << "Unrecognized ATM command: " << cmd << " line is: " << line << endl;
        }



        }



    return NULL;

}



int readFileToVec(vector<string> &linesVec, string strFile){

    //Now read file line by line. 
    //First - check that file exists.
    
    if (access (strFile.c_str(),F_OK) != -1 ){ //c_str returns char*
       cout << "File " << strFile << " exists" << endl; 
    }
    else {
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

bool accounts::accountExists(int accountNum){  //Check if account exists.

    //readers writers:
    bool exist = false;
    pthread_mutex_lock(&readersLock);
    if (readersCount == 0)
        pthread_mutex_lock(&writersLock);
    readersCount++;
    pthread_mutex_unlock(&readersLock);
    
    //Do some reading. Check if accountNum exists already.
    
    for (int i=0; i < accountsVec.size(); i++) {
        if (accountsVec[i].number == accountNum){
            exist = true;
            break;
        }
        }
    //After reading - free mutexes.

    pthread_mutex_lock(&readersLock);
    if (readersCount == 1) //You're the last one!
        pthread_mutex_unlock(&writersLock);
    readersCount--;
    pthread_mutex_unlock(&readersLock);

    return exist;
} 




bool accounts::createAccount(int accountNum, int pass, int initialAmount){ //Returns true on success.

    if (this->accountExists(accountNum))
        return false; //Can't write, accounts exists already.
    
    //else - readers-writers.

    pthread_mutex_lock(&writersLock);
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


    //Exit critical part, release mutex.
    pthread_mutex_unlock(&writersLock);

}



int strToInt(string str){

    return atoi(str.c_str());

}










