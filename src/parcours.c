#include "parcours.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


/**
 * Libère la mémoire de l'arbre
 * 
 * @param tree Arbe à libérer
 */
void free_tree(Tree* tree) {
    if (tree != NULL) {
        free_tree(tree->left);
        free_tree(tree->right);
        free(tree);
    }
}


/**
 * Parcours l'arbre de Huffman pour obtenir les chemins de chaque feuille
 * 
 * @param tree Arbre ou sous arbre à parcourir
 * @param path Chemin actuel depuis la racine
 * @param depth Profondeur actuelle depuis la racine
 * @param paths Tableau des chemins
 * @param nb_feuiles_parcourues Nombre de feuilles parcourues
 */
void parcours_tree(Tree tree, int* path, int depth, Path* paths, int* nb_feuiles_parcourues) {
    // printf("Parours : %c\n", tree.character);

    // Si une feuille
    if (tree.left == NULL && tree.right == NULL) {
        paths[*nb_feuiles_parcourues].character = tree.character;
        paths[*nb_feuiles_parcourues].size = depth;
        paths[*nb_feuiles_parcourues].path = (int*) malloc(depth * sizeof(int));
        paths[*nb_feuiles_parcourues].freq = tree.freq;
        for (int i = 0; i<depth; i++) {
            paths[*nb_feuiles_parcourues].path[i] = path[i];
        }
        (*nb_feuiles_parcourues)++;
        return;
    }
    
    // Aller à gauche
    path[depth] = 0;
    parcours_tree(*tree.left, path, depth + 1, paths, nb_feuiles_parcourues);

    // Aller à droite
    path[depth] = 1;
    parcours_tree(*tree.right, path, depth + 1, paths, nb_feuiles_parcourues);
}


/**
 * Lance le parcorus de l'arbre de Huffman
 * 
 * @param tree Arbre de Huffman
 * 
 * @return Structure associant chaque caractère à son chemin
 */
Path* parcours_tree_wrapper(Tree tree) {
    // Formules pour un ABR parfaitement équilibré
    int max_depth = (int) log2(tree.size + 1) - 1;
    int nb_leave = pow(2, max_depth);

    // On alloue la plus petite taille possible
    Path* paths = (Path*) malloc(nb_leave * sizeof(Path));
    int* path = (int*) malloc(max_depth * sizeof(int));
    int nb_feuilles_parcourues = 0;

    parcours_tree(tree, path, 0, paths, &nb_feuilles_parcourues);
    
    // Libère la mémoire
    free(path);
    free_tree(&tree);

    for (int i=0; i<nb_leave; i++) {
        printf("char: %c, path: ", paths[i].character);
        for (int j = 0; j<paths[i].size; j++) {
            printf("%d", paths[i].path[j]);
        }
        printf("\n");
    }

    return paths;
}
