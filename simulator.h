#include <stdlib.h>
#include <stdio.h>

typedef struct process_info {

	int pid;
	int arrival_t;
	int service_t;
	int priority;

} process_info;

void create_schedule(char *schedule);