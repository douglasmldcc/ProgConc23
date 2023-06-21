#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Please provide a file name as a command-line argument.\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r"); // Open the file in read mode
    int x, y, z;
    while (fscanf(file, "%d;%d;%d", &x, &y, &z) == 3) {
        printf("X: %d, Y: %d, Z: %d\n", x, y, z);
    }

    if (!feof(file)) {
        printf("Invalid line format.\n");
    }

    fclose(file); // Close the file

    return 0;
}