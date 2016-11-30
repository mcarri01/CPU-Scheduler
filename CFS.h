/*
*
*	CFS.h
*
*	Header file for CFS module defining methods to run 
*	main simulaton loop, along with helper functions to check
*	the waiting queue for any new processes that are ready-to-run,
*	updating the red-black tree before each TIME_LATENCY, and printing
*	results after the simulation. 
*
*	In addition, defines two comparison functions used to navigate
*	the red-black tree when traversing.
*
*
*   by 
*     	Justin Tze Tsun Lee
*     	Matthew Carrington-Fair
*     	Tomer Shapira
*
*
*/

#ifndef _CFS_H
#define _CFS_H

#include <math.h>
#include "rb_tree.h"
#include "param_structures.h"



void run_cfs(process_info processes[], int num_processes);

/* RB Tree Comparison Function */
int my_cmp_cb (struct rb_tree *self, struct rb_node *node_a, struct rb_node *node_b);
int my_idcmp_cb (struct rb_tree *self, struct rb_node *node_a, struct rb_node *node_b);
struct rb_tree* compute_schdule(struct rb_tree *tree, cfs_pnode *execute_buf[], int *exec_size, cfs_pnode *arrival_buf[], int *buf_size);
void check_arrival_queue(process_info processes[], cfs_pnode *arrival_buf[], int *buf_size, int num_processes, int time);
void print_cfs_results(float CPU_t, int total_t, struct rb_tree *tree, cfs_pnode *executed_buf[], int exec_size, int num_processes);
void my_free_test(struct rb_tree *self, struct rb_node *test);
void free_tree_nodes(struct rb_tree *self, struct rb_node *node);
void free_shit(process_info processes[], struct rb_iter *iter);
#endif