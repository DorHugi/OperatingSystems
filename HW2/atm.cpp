//This file contains the implementation of the ATM.


//I'll arrage the header later.
#include "atm.h"

using namespace std;


int readFileToVec(vector<string> &linesVec, string strFile);



void* createAtm(void* fileName){ //file name is actually char*

    string strFile((char*)(fileName));
    atm curAtm(strFile);
    cout << "Yay! it's a new thread!. The file I need to read is " << strFile << endl;

    vector<string> linesVec;
    readFileToVec(linesVec,strFile);
    //Now we have a new vecor of lines!


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
