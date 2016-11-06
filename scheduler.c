#include <stdlib.h>
#include <stdio.h>
#include "simulator.h"


int main(int argc, char *argv[]) {
	if (argc == 1) {
		fprintf(stderr, "Please supply input file\n");
		exit(EXIT_FAILURE);
	}
	else if (argc == 2) {
		fprintf(stderr, "Please provide schedule algorithm\n");
		exit(EXIT_FAILURE);
	}
	else if (argc > 4) {
		fprintf(stderr, "Too many arguments\n");
		exit(EXIT_FAILURE);
	}
	create_schedule(argv[1]);
	(void)argv;
	return EXIT_SUCCESS;
}
