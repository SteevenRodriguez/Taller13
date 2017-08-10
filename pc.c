#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
void *producor(void*args);
void *consumidor(void*args);
pthread_mutex_t mutex;
pthread_cond_t qnempty;
pthread_cond_t qnfull;



int cola = 0;
int producido = 0;
int items_total = 0;
int size_cola =0;

void *productor(void* args){
    while(items_total>producido){
         pthread_mutex_lock(&mutex);
         while(cola<size_cola-1){
            pthread_cond_wait(&qnfull,&mutex);           
         }
         cola++;
         pthread_mutex_unlock(&mutex);
         pthread_cond_signal(&qnempty);
    }

}

void *consumidor(void* args){
    while(items_total>producido || cola>0 ){
         pthread_mutex_lock(&mutex);
         while(cola<size_cola-1){
            pthread_cond_wait(&qnempty,&mutex);           
         }
         cola--;
         pthread_mutex_unlock(&mutex);
         pthread_cond_signal(&qnfull);
    }

}

int main(int argc, char** argv){

 if( argc!=7 ){
    printf("Numero de argumentos incorrectos");
    return -1;
}
 pthread_mutex_init(&mutex, NULL);	
  pthread_cond_init(&qnfull, NULL);		/* Initialize consumer condition variable */
  pthread_cond_init(&qnempty, NULL);		/* Initialize producer condition variable */


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

int h,j;
pthread_t * id_prod = (pthread_t*) malloc(sizeof(pthread_t)*num_prod);
pthread_t * id_cons = (pthread_t*) malloc(sizeof(pthread_t)*num_cons);

for(h=0;h<num_prod;h++){
	pthread_create(&id_prod[h],NULL,productor,NULL);

}
for(j=0;j<num_cons;j++){
	pthread_create(&id_cons[j],NULL,consumidor,NULL);

}

for(h=0;h<num_prod;h++){
	pthread_join(&id_prod[h], NULL);
  

}
for(j=0;j<num_cons;j++){
	pthread_join(&id_cons[j], NULL);

}

return 1;
}
