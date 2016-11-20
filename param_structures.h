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


/* Universal Structures */
typedef struct process_info {
	int pid;
	int arrival_t;
	int service_t;
	int priority;
} process_info;


typedef struct cfs_pnode {
	int pid;
	double remaining_t;
	double weight;
	double slice_t;
	double v_runtime;
} cfs_pnode;