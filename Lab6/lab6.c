#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <semaphore.h>

#define N 5 //tamanho do buffer
#define P N //qtde de threads produtoras
#define C N //qtde de threads consumidoras

//variaveis do problema
int Buffer[N]; //espaco de dados compartilhados
int count; 

sem_t slotCheio, slotVazio;     //semaforos para sincronizar a ordem de execucao das threads
sem_t mutexProd, mutexCons;     //exclusão mutua

//inicializa o buffer
void IniciaBuffer(int n) {
  int i;
  for(i=0; i<n; i++)
    Buffer[i] = 0;
}

//imprime o buffer
void ImprimeBuffer(int n) {
  int i;
  for(i=0; i<n; i++)
    printf("%d ", Buffer[i]);
  printf("\n");
}

//insere elementos no buffer ate que fique cheio
void Insere (int item, int id) {
    static int in = 0;
    //aguarda slot vazio
    sem_wait(&slotVazio);
    //exclusao mutua entre produtores
    sem_wait(&mutexProd);
    printf("P[%d] quer inserir\n", id);
    for(int i=0; i<N; i++){
        Buffer[in] = item;
        in = (in + 1)%N;
        //sinaliza um slot cheio
        sem_post(&slotCheio);
        count++;
    }
    printf("P[%d] inseriu\n", id);
    ImprimeBuffer(N);
    //exclusao mutua entre produtores
    sem_post(&mutexProd);

}

int Retira (int id) {
    int item;
    static int out = 0;
    //aguarda slot cheio
    sem_wait(&slotCheio);
    //exclusão mutua entre consumidores
    sem_wait(&mutexCons);

    printf("C[%d] quer consumir\n", id);

    item = Buffer[out];
    Buffer[out] = 0;
    out = (out + 1)%N;
    count--;
    printf("C[%d] consumiu %d\n", id, item);
    ImprimeBuffer(N);
    //exclusão mutua entre consumidores
    sem_post(&mutexCons);
    if(count==0){
        //sinaliza um slot vazio
        sem_post(&slotVazio);
    }
    return item;
}

//thread produtora
void * produtor(void * arg) {
    int *id = (int *) arg;
    printf("Sou a thread produtora %d\n", *id);
    while(1) {
        //produzindo o item
        Insere(*id, *id);
        sleep(1);
    } 
    free(arg);
    pthread_exit(NULL);
}

//thread consumidora
void * consumidor(void * arg) {
    int *id = (int *) arg;
    int item;
    printf("Sou a thread consumidora %d\n", *id);
    while(1) {
        //faz o processamento do item 
        item = Retira(*id);
        sleep(1); 
    } 
    free(arg);
    pthread_exit(NULL);
}

//funcao principal
int main(void) {
    //identificadores das threads
    pthread_t tid[P+C];
    int *id[P+C];

    int produz, consome;

    //aloca espaco para os IDs das threads
    for(int i=0; i<P+C;i++) {
        id[i] = malloc(sizeof(int));
        if(id[i] == NULL) exit(-1);
        *id[i] = i+1;
    }

    //inicializa o Buffer
    IniciaBuffer(N);  
    //inicia os semaforos
    sem_init(&slotCheio, 0, 0);
    sem_init(&slotVazio, 0, 1);
    sem_init(&mutexCons, 0, 1);
    sem_init(&mutexProd, 0, 1);

    //Escolhe a quantidade de threads produtoras e consumidoras
    printf("Digite o número de threads produtoras (1 a %d): ", P);
    scanf("%d", &produz);
    printf("Digite o número de threads consumidoras (1 a %d): ", C);
    scanf("%d", &consome);

    //cria as threads produtoras
    for(int i=0; i<produz; i++) {
        if(pthread_create(&tid[i], NULL, produtor, (void *) id[i])) exit(-1);
    } 
    
    //cria as threads consumidoras
    for(int i=0; i<consome; i++) {
        if(pthread_create(&tid[i+P], NULL, consumidor, (void *) id[i+P])) exit(-1);
    } 

    pthread_exit(NULL);
    return 1;
}