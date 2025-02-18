#ifndef TREE
#define TREE

typedef struct Tree_s {
    char character;
    struct Tree_s* left;
    struct Tree_s* right;
    int freq;
} Tree;

int get_smallest_tree(Tree* trees, int trees_size);
void remove_element(Tree** trees, int* trees_size, int remove_index);
void make_tree(char* filename);

#endif