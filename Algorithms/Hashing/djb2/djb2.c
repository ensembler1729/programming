#include <stdio.h>
#include <stdlib.h>


unsigned long hash(unsigned char *str);

int main(int argc, char *argv[]) {

    if(argc != 2) {
        printf("Error: Only 1 argument is expected!\n");
        return -1;
    }

    printf("Calculating DJB2 hash....\n");

    unsigned long result = hash(argv[1]);
    printf("Hashed Value: %lu\n", result);
    return 0;
}

unsigned long hash(unsigned char *str) {

    unsigned long hash = 5381;
    int c;

    while(c = *str++)
        hash = ((hash << 5) + hash) + c;

    return hash;
}
