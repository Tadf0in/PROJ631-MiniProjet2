#ifndef ENCODE
#define ENCODE

#include "parcours.h"
#include "alphabet.h"

int compress_file(char* filename, int** out);
char* get_file_name(char* filename);
void write_comp(char* filename);
void encode(char* filename);

#endif