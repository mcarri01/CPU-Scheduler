#include "simulator.h"

void create_schedule(char *schedule) {
	FILE *fp = fopen(schedule, "r");
	if (fp == NULL) {
		fprintf(stderr, "Error opening input file\n");
		exit(EXIT_FAILURE);
	}
	process_info process;
	int line_num = 0;
	fscanf(fp, "%d %d %d %d", &process.pid, &process.arrival_t, &process.service_t, &process.priority);
	

}