#ifndef _CFS_H
#define _CFS_H

#include <math.h>
#include "rb_tree.h"
#include "param_structures.h"



void run_cfs(process_info processes[], int num_processes);


/* RB Tree Comparison Function */
int my_cmp_cb (struct rb_tree *self, struct rb_node *node_a, struct rb_node *node_b);

#endif