#include "../src/alphabet.h"
#include "../src/tree.h"
#include <stdio.h>
#include <stdlib.h>


int main() {
    printf("\n====================================\nDébut test_tree\n====================================\n");
    
    FrequencySize fs = count_frequency("data/textesimple.txt");
    
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

    int smallest = get_smallest_tree(trees, trees_size);
    printf("%c", trees[smallest].character);

    printf("\n====================================\ntest_tree OK\n====================================\n");

    return EXIT_SUCCESS;
}