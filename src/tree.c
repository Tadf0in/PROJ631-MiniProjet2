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
 * @return Tree L'arbre de Huffman
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
    }
    free(fs.array); // On peut libérer la mémoire, on en a plus besoin

    int trees_size = fs.size;
    while (trees_size > 1) {
        // Récupère l'arbre le plus petit
        int index_min_tree1 = get_smallest_tree(trees, trees_size);
        Tree min_tree1 = remove_element(&trees, &trees_size, index_min_tree1);
        
        // Récupère le deuxième arbre le plus petit
        int index_min_tree2 = get_smallest_tree(trees, trees_size);
        Tree min_tree2 = remove_element(&trees, &trees_size, index_min_tree2);

        // Combine les 2 dans un nouvel arbre
        Tree combined;
        combined.character = '\0';
        combined.left = &min_tree1;
        combined.right = &min_tree2;
        combined.freq = min_tree1.freq + min_tree2.freq;

        printf("%d %d %d, ", trees_size, min_tree1.freq, min_tree2.freq);

        // Ajoute le nouvel arbre dans la liste d'arbres
        trees_size++;
        trees = realloc(trees, trees_size * sizeof(Tree));
        trees[trees_size-1] = combined;
    }

    // Plus que 1 seul arbre dans la liste, c'est l'arbre de Huffman
    return trees[0];
}

