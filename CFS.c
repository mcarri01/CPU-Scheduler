#include  "CFS.h"

void run_cfs(process_info processes[]){
	(void)processes;

	int time = 0;
	while(true){
		fprintf(stdout, "<time %d>\n", time);
		time++;
		CTICK;


	}

}