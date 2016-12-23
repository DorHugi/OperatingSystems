# Makefile for the bank program
CC = g++
CPPFLAGS = -pthread -g -Wall
CCLINK = $(CC)
OBJS = bank.o atm.o
RM = rm -f
# Creating the  executable
bankNew: $(OBJS)
	$(CCLINK) -pthread -o bank $(OBJS)
# Creating the object files
bank.o: bank.cpp atm.h
atm.o: atm.cpp atm.h
# Cleaning old files before new make
clean:
	$(RM) $(TARGET) *.o *~ "#"* core.*

