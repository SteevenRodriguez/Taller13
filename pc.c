#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
int items_total=0;
int size_cola=0;

void* producer(void *ptr) {
  int i;

  
    pthread_mutex_lock(&the_mutex);	/* protect buffer */
    while (buffer != 0)		       /* If there is something 
					  in the buffer then wait */
      pthread_cond_wait(&condp, &the_mutex);
    buffer = i;
    pthread_cond_signal(&condc);	/* wake up consumer */
    pthread_mutex_unlock(&the_mutex);	/* release the buffer */
  }
  pthread_exit(0);




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
