#ifndef ENCODE
#define ENCODE

#include "parcours.h"
#include "alphabet.h"

int compress_file(char* filename, int** out);
char* get_file_name(char* filename);
void write_comp(char* filename, char* output_filename);
void write_freq(char* filename, char* output_filename);
void compare_file_sizes(char* original_filename, char* bin_filename, char* txt_filename);
void encode(char* filename);

#endif