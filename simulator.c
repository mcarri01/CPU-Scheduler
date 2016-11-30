/*
*	simulator.c
*   
*	Core fnctions for simulator.c
*
*	Contains the methods:
*
*	This module initializes the simulator for the scheduler.
*	It reads the list of processes and stores them in a waiting queue
*	to be processed once it runs the simulation.
*   
*   by 
*     	Justin Tze Tsun Lee
*     	Matthew Carrington-Fair
*     	Tomer Shapira
*
*/

#include "simulator.h"
#define INIT_P_CAP 1

/* Creates scheduler given a file of processes and algorithm type */
void create_scheduler(FILE* file, char* algo) {

	/* Create Global Process Structure */
	int plist_capacity = INIT_P_CAP;
	int plist_size     = 0;

	process_info *processes = malloc(sizeof(*processes) * plist_capacity);
	process_info process;
	/* Each call to fscanf returns a single line from file (indiv process) */
	while (fscanf(file, "%d %d %d %d",
		   &process.pid, &process.arrival_t,
		   &process.service_t, &process.priority) != EOF){
		/* Expand processes array if needed */
		if (plist_size == plist_capacity){
			plist_capacity = plist_capacity * 2;
			processes = realloc(processes, plist_capacity * sizeof(*processes));
			assert(processes != NULL);
		}
		/* Tosses it in the waiting queue */
		processes[plist_size] = process;
		plist_size++;
	}
	fclose(file);


	/* Create Scheduler for CFS */
	if (strcmp(algo, "CFS") == 0){
		fprintf(stdout, "Linux Completely Fair Scheduling Running\n");
		run_cfs(processes, plist_size);
	/* Create Scheduler for FCFS */	
	} else if (strcmp(algo, "FCFS") == 0){
		fprintf(stdout, "First Come First Serve Scheduling Running\n");
		run_fcfs(processes, plist_size);
	/* Not supported algorithm */	
	} else {
		fprintf(stderr, "ERROR: Scheduling Algorithm not recognized.\n");
		free(processes);
		exit(EXIT_FAILURE);
	}


	free(processes);
	return;	
}