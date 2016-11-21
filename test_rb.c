#include "rb_tree.h"
#include "param_structures.h"
#include <math.h>


int my_cmp_cb (struct rb_tree *self, struct rb_node *node_a, struct rb_node *node_b);
int my_idcmp_cb (struct rb_tree *self, struct rb_node *node_a, struct rb_node *node_b);
int main(){
	struct rb_tree *tree = rb_tree_create(my_cmp_cb,my_idcmp_cb);

	for (int i = 0; i < 50; i ++){
		cfs_pnode *arr_process = malloc(sizeof(*arr_process));
		arr_process->pid = i;
		arr_process->vrun_t = i;
		rb_tree_insert(tree, arr_process);
	}

    struct rb_iter *iter = rb_iter_create();

    if (iter) {
	    for (cfs_pnode *v = rb_iter_first(iter, tree); v; v = rb_iter_next(iter)) {     
	    	printf("%d - %f\n",  v->pid, v->vrun_t);
	    	//rb_tree_remove(tree, v);
	    }
	}

    rb_iter_dealloc(iter);

	return 1;
}


int my_cmp_cb (struct rb_tree *self, struct rb_node *node_a, struct rb_node *node_b) {
    cfs_pnode *a = (cfs_pnode *) node_a->value;
    cfs_pnode *b = (cfs_pnode *) node_b->value;
    return (a->vrun_t > b->vrun_t) - (a->vrun_t < b->vrun_t);
}

int my_idcmp_cb (struct rb_tree *self, struct rb_node *node_a, struct rb_node *node_b) {
    cfs_pnode *a = (cfs_pnode *) node_a->value;
    cfs_pnode *b = (cfs_pnode *) node_b->value;
    return (a->pid == b->pid);
}