#include "../src/encode.h"
#include "../tests/list_tests.h"

int main() {
    for (int i = 0; i < 3; i++) {
        printf("\n - %s\n %s\n", printnames[i], filenames[i]);
        encode(filenames[i]);
        printf("%s encodé !", printnames[i]);
    }
}