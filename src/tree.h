#ifndef TREE
#define TREE

#include "alphabet.h"

typedef struct Tree_s {
    char character;
    struct Tree_s* left;
    struct Tree_s* right;
    int freq;
    int size;
    int nb_leaves;
} Tree;

int get_smallest_tree(Tree* trees, int trees_size);
Tree remove_element(Tree** trees, int* trees_size, int remove_index);
Tree make_tree(char* filename);
// void affiche_tree(Tree tree, int depth);

#endif