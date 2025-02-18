#ifndef ALPHABET
#define ALPHABET

typedef struct {
    char character;
    int count;
} Frequency;

typedef struct {
    Frequency* array;
    int size;
} FrequencySize;

char* read_file(char* filename);
FrequencySize count_frequency(char* filename);
int compare_frequency(const void* a, const void* b);

#endif