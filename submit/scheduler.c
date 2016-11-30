/*
*	shcheduler.c
*   
*	This program simulates a CPU scheduler for an OS, supporting both
*	the First Come First Serve (FCFS) and Completely Fair Scheduler (CFS)
*	algorithms. It receives both an input file of a list of processes 
*	structured as so:
*
*	pid arrival-time service-time priority
*
*	It also takes an argument indicating which scheduling algorithm to use.
*
*	After all processes finish, it reports % of CPU usage along with average 
*	turnaround time and normalized turnaround time.
*   
*   by 
*     	Justin Tze Tsun Lee
*     	Matthew Carrington-Fair
*     	Tomer Shapira
*
*
*/

#include "simulator.h"

/* Main simply checks to see if program was invoked correctly*/
int main(int argc, char *argv[]) {

        /* Ensures correct number of arguments */
	int VALID_ARGS = 1;
	VALID_ARGS = (argc == 1) ? fprintf(stderr, "Please supply input file\n") && 0 :
		     (argc == 2) ? fprintf(stderr, "Please provide schedule algorithm\n") && 0 :
		     (argc > 3 ) ? fprintf(stderr, "Too many arguments\n") && 0 :
		     1;
        /* If correct number */
	if (VALID_ARGS) {
		FILE *fp = fopen(argv[1], "r");
		if (fp == NULL) {
			fprintf(stderr, "Error opening input file\n");
			exit(EXIT_FAILURE);
		}
		/* Uses input file and algorithm to initialize */
		create_scheduler(fp, argv[2]);
		return EXIT_SUCCESS;
	}
        else {
                return EXIT_FAILURE;
        }	
}
