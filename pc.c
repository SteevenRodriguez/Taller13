#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

void *productor(void*args);
void *consumidor(void*args);
pthread_mutex_t mutex;
pthread_cond_t qnempty;
pthread_cond_t qnfull;



int cola;
int producido;
int items_total;
int size_cola;
double tiempo_cons;
double tiempo_prod;

void *productor(void* args){
	int n_prd = *((int *) args);
	
	
	while(1){
		
		pthread_mutex_lock(&mutex);
		
		while(cola==size_cola){
			pthread_cond_wait(&qnfull,&mutex);  
			
		}
		if(items_total<=producido){
				pthread_mutex_unlock(&mutex);
				pthread_cond_broadcast(&qnfull);
				pthread_cond_broadcast(&qnempty);
				return 0;      
			}   
		
		usleep(tiempo_prod);
		cola++;
		producido++;
		printf("Productor %d  ha producido 1 item, tamaño cola = %d\n" ,n_prd,cola );
		
		pthread_mutex_unlock(&mutex);
		pthread_cond_broadcast(&qnempty);
	}
	return 0;

}

void *consumidor(void* args){
	int n_cons = *((int *) args);
	
    while(1){
         pthread_mutex_lock(&mutex);
	if(items_total<=producido && cola<=0 ){
		pthread_mutex_unlock(&mutex);
         	pthread_cond_broadcast(&qnfull);
		pthread_cond_broadcast(&qnempty);
		return 0;
	}
         while(cola==0){
            pthread_cond_wait(&qnempty,&mutex);   
		if(items_total<=producido && cola<=0 ){
			pthread_mutex_unlock(&mutex);
		 	pthread_cond_broadcast(&qnfull);
			pthread_cond_broadcast(&qnempty);
		return 0;
		}
         }
	
	usleep(tiempo_cons);
         cola--;
	printf("Consumidor %d ha consumido 1 item, tamaño cola = %d\n",n_cons, cola);
	
         pthread_mutex_unlock(&mutex);
         pthread_cond_broadcast(&qnfull);
    }
	return 0;

}

int main(int argc, char** argv){

	if( argc!=7 ){
		printf("Numero de argumentos incorrectos");
		return -1;
	}
	pthread_mutex_init(&mutex, NULL);	
	pthread_cond_init(&qnfull, NULL);		
	pthread_cond_init(&qnempty, NULL);		


	int num_prod=atoi(argv[1]);
	tiempo_prod=atof(argv[2]);
	int num_cons=atoi(argv[3]);
	tiempo_cons=atof(argv[4]);
	size_cola=atoi(argv[5]);
	items_total=atoi(argv[6]);
	cola =0;
	producido = 0;
	printf("Numero de productores: %d\n", num_prod);
	printf("Numero de consumidores: %d\n",num_cons);
	printf("Tamaño de la cola: %d\n", size_cola);
	tiempo_cons=tiempo_cons*1000000;
	printf("Tiempo de produccion: %0.2f\n",tiempo_cons);
	tiempo_prod=tiempo_prod*1000000;
	printf("Tiempo de produccion: %0.2f\n",tiempo_prod);

	printf("Total de ítems a producir: %d\n",items_total);
	
	int h,j;
	pthread_t id_prod[num_prod];
	pthread_t id_cons[num_cons];
	
	for(h=0;h<num_prod;h++){
		int* arg = (int *)malloc(sizeof(int));
		*arg = h+1;
		pthread_create(&id_prod[h],NULL,productor,arg);

	}
	for(j=0;j<=num_cons;j++){
		int* arg2 = (int *)malloc(sizeof(int));
		*arg2 = j+1;
		//printf("%d\n",*arg2);
		pthread_create(&id_cons[j],NULL,consumidor,arg2);

	}

	for(h=0;h<num_prod;h++){
		pthread_join(id_prod[h], NULL);
	  

	}
	for(j=0;j<num_cons;j++){
		pthread_join(id_cons[j], NULL);

	}	
		
	return 1;	
}
