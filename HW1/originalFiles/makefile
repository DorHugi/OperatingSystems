# Makefile for the smash program
CC = g++
CPPFLAGS = -g -gstabs -Wall 
CCLINK = $(CC)
OBJS = smash.o commands.o signals.o
RM = rm -f
# Creating the  executable
smash: $(OBJS)
	$(CCLINK) -o smash $(OBJS)
# Creating the object files
commands.o: commands.cpp commands.h jobs.h
smash.o: smash.cpp commands.h 
signals.o: signals.cpp signals.h jobs.h
# Cleaning old files before new make
clean:
	$(RM) $(TARGET) *.o *~ "#"* core.*

