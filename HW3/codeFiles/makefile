# Makefile for the bank program
CC = g++
CXXFLAGS = -g -std=c++0x -Wall -w
CCLINK = $(CC)
OBJS = PhysMem.o VirtualMemory.o Test.o OurPointer.o
RM = rm -f
# Creating the  executable
all: $(OBJS)
	$(CCLINK) -o test $(OBJS)
# Creating the object files
Test.o: Test.cpp
VirtualMemory.o: VirtualMemory.cpp VirtualMemory.h  
PhysMem.o: PhysMem.cpp PhysMem.h 
OurPointer.o: OurPointer.cpp OurPointer.h 
PageTable.o: PageTable.cpp PageTable.h PageDirectoryEntry.cpp PageDirectoryEntry.h PageTableEntry.h AddressManipulation.h AddressManipulation.cpp
# Cleaning old files before new make
clean:
	$(RM) $(TARGET) *.o *~ "#"* core.*
