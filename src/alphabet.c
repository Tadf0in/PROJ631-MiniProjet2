#include "alphabet.h"

#include <stdio.h>
#include <stdlib.h>


/**
 * Fonction qui cherche si un caractère a déjà été compté
 * 
 * @param array Tableau dans lequel chercher
 * @param size Taille du tableau
 * @param c Caractère à chercher
 * 
 * @return Indice du caractère dans le tableau, -1 si pas présent
 */
int find_char(Frequency* array, int size, char c) {
    for (int i = 0; i < size; i++) {
        if (array[i].character == c) {
            return i;
        }
    }
    return -1;
}


/**
 * Fonction de comparaison pour `qsort`. Trie par fréquence, puis par ordre alphabétique suivant la table ASCII si fréquence égale
 * 
 * @param a Caractère 1
 * @param b Caractère 2
 * 
 * @return Une entier < 0 si a avant b, > 0 sinon
 */
int compare_frequency(const void* a, const void* b) {
    Frequency* freq_a = (Frequency*)a;
    Frequency* freq_b = (Frequency*)b;

    // Si fréquence égale, tri par ordre alphabétique selon ASCII
    if (freq_b->count == freq_a->count) {
        return freq_a->character - freq_b->character;
    } 
    // Sinon tri par fréquence
    else {
        return freq_b->count - freq_a->count;
    }
}


/**
 * Compte la fréquence d'apparition de chaque caractère dans le texte
 * 
 * @param filename Chemin vers le fichier texte
 */
FrequencySize count_frequency(char* filename) {
    FILE* file = fopen(filename, "r");

    // Initialise le tableau
    FrequencySize fs;
    fs.array = NULL;
    fs.size = 0;
    
    if (file == NULL) {
        printf("Error opening file %s\n", filename);
    } else {
        char c;
        while ((c = fgetc(file)) != EOF) { // Parcours le texte caractère par caractère

            int index = find_char(fs.array, fs.size, c);
            
            // 1ère fois qu'on rencontre ce caractère 
            if (index == -1) {
                fs.size++;
                fs.array = realloc(fs.array, fs.size * sizeof(Frequency)); // Réalloue la mamoire dynamiquement
                fs.array[fs.size - 1].character = c;
                fs.array[fs.size - 1].count = 1;
            } 
            // Sinon juste on incrémente
            else {
                fs.array[index].count++;
            }
        }

        fclose(file);

        // Trie la liste
        qsort(fs.array, fs.size, sizeof(Frequency), compare_frequency);
    }
    
    // free(fs.array);
    return fs;
}