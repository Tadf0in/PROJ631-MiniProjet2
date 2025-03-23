#include "../src/encode.h"
#include <stdio.h>
#include <stdlib.h>
#include "./list_tests.h"


int main() {
    printf("\n====================================\nDébut test_encode\n====================================\n");
    
    for (int i = 0; i < 5; i++) {
        printf("\n - %s\n", printnames[i]);
        int* compressed = NULL;
        int size = compress_file(filenames[i], &compressed);
        for (int i=0; i<size; i++) {
            printf("%d", compressed[i]);
        }
    }

    // int* compressed = NULL;
    // printf("ok1");
    // int size = compress_file("data/this.txt", &compressed);
    // printf("ok2");
    // printf("final size : %d", size);
    // for (int i=0; i<size; i++) {
    //     printf("%d", compressed[i]);
    // }

    printf("\n====================================\ntest_encode OK\n====================================\n");

    return EXIT_SUCCESS;
}