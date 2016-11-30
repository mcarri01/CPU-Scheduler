/*
*
*	param_structres.h
*
*	Universal header file to define general purpose
*	structs for processes, including algorithm-specific
*	structs for both FCFS and CFS. 
*
*	This file also defines CTICK as waiting for a second to
*	represent a single clock-tick, and defines TIME_LATENCY 
*	for CFS.
*
*
*   by 
*     	Justin Tze Tsun Lee
*     	Matthew Carrington-Fair
*     	Tomer Shapira
*
*
*/


/* Standard Includes */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>
#include <math.h>

/* Delay Macros */
#define CTICK sleep(1)

/* Parameters CFS */
#define TIME_LATENCY 5

/* Paramters Round Robin */


/* Universal Structure for Process */
typedef struct process_info {
	int pid;
	int arrival_t;
	int service_t;
	int priority;
} process_info;

/* Represents a process using FCFS algorithm */
typedef struct fcfs_pnode {
	int pid;
	int service_t;
	int arrival_t;
	int finish_t;
	int run_t;
} fcfs_pnode;

/* Represents a process using CFS algorithm */
typedef struct cfs_pnode {
	int pid;
	int arrival_t;
	int finish_t;
	double run_t;
	double weight;
	double remain_t;
	double slice_t;
	double vrun_t;
} cfs_pnode;

