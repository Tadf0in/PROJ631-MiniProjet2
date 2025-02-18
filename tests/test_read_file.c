// #include "../src/alphabet.h"
#include <stdio.h>
#include <stdlib.h>

// Ancienne fonction, plus utilisée dans src donc je la garde ici
char* read_file(char* filename) {
    FILE* file = fopen(filename, "r");

    if (file == NULL) {
        printf("Error opening file %s\n", filename);
        return NULL;
    } else {
        // Récupère la taille du fichier et alloue la mémoire en conséquence
        fseek(file, 0, SEEK_END);
        long file_size = ftell(file);
        fseek(file, 0, SEEK_SET);
        char* content = (char*) malloc(file_size + 1);

        // Lis le fichier
        fread(content, 1, file_size, file);
        content[file_size] = '\0';  // Caractère pour fermer le string

        fclose(file);
        return content;
    }
}


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