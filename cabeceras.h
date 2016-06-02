#include "stdio.h"
#include "stdlib.h"
#include "string.h"

//MACROS
#define TRUE 1
#define TAM 5000

//Prototipos de funciones
void modulo1(void);
void modulo2(void);
void modulo3(void);
const char * leerArchivo(char *);
char *concatenar(char *, char);

//Variables
const char * error_modulo1 = "Expresión regular incorrecta.\nERROR: número incorrecto de parentesis de cierre respecto a parentesis de apertura\n";
const char * continuar = "Presione ENTER para continuar";

//Definición de funciones
const char * leerArchivo(char * nombre_archivo){
	//Apertura y lectura del archivo pasado por parametro
	FILE *archivo;
 	char* contenido = malloc(sizeof(archivo)*TAM);
 	archivo = fopen ( nombre_archivo, "r" );
 	fscanf(archivo, "%s" ,contenido);
 	fclose (archivo);
 	//Cierre del archivo

 	//Retorno del contenido del archivo
 	return contenido; 
}


char *concatenar_caracter(char *cadena, char caracter){ 
   int i;
   //Se busca el final de la cadena
   for (i = 0; cadena[i] != '\0'; i++);
   //Se añade el caracter en una posición adelante del final anterior
   cadena[i++] = caracter;
   //Se  añade el nuevo fin de la cadena
   cadena[i] = '\0';
   return cadena; 
}