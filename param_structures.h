/* Standard Includes */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>


/* Parameters CFS */
#define CTICK sleep(1)


/* Paramters Round Robin */


/* Universal Structures */
typedef struct process_info {

	int pid;
	int arrival_t;
	int service_t;
	int priority;

} process_info;