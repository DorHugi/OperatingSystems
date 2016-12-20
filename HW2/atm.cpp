//This file contains the implementation of the ATM.


//I'll arrage the header later.
#include "atm.h"

using namespace std;

int createAtm(void* fileName){ //file name is actually char*

    string strFile(char*(fileName));
    atm curAtm(strFile);
    cout << "Yay! it's a new thread!. The file I need to read is " << strFile << endl;


}

