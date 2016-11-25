#include "FCFS.h"

void run_fcfs(process_info processes[], int num_processes) {

	fcfs_pnode *arrival_buf[num_processes];
	fcfs_pnode *executed_buf[num_processes];
	memset(arrival_buf, 0, (size_t)sizeof(arrival_buf));
	memset(executed_buf, 0, (size_t)sizeof(executed_buf));
	int buf_size = 0;
	int exec_size = 0;
	/* Begin Simulation */
	int total_t = 0;
	float CPU_t = 0;
	int process_count = 0;
	fcfs_pnode *curr_running_process;
	int curr_process = 0;
	while(1) {
		if (process_count == num_processes){
			free(processes);
			print_fcfs_results(CPU_t, total_t, executed_buf, num_processes);
			exit(EXIT_SUCCESS);
		}
		check_fcfs_queue(processes, arrival_buf, &buf_size, num_processes, total_t);
		curr_running_process = arrival_buf[curr_process];
		if (curr_running_process) {
			CPU_t++;
			printf("<time %d: Process %d running>\n", total_t, curr_running_process->pid);
			curr_running_process->run_t++;
			if (curr_running_process->run_t == curr_running_process->service_t) {
				total_t++;
				curr_running_process->finish_t = total_t;
				printf("<time %d: Process %d finished>\n", total_t, curr_running_process->pid);
				
				executed_buf[exec_size] = curr_running_process;
				exec_size++;
				curr_process++;
				total_t--;
				process_count++;
			}
		} else {
			printf("<time %d: Currently no process running>\n", total_t);
		}
		total_t++;
		CTICK;
	}
}
void check_fcfs_queue(process_info processes[], fcfs_pnode *arrival_buf[], int *buf_size, int num_processes, int total_t) {
	for (int i = 0; i < num_processes; i++) {
		if (processes[i].arrival_t == total_t) {
			fcfs_pnode *process = malloc(sizeof(*process));
			process->pid = processes[i].pid;
			process->arrival_t = processes[i].arrival_t;
			process->service_t = processes[i].service_t;
			process->run_t = 0;
			arrival_buf[*buf_size] = process;
			(*buf_size)++;
		}
	}
}
void print_fcfs_results(float CPU_t, int total_t, fcfs_pnode *processes[], int num_processes) {
	printf("****************************\n");
	printf("All processes have finished.\n");
	float TAT = 0;
	float NTAT = 0;	
	for (int i = 0; i < num_processes; i++) {
		TAT += (processes[i]->finish_t - processes[i]->arrival_t);
		NTAT += ((processes[i]->finish_t - processes[i]->arrival_t) / processes[i]->service_t);
		free(processes[i]);
	}
	TAT = TAT / num_processes;
	NTAT = NTAT / num_processes;
	printf("CPU usage: %.2f%c\n", CPU_t/total_t *  100,'%');
	printf("Average TAT: %.1f\n", TAT);
	printf("Average NTAT: %.1f\n", NTAT);
	printf("****************************\n");
}
