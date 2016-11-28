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

	FILE *fp = fopen(argv[1], "r");
	if (fp == NULL) {
		fprintf(stderr, "Error opening input file\n");
		exit(EXIT_FAILURE);
	}


	create_scheduler(fp, argv[2]);
	return EXIT_SUCCESS;
}
