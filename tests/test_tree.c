#include "../src/tree.h"
#include <stdio.h>
#include <stdlib.h>


int main() {
    printf("\n====================================\nDébut test_tree\n====================================\n");
    
    printf("This :\n");
    make_tree("data/this.txt");

    printf("Texte simple :\n");
    make_tree("data/textesimple.txt");

    printf("\nAlice :\n");
    make_tree("data/alice.txt");

    printf("\n====================================\ntest_tree OK\n====================================\n");

    return EXIT_SUCCESS;
}