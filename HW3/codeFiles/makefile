# Makefile for the Bank program
CC = g++
CXXFLAGS = -g -std=c++0x -Wall
CCLINK = $(CC)
OBJS = main.o VirtualMemory.o OurPointer.o PageTable.o PhysMem.o PageDirectoryEntry.o AddressManipulation.o SwapDevice.o
RM = rm -f
# Creating the  executable
App: $(OBJS)
	$(CCLINK) $(CFLAGS) -o App $(OBJS) 
# Creating the object files
main.o: main.cpp VirtualMemory.h OurPointer.h
VirtualMemory.o: VirtualMemory.h VirtualMemory.cpp OurPointer.h PhysMem.h PageTable.h
OurPointer.o: OurPointer.h OurPointer.cpp PageTable.h
PageTable.o: PageTable.h PageTable.cpp VirtualMemory.h
PhysMem.o: PhysMem.cpp PhysMem.h 
PageDirectoryEntry.o: PageDirectoryEntry.cpp PageDirectoryEntry.h PageTableEntry.h
AddressManipulation.o: AddressManipulation.cpp AddressManipulation.h
SwapDevice.o: SwapDevice.cpp SwapDevice.h
# Cleaning old files before new make
clean:
	$(RM) $(TARGET) *.o *~ "#"* core.*

