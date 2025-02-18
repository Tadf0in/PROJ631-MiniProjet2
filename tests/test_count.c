#include "../src/alphabet.h"
#include <stdio.h>
#include <stdlib.h>


int main() {
    printf("\n====================================\nDébut test_count\n====================================\n");
    
    count_frequency("data/textesimple.txt");

    printf("\n====================================\ntest_count OK\n====================================\n");

    return EXIT_SUCCESS;
}