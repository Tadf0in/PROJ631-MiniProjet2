#include "../src/alphabet.h"
#include <stdio.h>
#include <stdlib.h>


int main() {
    printf("\n====================================\nDébut test_count\n====================================\n");
    
    printf("Texte simple :\n");
    FrequencySize fs1 = count_frequency("data/textesimple.txt");
    for (int i = 0; i < fs1.size; i++) {
        printf("%c : %d\n", fs1.array[i].character, fs1.array[i].count);
    }

    printf("\nAlice :\n");
    FrequencySize fs2 = count_frequency("data/alice.txt");
    for (int i = 0; i < fs2.size; i++) {
        printf("%c : %d\n", fs2.array[i].character, fs2.array[i].count);
    }

    printf("\n====================================\ntest_count OK\n====================================\n");

    return EXIT_SUCCESS;
}