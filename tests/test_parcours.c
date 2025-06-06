#include "../src/tree.h"
#include "../src/parcours.h"
#include <stdio.h>
#include <stdlib.h>
#include "./list_tests.h"


int main() {
    printf("\n====================================\nDébut test_parcours\n====================================\n");
    
    for (int i = 0; i < 5; i++) {
        printf("\n - %s\n", printnames[i]);
        Tree t = make_tree(filenames[i]);
        int size = t.nb_leaves;
        Path* paths = parcours_tree_wrapper(&t);

        for (int i=0; i<size; i++) {
            printf("char: %c (ascii %d), path: ", paths[i].character, paths[i].character);
            for (int j = 0; j<paths[i].size; j++) {
                printf("%d", paths[i].path[j]);
            }
            printf(", size: %d, freq: %d\n", paths[i].size, paths[i].freq);
        }

        float sum_freq = 0;
        float sum_size = 0;
        for (int i=0; i<size; i++) {
            sum_size += paths[i].size * paths[i].freq;
            sum_freq += paths[i].freq;
        } 
        float mean = sum_size / sum_freq;
        printf("Moyenne : %.2f bits par caratère\n", mean);

        free_paths(paths, size);
    }

    printf("\n====================================\ntest_parcours OK\n====================================\n");

    return EXIT_SUCCESS;
}