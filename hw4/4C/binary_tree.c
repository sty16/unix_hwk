#include "list.h"

struct tree_node {
    int val;
    struct list_head left;
    struct list_head right;
};


int main(int argc, char* argv[]) {
    struct tree_node root;
    struct tree_node *tmp;
    INIT_LIST_HEAD(&(root.left));
    INIT_LIST_HEAD(&(root.right));
    for(int i = 0; i < 10; ++i) {
        tmp = (struct person *)malloc(sizeof(struct tree_node));
        tmp->val = i;
        list_add(&(tmp->left), &(root.left));
    }
    return 0;
}





