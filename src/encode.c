#include "encode.h"

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


void write_comp(char* filename, char* output_filename) {
    int* compressed = NULL;
    int size = compress_file(filename, &compressed);

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
                // printf("buffer : %d\n", buffer);
                fwrite(&buffer, sizeof(unsigned char), 1, output_file);
                buffer = 0;
                bit_count = 0;
            }
        }

        // A la fin si on rempli le dernier octet avec des 0
        if (bit_count > 0) {
            buffer = buffer << (8 - bit_count);
            // printf("buffer : %d\n", buffer);
            fwrite(&buffer, sizeof(unsigned char), 1, output_file);
        }

        fclose(output_file);
    }
    free(compressed);
}


void write_freq(char* filename, char* output_filename) {
    FrequencySize fs = count_frequency(filename);

    FILE* output_file = fopen(output_filename, "w");
    if (output_file == NULL) {
        perror("Erreur lors de l'ouverture du fichier de sortie");
    } else {
        fprintf(output_file, "%d\n", fs.size);
        for (int i = 0; i < fs.size-1; i++) {
            fprintf(output_file, "%c : %d\n", fs.array[i].character, fs.array[i].count);
        }
        fprintf(output_file, "%c : %d", fs.array[fs.size-1].character, fs.array[fs.size-1].count); // Derniere ligne sans \n
        fclose(output_file);
    }
    free(fs.array);
}


void compare_file_sizes(char* original_filename, char* compressed_filename, char* freq_filename) {
    FILE* original_file = fopen(original_filename, "rb");
    FILE* compressed_file = fopen(compressed_filename, "rb");
    FILE* freq_file = fopen(freq_filename, "rb");

    if (original_file == NULL || compressed_file == NULL || freq_file == NULL) {
        perror("Erreur lors de l'ouverture des fichiers pour comparaison");
        if (original_file != NULL) fclose(original_file);
        if (compressed_file != NULL) fclose(compressed_file);
        if (freq_file != NULL) fclose(freq_file);
        return;
    }

    fseek(original_file, 0, SEEK_END);
    fseek(compressed_file, 0, SEEK_END);
    fseek(freq_file, 0, SEEK_END);

    long original_size = ftell(original_file);
    long compressed_size = ftell(compressed_file);
    long freq_size = ftell(freq_file);

    fclose(original_file);
    fclose(compressed_file);

    printf("\nTaille du fichier original : %ld octets\n", original_size);
    printf("Taille du fichier compressé : %ld octets\n", compressed_size);
    printf("Taille du fichier de fréquences : %ld octets\n", freq_size);

    if (original_size > 0) {
        double ratio = (double) (original_size - compressed_size) / original_size;
        printf("\nTaux de compression (fichier compressé uniquement) : %.2f%%\n", ratio*100);

        long total_new_size = compressed_size + freq_size;
        double total_ratio = (double) (original_size - total_new_size) / original_size;
        printf("Taux de compression total : %.2f%%\n", total_ratio*100);
    } else {
        printf("Impossible de calculer le taux de compression (taille originale = 0).\n");
    }
}


void encode(char* filename) {
    char* name = get_file_name(filename);

    // Écrit le fichier compressé
    char compressed_filename[256];
    snprintf(compressed_filename, sizeof(compressed_filename), "out/%s_comp.bin", name);
    printf("bin filename : %s\n", compressed_filename);
    
    write_comp(filename, compressed_filename);

    // Écrit le fichiers de fréquences
    char txt_filename[256];
    snprintf(txt_filename, sizeof(txt_filename), "out/%s_freq.txt", name);
    printf("txt filename : %s\n", txt_filename);

    write_freq(filename, txt_filename);

    // Compare les tailles des fichiers
    compare_file_sizes(filename, compressed_filename, txt_filename);
}