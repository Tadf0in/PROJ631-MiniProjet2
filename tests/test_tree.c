#include "../src/tree.h"
#include <stdio.h>
#include <stdlib.h>
#include "./list_tests.h"


int main() {
    printf("\n====================================\nDébut test_tree\n====================================\n");
    
    for (int i = 0; i < 5; i++) {
        printf("%s\n", printnames[i]);
        // fs = c
        make_tree(filenames[i]);
    }

    printf("\n====================================\ntest_tree OK\n====================================\n");

    return EXIT_SUCCESS;
}