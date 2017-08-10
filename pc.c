#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
int items_total=0;
int size_cola=0;


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

printf("Numero de productores: %d/n", num_prod);
printf("Numero de consumidores: %d/n",num_cons);
printf("Tamaño de la cola %d/n", size_cola);
tiempo_cons=tiempo_cons*1000;
printf("Tiempo de produccion: %f",tiempo_cons);
tiempo_prod=tiempo_prod*1000;
printf("Tiempo de produccion: %f",tiempo_prod);

printf("Total de ítems a producir: %d",items_total);




}
