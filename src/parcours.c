#include "parcours.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


void parcours_tree(Tree tree, int* path, int depth, Encoded* encodeds, int* nb_feuiles_parcourues) {
    printf("Parours : %c\n", tree.character);

    // Si une feuille
    if (tree.left == NULL && tree.right == NULL) {
        encodeds[*nb_feuiles_parcourues].character = tree.character;
        encodeds[*nb_feuiles_parcourues].path = (int*) malloc(depth * sizeof(int));
        for (int i = 0; i<depth; i++) {
            encodeds[*nb_feuiles_parcourues].path[i] = path[i];
        }
        (*nb_feuiles_parcourues)++;
        return;
    }
    
    // Aller à gauche
    path[depth] = 0;
    parcours_tree(*tree.left, path, depth + 1, encodeds, nb_feuiles_parcourues);

    // Aller à droite
    path[depth] = 1;
    parcours_tree(*tree.right, path, depth + 1, encodeds, nb_feuiles_parcourues);
}


Encoded* parcours_tree_wrapper(Tree tree) {
    // Formules pour un ABR parfaitement équilibré
    int max_depth = (int) log2(tree.size + 1) - 1;
    int nb_leave = pow(2, max_depth);

    // On alloue la plus petite taille possible
    Encoded* encodeds = (Encoded*) malloc(nb_leave * sizeof(Encoded));
    int* path = (int*) malloc(max_depth * sizeof(int));
    int nb_feuilles_parcourues = 0;

    parcours_tree(tree, path, 0, encodeds, &nb_feuilles_parcourues);
    
    free(path);

    return encodeds;
}
