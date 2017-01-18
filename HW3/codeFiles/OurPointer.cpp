#include "OurPointer.h"

int& OurPointer::operator*(){
		*(_vrtlMem->GetPage(_adr));
}

OurPointer& OurPointer::operator++(){//Overload ++operator
		if(_adr>MAX_ADR-1){
			throw "invalid adrress";
		}
		_adr=_adr+1;
		return *this;
};

OurPointer OurPointer::operator++(int){
		if(_adr>MAX_ADR-1){
			throw "invalid adrress";
		}
		OurPointer ret(_adr,_vrtlMem);
		++(*this);
		return (ret);
	};
OurPointer& OurPointer::operator--(){
		if(_adr<1){
			throw "invalid adrress";
		}
		_adr=_adr-1;
		return *this;
};
OurPointer OurPointer::operator--(int){
		if(_adr<1){
			throw "invalid adrress";
		}
		OurPointer ret(_adr,_vrtlMem);
		--(*this);
		return (ret);
};	
