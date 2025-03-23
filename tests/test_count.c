#include "../src/alphabet.h"
#include <stdio.h>
#include <stdlib.h>
#include "./list_tests.h"


int main() {
    printf("\n====================================\nDébut test_count\n====================================\n");

    for (int i = 0; i < 5; i++) {
        printf("%s\n", printnames[i]);
        FrequencySize fs1 = count_frequency(filenames[i]);
        for (int i = 0; i < fs1.size; i++) {
            printf("%c : %d\n", fs1.array[i].character, fs1.array[i].count);
        }
    }

    printf("\n====================================\ntest_count OK\n====================================\n");

    return EXIT_SUCCESS;
}