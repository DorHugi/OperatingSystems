#include "OurPointer.h"

int& OurPointer::operator*(){
		*(_vrtlMem->GetPage(_adr));
	}