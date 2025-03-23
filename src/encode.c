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


void write_comp(char* filename) {
    int* compressed = NULL;
    compress_file(filename, &compressed);
}


/**
 * Fonction qui écrit dans un fichier selon le codage de Huffman
 * 
 * @param output_filename Nom du fichier de sortie
 */
// void encode_file(char* filename) {
//     Tree tree = make_tree(filename);

//     // Obtenir les chemins pour chaque caractère
//     Path* paths = parcours_tree_wrapper(tree);

//     // Ouvrir le fichier d'entrée
//     FILE* input_file = fopen(input_filename, "r");
//     if (input_file == NULL) {
//         perror("Erreur lors de l'ouverture du fichier d'entrée");
//         free(paths);
//         return;
//     }

//     // Ouvrir le fichier de sortie
//     FILE* output_file = fopen(output_filename, "wb");
//     if (output_file == NULL) {
//         perror("Erreur lors de l'ouverture du fichier de sortie");
//         fclose(input_file);
//         free(paths);
//         return;
//     }

//     // Lire le fichier d'entrée et encoder les caractères
//     int c;
//     while ((c = fgetc(input_file)) != EOF) {
//         for (int i = 0; i < tree->nb_leaves; i++) {
//             if (paths[i].character == c) {
//                 for (int j = 0; j < paths[i].size; j++) {
//                     fputc(paths[i].path[j] + '0', output_file); // Écrire les bits sous forme de caractères
//                 }
//                 break;
//             }
//         }
//     }

//     // Libérer la mémoire et fermer les fichiers
//     for (int i = 0; i < tree->nb_leaves; i++) {
//         free(paths[i].path);
//     }
//     free(paths);
//     fclose(input_file);
//     fclose(output_file);
// }