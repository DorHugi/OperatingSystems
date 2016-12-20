# Makefile for the bank program
CC = g++
CPPFLAGS = -g -gstabs -Wall 
CCLINK = $(CC)
OBJS = bank.o 
RM = rm -f
# Creating the  executable
bank: $(OBJS)
	$(CCLINK) -o bank $(OBJS)
# Creating the object files
bank.o: bank.cpp 
# Cleaning old files before new make
clean:
	$(RM) $(TARGET) *.o *~ "#"* core.*

