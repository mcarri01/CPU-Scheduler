# Makefile for Project 2 COMP 111
#   by 
#    	
#   	Matthew Carrington-Fair
#     	

############## Variables ###############

CC = gcc # The compiler being used

# Compile flags

CFLAGS = -g -std=gnu99 -Wall -Wextra -Werror -Wfatal-errors -pedantic


############### Rules ###############

all: scheduler

## Compile step (.c files -> .o files)

# To get *any* .o file, compile its .c file with the following rule.
%.o: %.c 
	$(CC) $(CFLAGS) -c $< -o $@

## Linking step (.o -> executable program)
scheduler: scheduler.o simulator.o
	$(CC) -o scheduler scheduler.o simulator.o $(CFLAGS) 


clean:
	rm -f *.o core* *~scheduler