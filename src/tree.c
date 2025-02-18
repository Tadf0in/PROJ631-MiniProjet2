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
    if (trees_size <= 0) {
        return NULL;
    }
    int i_min = 0;
    int freq_min = trees[0].freq;
    for (int i=1; i<trees_size; i++) {
        if (trees[i].freq < freq_min) {
            i_min = i;
        }
    }
    return i_min;
}


void remove_element(Tree** trees, int* trees_size, int remove_index) {
    for (int i=remove_index; i<trees_size-1; i++) {
        (*trees)[i] = (*trees)[i+1];
    }
    (*trees_size)--;
    *trees = realloc(*trees, (*trees_size) * sizeof(Tree));
}


void make_tree(char* filename) {
    FrequencySize fs = count_frequency(filename);
    
    // Créé un tableau d'arbres avec 1 arbre = 1 noeud = 1 caractère 
    Tree* trees = (Tree*) malloc(fs.size * sizeof(Tree));
    for (int i=0; i<fs.size; i++) {
        trees[i].character = fs.array[i].character;
        trees[i].left = NULL;
        trees[i].right = NULL;
        trees[i].freq = fs.array[i].count;
    }
    free(fs.array); // On peut libérer la mémoire, on en a plus besoin

    int trees_size = fs.size;
    while (trees_size > 1) {
        int min_tree1 = get_smallest_tree(trees, trees_size);
        

        trees_size--;
    }
}

