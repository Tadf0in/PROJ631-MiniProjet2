#include "tree.h"
#include "alphabet.h"

#include <stdio.h>
#include <stdlib.h>

/**
 * Récupère l'indice de l'arbre avec la plus petite fréquence
 * 
 * @param trees Liste d'arbres
 * @param trees_size Taille de la liste d'arbres
 * 
 * @return int 
 */
int get_smallest_tree(Tree* trees, int trees_size) {
    int i_min = 0;
    int freq_min = trees[0].freq;
    for (int i=1; i<trees_size; i++) {
        if (trees[i].freq < freq_min) {
            i_min = i;
        }
    }
    return i_min;
}

/**
 * Supprime un élément d'une liste d'arbres
 * 
 * @param trees Pointeur vers une liste d'arbres
 * @param trees_size Pointeur vers la taille de la liste d'arbres
 * @param remove_index Indice de l'élément à supprimer
 * 
 * @return Tree élément qui vient d'être supprimé
 */
Tree remove_element(Tree** trees, int* trees_size, int remove_index) {
    Tree popped = (*trees)[remove_index];
    for (int i=remove_index; i<*trees_size-1; i++) {
        (*trees)[i] = (*trees)[i+1];
    }
    (*trees_size)--;
    *trees = realloc(*trees, (*trees_size) * sizeof(Tree));
    return popped;
}


/**
 * Créé un arbre de Huffman
 * 
 * @param filename Chemin vers le fichier 
 * 
 * @return Tree L'abre de Huffman
 */
Tree make_tree(char* filename) {
    FrequencySize fs = count_frequency(filename);
    
    // Créé un tableau d'arbres avec 1 arbre = 1 noeud = 1 caractère 
    Tree* trees = (Tree*) malloc(fs.size * sizeof(Tree));
    for (int i=0; i<fs.size; i++) {
        trees[i].character = fs.array[i].character;
        trees[i].left = NULL;
        trees[i].right = NULL;
        trees[i].freq = fs.array[i].count;
        trees[i].size = 1;
    }
    free(fs.array); // On peut libérer la mémoire, on en a plus besoin

    int trees_size = fs.size;
    while (trees_size > 1) {
        
        
        // Combine les 2 dans un nouvel arbre
        Tree combined;
        combined.character = '\0';
        
        // Récupère l'arbre le plus petit
        int index_min_tree1 = get_smallest_tree(trees, trees_size);
        combined.left = (Tree*)malloc(sizeof(Tree));
        *combined.left = remove_element(&trees, &trees_size, index_min_tree1);
        
        // Récupère le deuxième arbre le plus petit
        int index_min_tree2 = get_smallest_tree(trees, trees_size);
        combined.right = (Tree*) malloc(sizeof(Tree));
        *combined.right = remove_element(&trees, &trees_size, index_min_tree2);
        
        combined.freq = combined.left->freq + combined.right->freq;
        combined.size = combined.left->size + combined.right->size + 1;

        // printf("combined : %c %d %c %c\n", combined.character, combined.freq, combined.left->character, combined.right->character);

        // Ajoute le nouvel arbre dans la liste d'arbres
        trees_size++;
        trees = realloc(trees, trees_size * sizeof(Tree));
        trees[trees_size-1] = combined;
    }

    // Plus que 1 seul arbre dans la liste, c'est l'arbre de Huffman
    return trees[0];
}


// /**
//  * Affiche l'arbre de Huffman
//  * 
//  * @param tree Arbre de Huffman
//  * @param depth Profondeur actuelle de l'arbre
//  */
// void affiche_tree(Tree tree, int depth) {
//     // Si une feuille
//     if (tree.left == NULL && tree.right == NULL) {
//         printf("[char: %c, freq: %d]\n", tree.character, tree.freq);
//         return;
//     }

//     printf("freq:%d left:%c right:%c\n", tree.freq, tree.left->character, tree.right->character);

//     // Affiche le sous arbre droit
//     affiche_tree(*tree.right, depth + 1);

//     // Affiche le sous arbre gauche
//     affiche_tree(*tree.left, depth + 1);
// }