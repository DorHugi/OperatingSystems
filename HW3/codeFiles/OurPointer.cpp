#include "OurPointer.h"


//int& OurPointer::operator*(){

		///[>(_vrtlMem->GetPage(_adr));
        
        ////get address from virtual memory:
        //int* physicalAddress = _vrtlMem->GetAdr(_adr); 
        //return *(physicalAddress);
//}

OurPointer& OurPointer::operator++(){//Overload ++operator
		if(_adr>MAX_ADR-4){
			throw "invalid adrress";
		}
		_adr=_adr+1;
		return *this;
};

OurPointer OurPointer::operator++(int){ //Overload operator++
		if(_adr>MAX_ADR-4){
			throw "invalid adrress";
		}
		OurPointer ret(_adr,_vrtlMem);
		++(*this);
		return (ret);
	};
OurPointer& OurPointer::operator--(){ //--operator
		if(_adr<4){
			throw "invalid adrress";
		}
		_adr=_adr-1;
		return *this;
};
OurPointer OurPointer::operator--(int){ //operator--
		if(_adr<4){
			throw "invalid adrress";
		}
		OurPointer ret(_adr,_vrtlMem);
		--(*this);
		return (ret);
};	
