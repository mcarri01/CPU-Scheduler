#include "rb_tree.h"
#include "param_structures.h"


int my_cmp_cb (struct rb_tree *self, struct rb_node *node_a, struct rb_node *node_b);
int my_idcmp_cb (struct rb_tree *self, struct rb_node *node_a, struct rb_node *node_b);
int main(){


	cfs_pnode *arr_process1 = malloc(sizeof(*arr_process1));
	arr_process1->pid = 1;
	arr_process1->v_runtime = 1;


	cfs_pnode *arr_process2 = malloc(sizeof(*arr_process2));
	arr_process2->pid = 2;
	arr_process2->v_runtime = 4;


	cfs_pnode *arr_process3 = malloc(sizeof(*arr_process3));
	arr_process3->pid = 3;
	arr_process3->v_runtime = 3;

	cfs_pnode *arr_process4 = malloc(sizeof(*arr_process4));
	arr_process4->pid = 4;
	arr_process4->v_runtime = 3;

	
	struct rb_tree *tree = rb_tree_create(my_cmp_cb,my_idcmp_cb);

	rb_tree_insert(tree, arr_process1);
	rb_tree_insert(tree, arr_process2);
	rb_tree_insert(tree, arr_process3);
	rb_tree_insert(tree, arr_process4);

    struct rb_iter *iter = rb_iter_create();
 //    if (iter) {
	//     for (cfs_pnode *v = rb_iter_first(iter, tree); v; v = rb_iter_next(iter)) {     
	//     	printf("%d - %f\n",  v->pid, v->v_runtime);
	//     	//rb_tree_remove(tree, v);
	//     }
	// }

    cfs_pnode *v = rb_iter_first(iter, tree);
    printf("%d - %f\n",  v->pid, v->v_runtime);
    rb_tree_remove(tree, v);

    v = rb_iter_first(iter, tree);
    printf("%d - %f\n",  v->pid, v->v_runtime);
    rb_tree_remove(tree, v);

    v = rb_iter_first(iter, tree);
    printf("%d - %f\n",  v->pid, v->v_runtime);
    rb_tree_remove(tree, v);

    v = rb_iter_first(iter, tree);
    printf("%d - %f\n",  v->pid, v->v_runtime);
    rb_tree_remove(tree, v);

	printf("Size: %d\n", tree->size);


    rb_iter_dealloc(iter);

	return 1;
}


int my_cmp_cb (struct rb_tree *self, struct rb_node *node_a, struct rb_node *node_b) {
    cfs_pnode *a = (cfs_pnode *) node_a->value;
    cfs_pnode *b = (cfs_pnode *) node_b->value;
    return (a->v_runtime > b->v_runtime) - (a->v_runtime < b->v_runtime);
}

int my_idcmp_cb (struct rb_tree *self, struct rb_node *node_a, struct rb_node *node_b) {
    cfs_pnode *a = (cfs_pnode *) node_a->value;
    cfs_pnode *b = (cfs_pnode *) node_b->value;
    return (a->pid == b->pid);
}