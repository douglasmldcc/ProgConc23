/* Disciplina: Computacao Concorrente */
/* Prof.: Silvana Rossetto */
/* Laboratório: 5 */
/* Codigo: Uso de variáveis de condição e suas operações básicas para sincronização por condição */

/***** Condicao logica da aplicacao: projetar e implementar um programa concorrente onde a ordem de execução
das threads é controlada no programa, usando variáveis de condição.*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NTHREADS 5

pthread_mutex_t x_mutex;
pthread_cond_t x_cond, y_cond;
int x = 0;


/* Threads 1 */
void* T1 (void* t){
    printf(" Oi Maria!\n");

    pthread_mutex_lock(&x_mutex);
    x++;
    pthread_cond_broadcast(&y_cond);
    pthread_mutex_unlock(&x_mutex);
    pthread_exit(NULL);

}
/* Threads 2 */
void* T2 (void* t){
    printf(" Oi José!\n");

    pthread_mutex_lock(&x_mutex);
    x++;
    pthread_cond_broadcast(&y_cond);
    pthread_mutex_unlock(&x_mutex);
    pthread_exit(NULL);

}
/* Threads 3 */
void* T3 (void* t){
    pthread_mutex_lock(&x_mutex);
    while(x < 2){
        pthread_cond_wait(&y_cond, &x_mutex);
    }
    x++;
    printf(" Sente-se por favor.\n");
    pthread_cond_signal(&x_cond);
    pthread_mutex_unlock(&x_mutex);
    pthread_exit(NULL);
}
/* Threads 4 */
void* T4 (void* t){
    pthread_mutex_lock(&x_mutex);
    while(x<3){
        pthread_cond_wait(&x_cond, &x_mutex);
    }
    x++;
    printf(" Até mais José!\n");
    pthread_cond_signal(&x_cond);
    pthread_mutex_unlock(&x_mutex);
    pthread_exit(NULL);
}
/* Threads 5 */
void* T5 (void* t){
    pthread_mutex_lock(&x_mutex);
    while(x<3){
        pthread_cond_wait(&x_cond, &x_mutex);
    }
    x++;
    printf(" Até mais Maria!\n");
    pthread_cond_signal(&x_cond);
    pthread_mutex_unlock(&x_mutex);
    pthread_exit(NULL);
}

/* Funcao principal */
int main(int argc, char *argv[]) {
  int i;
  pthread_t threads[NTHREADS];

  /* Inicilaiza o mutex (lock de exclusao mutua) e a variavel de condicao */
  pthread_mutex_init(&x_mutex, NULL);
  pthread_cond_init (&x_cond, NULL);
  pthread_cond_init(&y_cond, NULL);

  /* Cria as threads */
  pthread_create(&threads[0], NULL, T5, NULL);
  pthread_create(&threads[1], NULL, T4, NULL);
  pthread_create(&threads[2], NULL, T3, NULL);
  pthread_create(&threads[3], NULL, T2, NULL);
  pthread_create(&threads[4], NULL, T1, NULL);

  /* Espera todas as threads completarem */
  for (i = 0; i < NTHREADS; i++) {
    pthread_join(threads[i], NULL);
  }

  /* Desaloca variaveis e termina */
  pthread_mutex_destroy(&x_mutex);
  pthread_cond_destroy(&x_cond);
  pthread_cond_destroy(&y_cond);

}
