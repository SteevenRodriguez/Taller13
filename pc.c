#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t qnempty = PTHREAD_COND_INITIALIZER;
pthread_cond_t qnfull = PTHREAD_COND_INITIALIZER;

int cola = 0;
int producido = 0;
int total = 0;
int limite_cola = 0

void *productor(void* args){
    while(total>producido){
         pthread_mutex_lock(&mutex);
         while(cola<limite_cola-1){
            pthread_con_wait(&qnfull,&mutex);           
         }
         cola++;
         pthread_mutex_unlock(&mutex)
         pthread_cond_signal(&qnempty);
    }

}

void *consumidor(void* args){
    while(total>producido){
         pthread_mutex_lock(&mutex);
         while(cola<limite_cola-1){
            pthread_con_wait(&qnempty,&mutex);           
         }
         cola++;
         pthread_mutex_unlock(&mutex)
         pthread_cond_signal(&qnfull);
    }

}

int main(int argc, char** argv){

 if( argc<7 ){
    printf("Numero de argumentos incorrectos");
    return -1;
}

int num_prod=atoi(argv[1]);
double tiempo_prod=atof(argv[2]);
int num_cons=atoi(argv[3]);
double tiempo_cons=atof(argv[4]);
size_cola=atoi(argv[5]);
items_total=atoi(argv[6]);
int cola=0;

printf("Numero de productores: %d\n", num_prod);
printf("Numero de consumidores: %d\n",num_cons);
printf("Tamaño de la cola: %d\n", size_cola);
tiempo_cons=tiempo_cons*1000;
printf("Tiempo de produccion: %0.2f\n",tiempo_cons);
tiempo_prod=tiempo_prod*1000;
printf("Tiempo de produccion: %0.2f\n",tiempo_prod);

printf("Total de ítems a producir: %d\n",items_total);




}
