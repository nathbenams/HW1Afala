# Makefile for the smash program
CC = g++
CFLAGS = -g -Wall
CCLINK = $(CC)
OBJS = smash.o commands.o signals.o Jobs.o ListOfJobs.o HistoryCommands.o
RM = rm -f
# Creating the  executable
smash: $(OBJS)
	$(CCLINK) -o smash $(OBJS)
# Creating the object files
commands.o: commands.cpp commands.h
smash.o: smash.cpp commands.h signals.h Jobs.h ListOfJobs.h HistoryCommands.h
signals.o: signals.cpp signals.h
ListOfJobs.o: ListOfJobs.cpp ListOfJobs.h
Jobs.o: Jobs.cpp Jobs.h
HistoryCommands.o: HistoryCommands.cpp HistoryCommands.h 
# Cleaning old files before new make
clean:
	$(RM) $(TARGET) *.o *~ "#"* core.*

