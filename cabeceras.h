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
const char * leerArchivoCompleto(char *);
char *concatenar(char *, char);

//Variables
const char * error_parentesis = "\n\n\nERROR DE SINTAXIS: número incorrecto de parentesis de cierre respecto a parentesis de apertura\n";
const char * error_apertura = "\n\n\nERROR DE SINTAXIS: se encontró una expresión incorrecta luego de '('\n";
const char * error_cierre = "\n\n\nERROR DE SINTAXIS: se encontró una expresión incorrecta luego de ')'\n";
const char * error_kleene = "\n\n\nERROR DE SINTAXIS: se encontró una expresión incorrecta luego de '*'\n";
const char * error_kleene_positiva = "\n\n\nERROR DE SINTAXIS: se encontró una expresión incorrecta luego de '^'\n";
const char * error_or = "\n\n\nERROR DE SINTAXIS: se encontró una expresión incorrecta luego de '+'\n";
const char * error_and = "\n\n\nERROR DE SINTAXIS: se encontró una expresión incorrecta luego de '.'\n";
const char * error_simbolo = "\n\n\nERROR DE SINTAXIS: se esperaba un operador luego del simbolo del alfabeto: ";
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

const char * leerArchivoCompleto(char * nombre_archivo){
	FILE *archivo;
 	char* contenido = malloc(sizeof(archivo)*TAM);
 	char caracter;
 	archivo = fopen ( nombre_archivo, "r" );
 	int i =0;
 	while(feof(archivo)== 0)
	 {
	 	char x = fgetc(archivo);
	 	contenido[i] =x;
	 	i++;
	 }
 	fclose (archivo);
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

char *obtenerEstadoEspecifico(char** estados,int i){
	int j=0;
	char* estado = (char *) malloc (1000*sizeof(char));
	do{
		estado[j] = estados[i][j];
		j++;
	}while(estados[i][j] != '|' );
	printf("estado %s \n", estados[i]);
	return estado;
}
char *concatenarEstado(char* estados, char* estado){
	printf("concatenando\n");
	int i = 0,j=0;
	char c ;
	char* MetaEstado = (char *) malloc (1000*sizeof(char));
	while(estados[i]!='|'){
		MetaEstado[i]= estados[i];
		i++;
	};
	while(estados[j]!='|'){
		MetaEstado[i]= estados[j];
		j++;
		i++;
	};
	MetaEstado[i]='|';
	return MetaEstado;
}
void imprimirEstados(char** estados){
	int i=0,j=0;
	for (i=0; i< 5 ;i++){
		for (j=0; j< 5 ;j++){
			if (estados[i][j] != '|')
				printf("i: %d j: %d c: %c \n",i,j, estados[i][j]);
			else
				break;
		}
		if (estados[i][0] == '|'){
			break;
		}
			
	}
}
int obtenerCantidadEstados(char** estados){
	int i=0;
	while(estados[i][0] != '|'){
		i++;
	}
	return i;
}

char **obtener_estados(const char* NDFA, char tipo ){
	int i=0,j=0,k=0,l=0;
	char** estados= (char **)malloc (1000*sizeof(char *));
	for (i=0;i<1000;i++)
		estados[i] = (char *) malloc (1000*sizeof(char));
	int flag = 0;
	char caracter;
	int fileLenght = ( strlen(NDFA));
	char* contenido = malloc(sizeof(char));
	char y;
	int aumentarL = 0;
	for (i=0;i <=fileLenght ; i++)
	{
		do
		{
			caracter = NDFA[j];
			if(caracter == tipo){
				flag = 1;
				aumentarL = 0;
			}else if (flag == 1 && caracter!= '=' && caracter!= '{' && caracter!= '}' && caracter!= ','){
				printf (" 1 i=%d k=%d char= %c \n",l,k,caracter);
				estados[l][k] = caracter;
				k++;
				aumentarL = 1;
			}else if (caracter == '}' || caracter == 0 ){
				estados[l][k] = '|';
				l++;
				flag = 0;
				j++;
				aumentarL = 0;
				break;
			}
			j++;
		}while(caracter != ',' );
		if (aumentarL==1){
			estados[l][k] = '|';
			
			l++;
			aumentarL= 0;
		}
		k = 0;
		
	}
	estados[l+1][0] = '|';
	return estados;
}
