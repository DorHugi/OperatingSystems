# Makefile for the bank program
CC = g++
CPPFLAGS = -g -Wall 
CCLINK = $(CC)
OBJS = bank.o 
RM = rm -f
# Creating the  executable
bank: $(OBJS)
	$(CCLINK) -o bank $(OBJS)
# Creating the object files
bank.o: bank.cpp 
atm.o: atm.cpp atm.h
# Cleaning old files before new make
clean:
	$(RM) $(TARGET) *.o *~ "#"* core.*

