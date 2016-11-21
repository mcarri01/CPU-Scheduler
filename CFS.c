#include  "CFS.h"

#define  NICE_TO_WEIGHT(nice_val) 1024/pow(1.25, nice_val)

void run_cfs(process_info processes[], int num_processes){
    /* Arrival Buffer */
    cfs_pnode *arrival_buf[num_processes];
    memset(arrival_buf, 0, (size_t)sizeof(arrival_buf));
    int buf_size = 0;

    /* Initialize RB Tree */
    struct rb_tree *tree = rb_tree_create(my_cmp_cb, my_idcmp_cb);
    if (tree == NULL) {
		fprintf(stderr, "Error: Red Black Tree for Ready Queue unable to initialize.\n");
		exit(EXIT_FAILURE);
	}

	/* Begin Simulation */
	int time = 0;
	int process_count = 0;


	struct rb_iter *iter = rb_iter_create();
	if (iter == NULL) {
			fprintf(stderr, "Iteration Error in RB tree\n");
			/* FREE SHIT */
			exit(EXIT_FAILURE);
	}
	cfs_pnode *curr_running_node;
	cfs_pnode *completed_node_buf = NULL;
	float curr_running_ticks = 0;

	while(1){
		if (process_count == num_processes){
			printf("All processes have finished.\n");
			exit(EXIT_SUCCESS);
		}

		if (completed_node_buf) {
			printf("<time %d: Process %d finished.\n", time, completed_node_buf->pid);
			completed_node_buf = NULL;
		}

		check_arrival_queue(processes, arrival_buf, &buf_size, num_processes, time);

		if (time % TIME_LATENCY == 0){	
			tree = compute_schdule(tree, arrival_buf, &buf_size);
			/* Clear Arrival Buffer */
			memset(arrival_buf, 0, (size_t)sizeof(arrival_buf));
			buf_size = 0;
			curr_running_node = rb_iter_first(iter, tree);
		}


		/* Run current running process and determine if it needs to run next process */
		if (curr_running_node){
			//printf("YEEE BOI, time to do shit\n");
			printf("<time %d: Process %d running\n", time, curr_running_node->pid);
			curr_running_node->remain_t--;
			curr_running_node->run_t++;

			float remain_window_t = curr_running_node->slice_t - curr_running_ticks;
			curr_running_ticks++;
			if(remain_window_t < 1 && remain_window_t != 0){
				curr_running_node->remain_t	= 0;
				completed_node_buf = curr_running_node;
				curr_running_node = rb_iter_next(iter);
				curr_running_ticks = 0;
				if (curr_running_node) {
					printf("<time %d: Process %d running\n", time, curr_running_node->pid);
					curr_running_node->remain_t -= 1-remain_window_t;
				}
				process_count++;
				

			} else if (remain_window_t == 0){
				printf("<time %d: Process %d finished.\n", time, curr_running_node->pid);
				process_count++;
				curr_running_node = rb_iter_next(iter);
				curr_running_ticks = 0;
				if (curr_running_node) {
					printf("<time %d: Process %d running\n", time, curr_running_node->pid);
				}
			}
		} else {
			printf("<time %d: Currently no process running>\n", time);
		}


		time++;
		CTICK;	
	}
	rb_iter_dealloc(iter);


	/* Some Freeing Subroutine */
}


struct rb_tree* compute_schdule(struct rb_tree *tree, cfs_pnode *arrival_buf[], int *buf_size) {
	/* Clear the Tree */
	struct rb_iter *iter = rb_iter_create();
	if (iter) {
		for (cfs_pnode *v = rb_iter_first(iter, tree); v; v = rb_iter_next(iter)){
			if (v->remain_t != 0) {
				v->vrun_t = v->run_t * (1024/v->weight);
				arrival_buf[*buf_size] = v;
				(*buf_size)++;
			}
			
		}
	} else {
		fprintf(stderr, "Iteration Error in RB tree\n");
	}
	rb_tree_dealloc(tree, NULL);
	tree = rb_tree_create(my_cmp_cb, my_idcmp_cb);

	/* Add arrival buffer items into tree */
	for(int i = 0; i < *buf_size; i++){
		//printf("Adding shit in\n");
		rb_tree_insert(tree, arrival_buf[i]);
	}
	/* DFS and assign time slice */
	double sum_weight = 0;
	if (iter) {
   		for (cfs_pnode *v = rb_iter_first(iter, tree); v; v = rb_iter_next(iter)){ 
   			sum_weight += v->weight;
   		}
   		for (cfs_pnode *v = rb_iter_first(iter, tree); v; v = rb_iter_next(iter)) {
   			v->slice_t = TIME_LATENCY * (v->weight / sum_weight);
		    //printf("slice: %f of %d\n", v->slice_t, v->pid);
   		}
   	} else {
   		fprintf(stderr, "Iteration Error in RB tree\n");
   	}
   	rb_iter_dealloc(iter);
   	
   	return tree;
}

 void check_arrival_queue(process_info processes[], cfs_pnode *arrival_buf[], int *buf_size, int num_processes, int time) {
  	/* Linear Scan through general array to find new processes which enters */
 	for (int i = 0; i < num_processes; i++) {
		if (processes[i].arrival_t == time) {
			cfs_pnode *arr_process = malloc(sizeof(*arr_process));
			arr_process->pid = processes[i].pid;
			arr_process->remain_t = processes[i].service_t;
			arr_process->weight = NICE_TO_WEIGHT(processes[i].priority);
			arr_process->vrun_t = 0;
			arr_process->slice_t = 0;
			arr_process->run_t = 0;
			arrival_buf[*buf_size] = arr_process;
			(*buf_size)++;
		} 		
 	}
 }


/* RB Tree defined overload function */
int my_cmp_cb (struct rb_tree *self, struct rb_node *node_a, struct rb_node *node_b) {
	 (void)self;
    cfs_pnode *a = (cfs_pnode *) node_a->value;
    cfs_pnode *b = (cfs_pnode *) node_b->value;
    return (a->vrun_t < b->vrun_t) - (a->vrun_t > b->vrun_t);
}

int my_idcmp_cb (struct rb_tree *self, struct rb_node *node_a, struct rb_node *node_b) {
	(void)self;
    cfs_pnode *a = (cfs_pnode *) node_a->value;
    cfs_pnode *b = (cfs_pnode *) node_b->value;
    return (a->pid == b->pid);
}
