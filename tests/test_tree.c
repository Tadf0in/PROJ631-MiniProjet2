#include "../src/tree.h"
#include <stdio.h>
#include <stdlib.h>


int main() {
    printf("\n====================================\nDébut test_tree\n====================================\n");
    
    printf("This :\n");
    Tree t = make_tree("data/this.txt");
    affiche_tree(t, 0);

    // printf("Texte simple :\n");
    // TreeSize ts = make_tree("data/textesimple.txt");
    // affiche_tree(ts.tree, 0);

    // printf("\nAlice :\n");
    // TreeSize a = make_tree("data/alice.txt");
    // affiche_tree(a.tree, 0);

    printf("\n====================================\ntest_tree OK\n====================================\n");

    return EXIT_SUCCESS;
}