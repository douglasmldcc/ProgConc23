#include <stdio.h>
#include <stdlib.h>

int main(){
    int cont = 10;
    int estado;
    while (cont>10){
        estado=estado+1;
        if(estado%5){
             printf("funA");
             }
        else{
             printf("funB");
             }
        cont = cont -1;
    }
}
