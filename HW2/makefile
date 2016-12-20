# Makefile for the bank program
CC = gcc
CFLAGS = -g -Wall
CCLINK = $(CC)
OBJS = bank.o
RM = rm -f
# Creating the  executable
bank: $(OBJS)
	$(CCLINK) -o smash $(OBJS)
# Creating the object files
bank.o: bank.cpp
# Cleaning old files before new make
clean:
	$(RM) $(TARGET) *.o *~ "#"* core.*

