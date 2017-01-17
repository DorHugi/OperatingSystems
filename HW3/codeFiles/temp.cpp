// Example program
#include <iostream>
#include <string>

int main()
{

    using namespace std;

    //Let us extract some bits.

    int original  = 0b00000001100000010100000000110100;

    int dirMask = 0b11111111110000000000000000000000;
    int tableMask = 0b00000000001111111111000000000000;
    int offsetMask = 0b111111111111;

    //Get actual data:

    int dir = (original & dirMask)  >> 22;
    int table = (original & tableMask) >> 12;
    int offset = (original & offsetMask);
    cout << "Dir is : " << dir << " table is: " << table << "offset is: " << offset <<  endl;

    cout << "HELLO" << endl;
}

