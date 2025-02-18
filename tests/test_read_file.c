#include "../src/alphabet.h"
#include <stdio.h>
#include <stdlib.h>


int main() {
    printf("\n====================================\nDébut test_read_file\n====================================\n");
    
    char* content = read_file("data/textesimple.txt");
    if (content != NULL) {
        printf("%s\n", content);
        free(content);
    }

    printf("\n====================================\ntest_read_file OK\n====================================\n");

    return EXIT_SUCCESS;
}