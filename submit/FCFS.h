/*
*
*	FCFS.h
*
*	Header file for FCFS module defining methods to run 
*	main simulaton loop, along with helper functions to check
*	the waiting queue for any new processes that are ready-to-run.
*
*
*   by 
*     	Justin Tze Tsun Lee
*     	Matthew Carrington-Fair
*     	Tomer Shapira
*
*/


#ifndef FCFS_H
#define FCFS_H

#include "CFS.h"

void run_fcfs(process_info processes[], int num_processes);

void print_fcfs_results(float CPU_t, int total_t, fcfs_pnode *processes[], int num_processes);
void check_fcfs_queue(process_info processes[], fcfs_pnode *arrival_buf[], int *buf_size, int num_processes, int total_t);
#endif