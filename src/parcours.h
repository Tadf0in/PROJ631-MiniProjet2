#ifndef PARCOURS
#define PARCOURS

#include "tree.h"

typedef struct {
    char character;
    int* path;
} Encoded;

void parcours_tree(Tree tree, int* path, int depth, Encoded* encodeds, int* nb_feuiles_parcourues);
Encoded* parcours_tree_wrapper(Tree tree);

#endif