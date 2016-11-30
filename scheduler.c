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
	/* No input file or algorithm*/
	if (argc == 1) {
		fprintf(stderr, "Please supply input file\n");
		exit(EXIT_FAILURE);
	}
	/* No algorithm */
	else if (argc == 2) {
		fprintf(stderr, "Please provide schedule algorithm\n");
		exit(EXIT_FAILURE);
	}
	/* As error suggests, too many args */
	else if (argc > 4) {
		fprintf(stderr, "Too many arguments\n");
		exit(EXIT_FAILURE);
	}

	FILE *fp = fopen(argv[1], "r");
	if (fp == NULL) {
		fprintf(stderr, "Error opening input file\n");
		exit(EXIT_FAILURE);
	}

	/* Uses input file and algorithm to initialize scheduler */
	create_scheduler(fp, argv[2]);
	return EXIT_SUCCESS;
}
