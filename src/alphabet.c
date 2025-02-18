#include "alphabet.h"

#include <stdio.h>
#include <stdlib.h>


typedef struct {
    char character;
    int count;
} Frequency;


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
 * Compte la fréquence d'apparition de chaque caractère dans le texte
 * 
 * @param filename Chemin vers le fichier texte
 */
void count_frequency(char* filename) {
    FILE* file = fopen(filename, "r");

    if (file == NULL) {
        printf("Error opening file %s\n", filename);
        return;
    } else {
        // Initialise le tableau
        Frequency* frequency_dict = NULL;
        int size = 0;

        char c;
        while ((c = fgetc(file)) != EOF) { // Parcours le texte caractère par caractère
            
            // Ignore les tabulation et retour à la ligne
            // if (c < 32 || c == 127) continue;

            int index = find_char(frequency_dict, size, c);
            
            // 1ère fois qu'on rencontre ce caractère 
            if (index == -1) {
                size++;
                frequency_dict = realloc(frequency_dict, size * sizeof(Frequency)); // Réalloue la mamoire dynamiquement
                frequency_dict[size - 1].character = c;
                frequency_dict[size - 1].count = 1;
            } 
            // Sinon juste on incrémente
            else {
                frequency_dict[index].count++;
            }
        }

        fclose(file);

        for (int i = 0; i < size; i++) {
            printf("%c : %d\n", frequency_dict[i].character, frequency_dict[i].count);
        }
    
        free(frequency_dict);
    }
}