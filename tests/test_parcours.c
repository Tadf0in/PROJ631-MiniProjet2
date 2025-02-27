#include "../src/tree.h"
#include "../src/parcours.h"
#include <stdio.h>
#include <stdlib.h>


int main() {
    printf("\n====================================\nDébut test_parcours\n====================================\n");
    
    printf("Texte simple :\n");
    Tree ts = make_tree("data/textesimple.txt");
    parcours_tree_wrapper(ts);

    printf("\nAlice :\n");
    Tree a = make_tree("data/alice.txt");
    parcours_tree_wrapper(a);

    printf("\n====================================\ntest_parcours OK\n====================================\n");

    return EXIT_SUCCESS;
}