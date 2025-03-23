#include "../src/encode.h"
#include <stdio.h>
#include <stdlib.h>
#include "./list_tests.h"


int main() {
    printf("\n====================================\nDébut test_encode\n====================================\n");
    
    for (int i = 0; i < 5; i++) {
        printf("\n - %s\n", printnames[i]);
        encode(filenames[i]);
    }

    printf("\n====================================\ntest_encode OK\n====================================\n");

    return EXIT_SUCCESS;
}