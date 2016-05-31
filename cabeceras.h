#include "stdio.h"
#include "stdlib.h"
#include "string.h"

//MACROS
#define TRUE 1
#define TAM 100

//Funciones
void modulo1(void);
void modulo2(void);
void modulo3(void);
const char * leerArchivo(char *);


const char * leerArchivo(char * nombre_archivo){
	//Apertura y lectura del archivo pasado por parametro
	FILE *archivo;
 	char* contenido = malloc(sizeof(archivo));
 	archivo = fopen ( nombre_archivo, "r" );
 	fscanf(archivo, "%s" ,contenido);
 	fclose (archivo);
 	//Cierre del archivo

 	//Retorno del contenido del archivo
 	return contenido; 
}