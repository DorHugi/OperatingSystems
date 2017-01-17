#include "OurPointer.h"

int& OurPointer::operator*(){
		*(_vrtlMem->GetPage(_adr));
}

OurPointer& OurPointer::operator++(){//Overload ++operator
		if(_adr>MAX_ADR-1){
			throw "invalid adrress";
		}
		OurPointer ptr(_adr+1,_vrtlMem);
		return ptr;
};

OurPointer OurPointer::operator++(int){
		if(_adr>MAX_ADR-1){
			throw "invalid adrress";
		}
		OurPointer ret(_adr,_vrtlMem);
		operator++();
		return (*this);
	};
OurPointer& OurPointer::operator--(){
		if(_adr<1){
			throw "invalid adrress";
		}
		OurPointer ptr(_adr-1,_vrtlMem);
		return ptr;
};
OurPointer OurPointer::operator--(int){
		if(_adr<1){
			throw "invalid adrress";
		}
		OurPointer ret(_adr,_vrtlMem);
		operator++();
		return (*this);
};	