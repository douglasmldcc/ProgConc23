/*TAREFA LAB 1 - Atividade 2
 Implementar o seu primeiro programa concorrente!
	Escreva um programa com duas, para multiplicar por 2 cada elemento de um vetor de 10000 elementos.(Para
cada elemento ai do vetor, calcular o novo valor e escrever o resultado na mesma posicao do elemento.)
*/
 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define VETOR 10000  // Variavel Global para o tamanho do vetor
#define THREADS 2  // Variavel Global definindo o numero de threads
#define FATOR 2 // Variavel Global definindo o fator de multiplicacao

int vetor[VETOR]; 

// funcao executada pela thread,  multiplica por 2 o valor lido e substitui o valor na posicao
void *mult_vet(void *thread_id) {

  for(long i = (long) thread_id; i < VETOR; i+=THREADS){
	vetor[i] = vetor[i]*FATOR;
  }

  pthread_exit(NULL);
}


int main() {
  printf("Tamanho do Vetor = %d \n", VETOR);
  printf("Threads trabalhando = %d\n",THREADS);
  printf("Multiplicacao fator = %dx\n\n",FATOR);

  //preenchendo vetor com valores aleatorios
  srand(time(NULL));
  for(int i=0; i < VETOR; i++){
	//Coloca  numeros  aleatorios entre 0 e 9 
   	vetor[i] = rand()%10;
  }

  // Imprime os ultimos 10 valores no vetor
  printf("Valores do vetor original \n(%d)... ",VETOR-10);
  for(int i = VETOR - 10; i < VETOR; i ++) {
        printf("%d ", vetor[i]);
  }
  printf("\n");

  pthread_t threads[THREADS];

  for (long i = 0; i < THREADS; i++) {
    pthread_create(&threads[i], NULL, mult_vet, (void *) i);
  }

  for (int i = 0; i < THREADS; i++) {
    pthread_join(threads[i], NULL);
  }

  // Imprimindo os ultimo 10 valores do vetor 
  printf("Novos valores atribuidos ao vetor \n(%d)... ",VETOR-10);
  for(int i = VETOR - 10; i < VETOR; i ++) {
        printf("%d ", vetor[i]);
  }
  printf("\n");

  return 0;
}
