/*---------------------------------------
UNIVERSIDAD DEL VALLE DE GUATEMALA
CC3086 - Programacion de Microprocesadores
Modificado por: Kimberly Barrera
Fecha: 08/11/2019
Mod:   09/12/2023

test_self.cpp
Hilo realiza rutina para impresión de 
thread id 
---------------------------------------*/

#include <stdio.h> 
#include <stdlib.h> 
#include <pthread.h>

//using namespace std;

// Esta función se ejecutará en el nuevo hilo.
void *PrintID(void *threadid) {
   printf("Subrutina - Thread ID, %ld", pthread_self());
   printf("\n");
   pthread_exit(NULL);
   return NULL;
}

int main () {
    pthread_t threads;
    int rc;
   
    printf("\n--- MAIN() : CREATING NEW THREAD ---");

    // Crear un nuevo hilo.
    rc = pthread_create(&threads, NULL, PrintID, NULL);

    // Imprimir el ID del hilo principal (principal).
    printf("\nMain - Thread ID, %ld\n",threads);
    
    // Esperar a que el hilo recién creado termine.
    pthread_join(threads, NULL); 

    // Salir del programa.
    pthread_exit(NULL);
}
