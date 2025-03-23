#ifndef ENCODE
#define ENCODE

int compress_file(char* filename, int** out);
char* get_file_name(char* filename);
void write_comp(char* filename);
void encode(char* filename);

#endif