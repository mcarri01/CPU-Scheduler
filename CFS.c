#include  "CFS.h"

#define  NICE_TO_WEIGHT(nice_val) 1024/pow(1.25, nice_val)


void run_cfs(process_info processes[], int num_processes){
    /* Arrival Buffer */
    cfs_pnode *arrival_buf[num_processes];
    memset(arrival_buf, 0, (size_t)sizeof(arrival_buf));
    int buf_size = 0;


    /* Initialize RB Tree */


    /* ------------------ */


	int time = 0;
	while(1){
		fprintf(stdout, "<time %d>\n", time);

		/* Linear Scan through general array to find new processes which enters */
		for(int i = 0; i < num_processes; i++){
			if(processes[i].arrival_t == time){
				fprintf(stdout, "%d entered run-queue\n", processes[i].pid);
				cfs_pnode *arr_process = malloc(sizeof(*arr_process));
				arr_process->pid = processes[i].pid;
				arr_process->remaining_t = processes[i].service_t;
				arr_process->weight = NICE_TO_WEIGHT(processes[i].priority);
				arr_process->v_runtime = 0;
				arr_process->slice_t = 0;


				arrival_buf[buf_size] = arr_process;
				buf_size++;
			}
		}

		/* Check if it is the start of TL Window */
		if (time % TIME_LATENCY == 0){
			fprintf(stdout, "--- TL Window ---\n");
			/* Add arrival buffer items into tree */

			/* Clear Arrival Buffer */
			memset(arrival_buf, 0, (size_t)sizeof(arrival_buf));
    		buf_size = 0;

			/* DFS and assign time slice */
		}

		/* Iterate Time and Sleep Delay */
		time++;
		CTICK;
	}



	/* Some Freeing Subroutine */

}