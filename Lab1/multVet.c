/*TAREFA LAB 1 - Implementar o seu primeiro programa concorrente!
	Escreva um programa com duas, para multiplicar por 2 cada elemento de um vetor de 10000 elementos.(Para
cada elemento ai do vetor, calcular o novo valor e escrever o resultado na mesma posicao do elemento.)
*/

#include <stdio.h>
#include <pthread.h>

// funcao executada pela thread,  multiplica por 2 o valor lido e substitui o valor na posicao
void *mult_vet(void *thread_id) {
  printf("Hello, World! from thread %ld\n", (long) thread_id);
  pthread_exit(NULL);
}

int main() {
  int x;
  int x_off;
  printf("Escolha quantidade de threads \n");
  scanf("%d",x);
  x_off = x-1;;
  pthread_t threads[x_off];

  for (long i = 0; i < x_off; i++) {
    pthread_create(&threads[i], NULL, mult_vet, (void *) i);
  }

  for (int i = 0; i < x_off; i++) {
    pthread_join(threads[i], NULL);
  }

  return 0;
}
