# 
# Sample Makefile for project 1 (COMP30017)
#
# The program used for illustration purposes is
# a simple program using input numbers
#


## CC  = Compiler.
## CFLAGS = Compiler flags.
CC	= gcc
CFLAGS 	= -Wall  


## OBJ = Object files.
## SRC = Source files.
## EXE = Executable name.

SRC =		main.c input.c linkedlist.c sortedlinkedlist.c process.c memoryfree.c fcfs.c multi.c
OBJ =		main.o input.o linkedlist.o sortedlinkedlist.o process.o memoryfree.o fcfs.o multi.o
EXE = 		simulation

## Top level target is executable.
$(EXE):	$(OBJ)
		$(CC) $(CFLAGS) -o $(EXE) $(OBJ) -lm


## Clean: Remove object files and core dump files.
clean:
		/bin/rm $(OBJ) 

## Clobber: Performs Clean and removes executable file.

clobber: clean
		/bin/rm $(EXE) 

## Dependencies

multi.o:				multi.c fcfs.h memoryfree.h sortedlinkedlist.h input.h
fcfs.o:					fcfs.c fcfs.h memoryfree.h sortedlinkedlist.h input.h
memoryfree.o:			memoryfree.c memoryfree.h sortedlinkedlist.h
process.o:				process.c process.h
linkedlist.o: 			linkedlist.c linkedlist.h process.h
sortedlinkedlist.o: 	sortedlinkedlist.c process.h memoryfree.h
input.o:				input.c input.h linkedlist.h process.h
main.o:					main.c fcfs.h memoryfree.h sortedlinkedlist.h input.h
