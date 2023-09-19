/*---------------------------------------
UNIVERSIDAD DEL VALLE DE GUATEMALA
CC3086 - Programacion de Microprocesadores
Modificado por: Kimberly Barrera

Fecha:   09/12/2023

retorno.cpp
Comparte desde subrutina argumento puntero
de tipo void, por medio de return.
---------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

void *calculos(void* argument){
	
	int input, output;
	
	input = (int)(intptr_t) argument;	
	output = input*2;
	
	return (void*)(intptr_t) output;
}
int main(){

	printf("\n\n");
	pthread_t thread_id;
	pthread_attr_t attr;

	//declara el atributo con el valor predeterminado de la implementación
	pthread_attr_init (&attr);
	//declara si el hilo es creado en un estado detached o no, en caso lo sea uiliza el ID más reciente creado por pthread_join
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);
	
	//se declara el puntero que permite pasar el argumento para cada hilo
	void *exit_value;
	unsigned int result = 1;
	
	/**
	 * Al remover el segundo for y poner pthread_create y pthread_join en el mismo segmento
	 * se logra el buen funcionamiento del programa
	 * Lo que causa error es que primero se crean todos los hilos y al finalizar pthread_join
	 * toma el último hilo solamente y corre solo con ese 
	 * 
	*/
	
	for(int i = 0; i < 10; i++){
		//se crea los hilos que se utilizarán en la subrutina
		pthread_create(&thread_id, &attr, calculos, (void*) (intptr_t) i);

	}
	
	for(int i = 0; i < 10; i++){
		//exit_value es la dirección donde se almacenará el valor retornado de la subrutina
		pthread_join(thread_id, &exit_value);
		
		//se utiliza el valor retornado para usarlo en el main (se especifica qué tipo será)
		int result =(int)(intptr_t)exit_value;
		printf("Resultado multiplicación es: %d\n", result);
	}
	
	pthread_attr_destroy(&attr);
	pthread_exit(NULL);
	return 0;
	
}


