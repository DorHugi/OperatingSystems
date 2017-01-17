# Makefile for the bank program
CC = g++
CPPFLAGS = -g -Wall -std=c++11
CCLINK = $(CC)
OBJS = PhysMem.o VirtualMemory.o Test.o
RM = rm -f
# Creating the  executable
all: $(OBJS)
	$(CCLINK) -o test $(OBJS)
# Creating the object files
Test.o: Test.cpp
VirtualMemory.o: VirtualMemory.cpp
PhysMem.o: PhysMem.cpp PhysMem.h
# Cleaning old files before new make
clean:
	$(RM) $(TARGET) *.o *~ "#"* core.*
