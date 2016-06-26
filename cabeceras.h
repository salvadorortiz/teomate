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

typedef struct transicion
{
	char* estado;
	char valor;
	char* estadosiguiente;
}Transicion;

int potencia(int b,int e){
    int i;
    int pot=1;
    for(i=1;i<=e;i++){
          pot=pot*b;
    }
    return pot;
}
char** cleanStates(char** estados, int cantidadEstados){
	int i =0;
	char** estadosLimpios = (char **)malloc (1000*sizeof(char *));
	for (i=0;i<1000;i++)
		estadosLimpios[i] = (char *) malloc (1000*sizeof(char));
		
	for(i=0; i<cantidadEstados; i++){
		printf("start");
		estados[i][strlen(estados[i])-1]='\0';
		printf("%s\n",estados[i]);
		estadosLimpios[i] = estados[i];
	}
	return	estadosLimpios;
}
char** obtenerMetas(char** estados, int limite){
	int i,j;
	char** metaEstados = (char **)malloc (1000*sizeof(char *));
	for (i=0;i<1000;i++)
		metaEstados[i] = (char *) malloc (1000*sizeof(char));
    
    for(i=0;i<potencia(2,limite);i++){
    	char* metaTemp = (char *) malloc (1000*sizeof(char));
        for(j=0;j<limite;j++){
          if(i & (1<<j)){
          	strcat(metaTemp, estados[j]);
		  }
        }
        metaEstados[i] = metaTemp;
    }
    return metaEstados;
}

Transicion buscarEstado(char* estado, Transicion* todosLosEstados){
	int sizeEstados= (sizeof(todosLosEstados));
	Transicion def;
	int i = 0, j = 0;
	for(i=0; i<sizeEstados; i++){
		int sizeEstado = (sizeof(todosLosEstados[i].estado));
		int flag = 0;
		for (j=0; j<sizeEstado; j++){
			if (todosLosEstados[i].estado != NULL && todosLosEstados[i].estado[j] == estado[j]){
				flag = 1;
			}else{
				flag = 0;
				break;
			}
		}
		if (flag ==1)
		{
			return todosLosEstados[i];
		}
	}
	return def;
}

Transicion* obtenerTransiciones(const char* NDFA)
{
	Transicion* transiciones = (Transicion *) malloc (1000*sizeof(Transicion));
	
	int i=0, fileLenght = ( strlen(NDFA));
	int flagTransicion = 0;
	int flagDeclaracion = 0;
	int j =0;
	int k = 0;
	for (i=0;i <=fileLenght ; i++)
	{		
		if (NDFA[i] == 'T'){
			
			flagTransicion =1;
		}else if(NDFA[i] == '\n' && flagTransicion == 1){
			flagTransicion = 0;
		}
		if (flagTransicion == 1)
		{
			
			if (NDFA[i] == '(')
			{
				i++;
				j=0;
				transiciones[k].estado = (char *) malloc (1000*sizeof(char));
				while(NDFA[i] != ',')
				{
					transiciones[k].estado[j] = NDFA[i];
					i++;
					j++;
				}
				j=0;
				i++;
				transiciones[k].valor = NDFA[i];
				i++;
			}
			
			if (NDFA[i] == '{')
			{
				i++;
				transiciones[k].estadosiguiente = (char *) malloc (1000*sizeof(char));
				while(NDFA[i]!='}')
				{
					transiciones[k].estadosiguiente[j]=NDFA[i] ;
					j++;
					i++;
				}
				k++;
				flagTransicion = 0;
			}
			else if (NDFA[i] == '!')
			{
				transiciones[k].estadosiguiente = (char *) malloc (1000*sizeof(char));
				transiciones[k].estadosiguiente[0]=NDFA[i] ;
				k++;
				flagTransicion = 0;
			}			
		}
	}
	return transiciones;
}

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

char obtenerModo(const char* DFA){
	int i = 0;
	char modo;
	int longitud = (strlen(DFA));
	for (i=0; i <=longitud; i++){
		if(DFA[i]=='\n'){
			return modo= DFA[i+1];
		}
	}
}

char* obtenerPalabra(const char* DFA){
	int i = 0;
	char* palabra = (char *) malloc(sizeof(char)*TAM);
	while(DFA[i+1] != '\n'){
		palabra[i]=DFA[i];
		i++;
	}
	return palabra;
}

char* obtenerEstadoInicial(const char* DFA){
	int i = 0;
	int j = 0;
	char* estado_inicial = (char *) malloc(sizeof(char)*TAM);
	while(DFA[i] != 'S'){
		i++;
	}
	i=i+2;
	while(DFA[i+1] != '\n'){
		estado_inicial[j]=DFA[i];
		i++;
		j++;
	}
	return estado_inicial;
}

char* obtenerEstadosFinales(const char* DFA){
	int i = 0;
	int j = 0;
	char* estados_finales = (char *) malloc(sizeof(char)*TAM);
	while(DFA[i] != 'F'){
		i++;
	}
	i=i+2;
	while(DFA[i+1] != '\n'){
		estados_finales[j]=DFA[i];
		i++;
		j++;
	}
	return estados_finales;
}

Transicion* obtenerTransicionesDFA(const char* DFA){
	Transicion* transiciones = (Transicion *) malloc(sizeof(Transicion)*TAM);
	
	int i = 0;
	int j = 0;
	int k = 0;
	int longitud = (strlen(DFA));
	int bandera_transicion = 0;

	while(i <= longitud){
		if (DFA[i] == 'T'){
			bandera_transicion = 1;
		}

		if (bandera_transicion == 1){
			if (DFA[i] == '('){
				i++;
				j=0;
				transiciones[k].estado = (char *) malloc(sizeof(char)*TAM);
				while(DFA[i] != ','){
					//Ingreso del estado a la estructura
					transiciones[k].estado[j] = DFA[i];
					i++;
					j++;
				}
				j=0;
				i++;
				//Ingreso del simbolo a la estructura
				transiciones[k].valor = DFA[i];
			}
			
			if (DFA[i] == '='){
				i++;
				if(DFA[i]==' '){
					i++;
				}
				transiciones[k].estadosiguiente = (char *) malloc(sizeof(char)*TAM);
				while(DFA[i+1]!='\n'){
					//Ingreso de los estados generados por la transicion
					transiciones[k].estadosiguiente[j]=DFA[i] ;
					j++;
					i++;
					//Validacion para no generar loop infinito en caso de olvidar salto de linea al final del archivo
					if(i > longitud-2){
						break;
					}
				}
				k++;
				bandera_transicion = 0;
			}	
		}
		i++;
	}
	return transiciones;
}
