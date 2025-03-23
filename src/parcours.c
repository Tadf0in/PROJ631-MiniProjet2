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
    if (tree->left != NULL) {
        free_tree(tree->left);
    }
    if (tree->right != NULL) {
        free_tree(tree->right);
    }
    if (tree != NULL) {
        free(tree);
        tree = NULL;
    }
}

/**
 * Libère la mémoire des chemins
 * 
 * @param paths Tableau des chemins à libérer
 * @param nb_paths Nombre de chemins dans le tableau
 */
void free_paths(Path* paths, int nb_paths) {
    for (int i = 0; i < nb_paths; i++) {
        if (paths[i].path != NULL) {
            free(paths[i].path);
            paths[i].path = NULL;
        }
    }
    free(paths);
    paths = NULL;
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
void parcours_tree(Tree* tree, int* path, int depth, Path** paths, int* nb_feuiles_parcourues) {
    // Si une feuille
    if (tree->left == NULL && tree->right == NULL) {
        // printf("Parcours : %c %d\n", tree->character, tree->character);
        (*paths)[*nb_feuiles_parcourues].character = tree->character;
        (*paths)[*nb_feuiles_parcourues].size = depth;
        (*paths)[*nb_feuiles_parcourues].path = (int*) malloc(depth * sizeof(int));
        (*paths)[*nb_feuiles_parcourues].freq = tree->freq;
        for (int i = 0; i<depth; i++) {
            (*paths)[*nb_feuiles_parcourues].path[i] = path[i];
        }
            for (int i = 0; i<depth; i++) {
            }
        (*nb_feuiles_parcourues)++;
        return;
    }
    
    // Aller à gauche
    path[depth] = 0;
    parcours_tree(tree->left, path, depth + 1, paths, nb_feuiles_parcourues);

    // Aller à droite
    path[depth] = 1;
    parcours_tree(tree->right, path, depth + 1, paths, nb_feuiles_parcourues);
}


/**
 * Lance le parcorus de l'arbre de Huffman
 * 
 * @param tree Arbre de Huffman
 * 
 * @return Structure associant chaque caractère à son chemin
 */
Path* parcours_tree_wrapper(Tree* tree) {

    // On alloue la mémoire (trop mais suffisamment)
    Path* paths = (Path*) malloc(tree->nb_leaves * sizeof(Path));
    int* path = (int*) malloc((tree->nb_leaves) * sizeof(int));
    int nb_feuilles_parcourues = 0;
    parcours_tree(tree, path, 0, &paths, &nb_feuilles_parcourues);

    // Libère la mémoire
    free(path);
    path = NULL;

    // for (int i=0; i<tree->nb_leaves; i++) {
    //     printf("char: %c (ascii %d), path: ", paths[i].character, paths[i].character);
    //     for (int j = 0; j<paths[i].size; j++) {
    //         printf("%d", paths[i].path[j]);
    //     }
    //     printf(", size: %d, freq: %d\n", paths[i].size, paths[i].freq);
    // }

    return paths;
}
