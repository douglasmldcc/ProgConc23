#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Please provide a file name as a command-line argument.\n");
        return 1;
    }
    if (argc < 3) {
        printf("Please provide a file size as a command-line argument.\n");
        return 1;
    }
    FILE *file = fopen(argv[1], "w"); // Open the file in write mode

    if (file == NULL) {
        printf("Error opening the file.\n");
        return 1;
    }
    int x=0;
    int size = argv[2];

    fprintf(file, "10;20;30\n");
    fprintf(file, "40;50;60\n");
    fprintf(file, "70;80;90\n");
    fprintf(file, "%d;%d;%d\n", x, x+1,x+2);

    printf("%d\n", size );
    
    for(int i=0; i < 5; i++ ){
        fprintf(file, "%d;%d;%d\n", i, i+1,i+2);
    } 

    fclose(file); // Close the file

    printf("Data written to file successfully.\n");

    return 0;
}