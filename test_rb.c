#include "rb_tree.h"
#include "param_structures.h"


int my_cmp_cb (struct rb_tree *self, struct rb_node *node_a, struct rb_node *node_b);

int main(){


	cfs_pnode *arr_process1 = malloc(sizeof(*arr_process1));

	arr_process1->v_runtime = 1;


	cfs_pnode *arr_process2 = malloc(sizeof(*arr_process2));

	arr_process2->v_runtime = 2;


	cfs_pnode *arr_process3 = malloc(sizeof(*arr_process3));

	arr_process3->v_runtime = 3;

	cfs_pnode *arr_process4 = malloc(sizeof(*arr_process4));

	arr_process4->v_runtime = 4;

	
	struct rb_tree *tree = rb_tree_create(my_cmp_cb);
	if (tree) {
		rb_tree_insert(tree, arr_process1);
		rb_tree_insert(tree, arr_process2);
		rb_tree_insert(tree, arr_process3);
	}


    cfs_pnode *ret_struct = rb_tree_find(tree, arr_process4);

    if(ret_struct == NULL){
    	printf("Didn't find\n");
    }

    struct rb_iter *iter = rb_iter_create();
    if (iter) {
	    for (cfs_pnode *v = rb_iter_first(iter, tree); v; v = rb_iter_next(iter)) {     
	    	printf("- %f\n", v->v_runtime);
	    }
	}


    if (iter) {
	    for (cfs_pnode *v = rb_iter_first(iter, tree); v; v = rb_iter_next(iter)) {     
	    	printf("- %f\n", v->v_runtime);
	    }
	}
	
    rb_iter_dealloc(iter);

	return 1;
}


int my_cmp_cb (struct rb_tree *self, struct rb_node *node_a, struct rb_node *node_b) {

    cfs_pnode *a = (cfs_pnode *) node_a->value;
    cfs_pnode *b = (cfs_pnode *) node_b->value;
    return (a->v_runtime > b->v_runtime) - (a->v_runtime < b->v_runtime);
}