#include  "CFS.h"

#define  NICE_TO_WEIGHT(nice_val) 1024/pow(1.25, nice_val)

void run_cfs(process_info processes[], int num_processes){
    /* Arrival Buffer */
    cfs_pnode *arrival_buf[num_processes];
    cfs_pnode *executed_buf[num_processes];
    memset(arrival_buf, 0, (size_t)sizeof(arrival_buf));
    int buf_size = 0;
    int exec_size = 0;

    /* Initialize RB Tree */
    struct rb_tree *tree = rb_tree_create(my_cmp_cb, my_idcmp_cb);
    if (tree == NULL) {
		fprintf(stderr, "Error: Red Black Tree for Ready Queue unable to initialize.\n");
		exit(EXIT_FAILURE);
	}

	/* Begin Simulation */
	int total_t = 0;
	float CPU_t = 0;
	int process_count = 0;


	struct rb_iter *iter = rb_iter_create();
	if (iter == NULL) {
			fprintf(stderr, "Iteration Error in RB tree\n");
			/* FREE SHIT */
			exit(EXIT_FAILURE);
	}


	cfs_pnode *curr_running_node;
	int clock_ticks = 0;

	while(1){
		if (process_count == num_processes){
			print_cfs_results(CPU_t, total_t, tree, executed_buf, exec_size, num_processes);
			
			free_shit(processes, iter);
			exit(EXIT_SUCCESS);
		}
		check_arrival_queue(processes, arrival_buf, &buf_size, num_processes, total_t);

		if (total_t % TIME_LATENCY == 0){	
			//printf("-----TL-------\n");
			tree = compute_schdule(tree, executed_buf, &exec_size, arrival_buf, &buf_size);
			/* Clear Arrival Buffer */
			memset(arrival_buf, 0, (size_t)sizeof(arrival_buf));
			buf_size = 0;
			curr_running_node = rb_iter_first(iter, tree);
		}
		/* Run current running process and determine if it needs to run next process */
		if (curr_running_node){

			CPU_t++;
			printf("<time %d: Process %d running>\n", total_t, curr_running_node->pid);
			curr_running_node->remain_t--;
			curr_running_node->run_t++;

			float window_t = floor(curr_running_node->slice_t) - clock_ticks;
			clock_ticks++;

			if(curr_running_node->remain_t < 1){
				total_t++;
				curr_running_node->finish_t = total_t;
				printf("<time %d: Process %d finished>\n", total_t, curr_running_node->pid);
				total_t--;	
				curr_running_node->remain_t	= 0;
				curr_running_node = rb_iter_next(iter);
				clock_ticks = 0;
				//remain_window_t = curr_running_node->slice_t;
				process_count++;

			} else if(window_t <= 1){
				//float prev_remain_t = remain_window_t;
				curr_running_node = rb_iter_next(iter);
				clock_ticks = 0;
	
			}
		} 
		else if (curr_running_node == NULL) {
			printf("<time %d: Currently no process running>\n", total_t);
		}
		total_t++;
		CTICK;	
	}
	rb_iter_dealloc(iter);


	/* Some Freeing Subroutine */
}


struct rb_tree* compute_schdule(struct rb_tree *tree, cfs_pnode *executed_buf[], int *exec_size, cfs_pnode *arrival_buf[], int *buf_size) {
	/* Clear the Tree */
	struct rb_iter *iter = rb_iter_create();
	if (iter) {
		for (cfs_pnode *v = rb_iter_first(iter, tree); v; v = rb_iter_next(iter)){
			if (v->remain_t != 0) {
				v->vrun_t = v->run_t * (1024/v->weight);
				arrival_buf[*buf_size] = v;
				(*buf_size)++;
			} else {
				executed_buf[*exec_size] = v;
				(*exec_size)++;
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

 void check_arrival_queue(process_info processes[], cfs_pnode *arrival_buf[], int *buf_size, int num_processes, int total_t) {
  	/* Linear Scan through general array to find new processes which enters */
 	for (int i = 0; i < num_processes; i++) {
		if (processes[i].arrival_t == total_t) {
			cfs_pnode *arr_process = malloc(sizeof(*arr_process));
			arr_process->pid = processes[i].pid;
			arr_process->arrival_t = processes[i].arrival_t;
			arr_process->remain_t = processes[i].service_t;
			arr_process->weight = NICE_TO_WEIGHT(processes[i].priority);
			arr_process->vrun_t = 0;
			arr_process->slice_t = 0;
			arr_process->run_t = 0;
			arr_process->finish_t = 0;
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
void print_cfs_results(float CPU_t, int total_t, struct rb_tree *tree, cfs_pnode *executed_buf[], int exec_size, int num_processes) {
	
	printf("****************************\n");
	printf("All processes have finished.\n");
	float TAT = 0;
	float NTAT = 0;
	struct rb_iter *iter = rb_iter_create();
	for (int i = 0; i < exec_size; i++){
		rb_tree_insert(tree, executed_buf[i]);
	}
	if (iter) {
		for (cfs_pnode *v = rb_iter_first(iter, tree); v; v = rb_iter_next(iter)){
			TAT += (v->finish_t - v->arrival_t);
			NTAT += ((v->finish_t - v->arrival_t) / v->run_t);
		}
	} else {
		fprintf(stderr, "Iteration Error in RB tree\n");
	}
	
	rb_iter_dealloc(iter);
	rb_tree_dealloc(tree, my_free_test);

	TAT = TAT / num_processes;
	NTAT = NTAT / num_processes;
	printf("CPU usage: %.2f%c\n", CPU_t/total_t *  100,'%');
	printf("Average TAT: %.1f\n", TAT);
	printf("Average NTAT: %.1f\n", NTAT);
	printf("****************************\n");
}
void free_shit(process_info processes[], struct rb_iter *iter) {
	free(iter);
	free(processes);
}
void my_free_test(struct rb_tree *self, struct rb_node *test) {
	(void)self;
	free(test->value);
	free(test);
}
