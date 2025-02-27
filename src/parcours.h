#ifndef PARCOURS
#define PARCOURS

#include "tree.h"


typedef struct {
    char character;
    int* path;
    int size;
    int freq;
} Path;

void parcours_tree(Tree tree, int* path, int depth, Path* paths, int* nb_feuiles_parcourues);
Path* parcours_tree_wrapper(Tree tree);

#endif