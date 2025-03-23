#include "../src/tree.h"
#include "../src/parcours.h"
#include <stdio.h>
#include <stdlib.h>
#include "./list_tests.h"


int main() {
    printf("\n====================================\nDébut test_parcours\n====================================\n");
    
    for (int i = 0; i < 4; i++) {
        printf("\n - %s\n", printnames[i]);
        Tree t = make_tree(filenames[i]);
        parcours_tree_wrapper(&t);
    }

    printf("\n====================================\ntest_parcours OK\n====================================\n");

    return EXIT_SUCCESS;
}