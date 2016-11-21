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
void print_results(float CPU_t, int total_t, struct rb_tree *tree, cfs_pnode *executed_buf[], int exec_size, int num_processes);
void free_shit();
#endif