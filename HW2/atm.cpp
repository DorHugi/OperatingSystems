//This file contains the implementation of the ATM.


//I'll arrage the header later.
#include "atm.h"

using namespace std;

//Private functions

int readFileToVec(vector<string> &linesVec, string strFile);
vector<string> parseLine (string line);
    


void* createAtm(void* fileName){ //file name is actually char*

    string strFile((char*)(fileName));
    atm curAtm(strFile);

    vector<string> linesVec;
    readFileToVec(linesVec,strFile);
    //Now we have a new vecor of lines!
    
    //Now, iterate through lines of instructions, and perform each inst.    
    for (int i = 0; i< linesVec.size();i++){
        string line = linesVec[i];
        //Parse string: 
        
        vector<string> parsedLine = parseLine(line); //Now parsedLine contains the parsed line.
        //parseLine contains logic that checks thaat there are at least two arguements.
        
        string cmd = parsedLine[0];
        if (cmd == "O"){
            cout << "Line is: " << line << "command is: O " << endl;
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
