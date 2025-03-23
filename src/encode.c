#include "parcours.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Fonction qui compresse chaque caractère d'un texte selon le codage de Huffmann
 * 
 * @param filename Fichier à compresser
 * @param out Tableau d'entiers qui contiendra le texte compressé
 * 
 * @return int Taille du tableau
 */
int compress_file(char* filename, int** out) {
    int out_i = 0;

    Tree* tree = (Tree*) malloc(sizeof(Tree));
    tree[0] = make_tree(filename);
    Path* paths = parcours_tree_wrapper(tree);

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file %s\n", filename);
    } else {
        char c;
        while ((c = fgetc(file)) != EOF) { // Parcours le texte caractère par caractère$
            for (int i = 0; i < 256; i++) {
                if (paths[i].character == c) {
                    // Ajoute à la suite l'encodage du caractère
                    *out = (int*) realloc(*out, (out_i + paths[i].size) * sizeof(int));
                    for (int j = 0; j < paths[i].size; j++) {
                        (*out)[out_i] = paths[i].path[j];
                        out_i++;
                    }
                    break;
                }
            }
        }
        fclose(file);
    }
    free_paths(paths, tree->nb_leaves);
    free_tree(tree);
    
    return out_i;
}


char* get_file_name(char* filename) {
    // Enleve le 'data/'
    char* name = strrchr(filename, '/');
    if (name != NULL) {
        name++;
    } else {
        name = filename;
    }
    
    // Enleve le '.txt'
    char* dot = strrchr(name, '.');
    if (dot != NULL) {
        int len = dot - name;
        char* temp = (char*) malloc((len + 1) * sizeof(char));
        if (temp != NULL) {
            strncpy(temp, name, len);
            temp[len] = '\0';
            name = temp;
        }
    }
    return name;
}


void write_comp(char* filename) {
    int* compressed = NULL;
    int size = compress_file(filename, &compressed);

    char output_filename[256];
    char* name = get_file_name(filename);
    snprintf(output_filename, sizeof(output_filename), "out/%s_comp.bin", name);
    printf("\noutfilename : %s\n", output_filename);

    FILE* output_file = fopen(output_filename, "wb");
    if (output_file == NULL) {
        perror("Erreur lors de l'ouverture du fichier de sortie");
    } else {        
        unsigned char buffer = 0;
        int bit_count = 0;

        for (int i = 0; i < size; i++) {
            // Ajoute le bit de poids faible à la suite buffer
            buffer = (buffer << 1) | (compressed[i] & 1); 
            bit_count++;

            // Dès qu'on octet est rempli, on l'écrit dans le fichier puis on reset le buffer
            if (bit_count == 8) {
                printf("buffer : %d\n", buffer);
                fwrite(&buffer, sizeof(unsigned char), 1, output_file);
                buffer = 0;
                bit_count = 0;
            }
        }

        // A la fin si on rempli le dernier octet avec des 0
        if (bit_count > 0) {
            buffer = buffer << (8 - bit_count);
            printf("buffer : %d\n", buffer);
            fwrite(&buffer, sizeof(unsigned char), 1, output_file);
        }

        fclose(output_file);
    }
    free(compressed);
}


void encode(char* filename) {
    write_comp(filename);
}