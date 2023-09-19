/*---------------------------------------
UNIVERSIDAD DEL VALLE DE GUATEMALA
CC3056 - Programacion de Microprocesadores
Modificado por: Kimberly Barrera
Fecha: 08/11/2019
Mod:   09/12/23

argumentos1.cpp
Comparte a subrutina argumentos en es-
tructura con elementos de múltpiple 
tipo, hacia el thread creado
---------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define num_th 100

// Define una estructura para los parametros del hilo
struct parameters {
    int id;
    float val1;
    float val2;
};

// Esta funcion se ejecutara en cada hilo
void *calculate(void *arg) {
    // Convierte el puntero void nuevamente a un puntero a parameters
    struct parameters *ps = (struct parameters *)arg;
    float res;

    // Realiza algun calculo simple (multiplicacion)
    res = ps->val1 * ps->val2;
    
    // Imprime el resultado junto con el ID del hilo
    printf("Thread %d resultado %f\n", ps->id, res);
    
    // El hilo llama a pthread_exit al finalizar su ejecución
    pthread_exit(NULL);
	return(NULL);
}

int main() {
    pthread_t thread[num_th];
    int i;
    
    // Declarar un arreglo de estructuras para almacenar los parametros
    struct parameters params[num_th];
    
    // Inicializar y crear los hilos
    for (i = 0; i < num_th; i++) {
        params[i].id = i;
        params[i].val1 = i;
        params[i].val2 = i - 1;
        
        // Crear y ejecutar el hilo con los parametros correspondientes
        if (pthread_create(&thread[i], NULL, calculate, (void *)&params[i]) != 0) {
            perror("Error al crear el hilo");
            exit(1);
        }
    }

    // Esperar a que todos los hilos terminen
    for (i = 0; i < num_th; i++) {
        pthread_join(thread[i], NULL);
    }

    printf("\n--- Fin ---\n");

    return 0;
}

