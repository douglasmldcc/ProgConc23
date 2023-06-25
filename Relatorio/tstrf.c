#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Digite: %s <Nome do Arquivo>\n",argv[0]);
        return 1;
    }
    int tamanho;

    printf("Digite o tamanho do array: ");
    scanf("%d", &tamanho);

    int arrX[tamanho];
    int arrY[tamanho];
    int arrZ[tamanho];

    int ind=0;

    FILE *file = fopen(argv[1], "r"); //Abre arquivo em modo de leitura 
    int x, y, z;
    while (fscanf(file, "%d;%d;%d", &x, &y, &z) == 3) {
        
        printf("X: %d, Y: %d, Z: %d\n", x, y, z);
        arrX[ind]= x;
        arrY[ind]= y;
        arrZ[ind]= z;
        ind++;
    }

    printf("\nValores do array x:\n");

    printf("Extremos do Array X %d , %d \n", arrX[0],arrX[tamanho-1]);
    printf("Extremos do Array Y %d , %d \n", arrY[0],arrY[tamanho-1]);
    printf("Extremos do Array Z %d , %d \n", arrZ[0],arrZ[tamanho-1]);

    if (!feof(file)) {
        printf("Formato Invalido.\n");
    }

    fclose(file); // Fecha o arquivo

    return 0;
}