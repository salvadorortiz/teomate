#include "stdio.h"
#include "stdlib.h"
#include "string.h"

/**MACROS*/
#define TRUE 1
#define TAM 5000

/**ESTRUCTURA DE DATOS PARA LA FUNCION DE TRANSICION DE LOS DFA Y NDFA*/
typedef struct transicion
{
	char* estado;
	char valor;
	char* estadosiguiente;
}Transicion;

/**PROTOTIPOS DE FUNCIONES*/
void modulo1(void);
void modulo2(void);
void modulo3(void);
const char * leerArchivo(char *);
const char * leerArchivoCompleto(char *);
char *concatenar(char *, char);
Transicion buscarEstado(char* estado, Transicion* todosLosEstados,char valor);

/**MENSAJES DE ERROR Y MENSAJE DE CONTINUAR*/
const char * error_parentesis = "\n\n\nERROR DE SINTAXIS: numero incorrecto de parentesis de cierre respecto a parentesis de apertura\n";
const char * error_apertura = "\n\n\nERROR DE SINTAXIS: se encontro una expresion incorrecta luego de '('\n";
const char * error_cierre = "\n\n\nERROR DE SINTAXIS: se encontro una expresion incorrecta luego de ')'\n";
const char * error_kleene = "\n\n\nERROR DE SINTAXIS: se encontro una expresion incorrecta luego de '*'\n";
const char * error_kleene_positiva = "\n\n\nERROR DE SINTAXIS: se encontro una expresion incorrecta luego de '^'\n";
const char * error_or = "\n\n\nERROR DE SINTAXIS: se encontro una expresion incorrecta luego de '+'\n";
const char * error_and = "\n\n\nERROR DE SINTAXIS: se encontro una expresion incorrecta luego de '.'\n";
const char * error_simbolo = "\n\n\nERROR DE SINTAXIS: se esperaba un operador luego del simbolo del alfabeto: ";
const char * continuar = "Presione ENTER para continuar";


/** 
	Funcion que verifica si el meta estado contiene un estado en especifico

	__name__:				comparar_meta_con_estado	
    @param meta: 			un meta en especifico
    @param estado: 			y un estado en especifico
    @return int: 			retorn 1 si se encuentra 0 si no se encuentra
*/
int comparar_meta_con_estado(char* meta, char* estado){
	int flag=0,i=0,j=0;
	for(i=0;i<strlen(meta);i++){
		for(j=0;j<strlen(estado);j++){
			if(meta[i+j]==estado[j]){
				flag =1;
			}
			else{
				flag=0;
			}
		}
		if(flag==1){
			return flag;
		}
	}
	return 0;
}
/** 
	Funcion que remueve los estados repeditos dentro de un meta y ademas remueve conjustos vacios innecesarios

	__name__:				EliminarRepeticion	
    @param estadoSiguiente: Es un meta estado resultado de llevar acabo un evaluacion de transicion.
    @return int: 			retorna el meta sin estados repetidos y sin conjuntos vacios innecesarios.
*/
char* EliminarRepeticion(char* estadoSiguiente){
	int i=0,j=0,k=0;
	char* estadosSinRepeticion = (char *) malloc (1000*sizeof(char));
	
	char** estadosSeparados = (char **)malloc (1000*sizeof(char *));
	for (i=0;i<1000;i++)
		estadosSeparados[i] = (char *) malloc (1000*sizeof(char));
		
	char* estadoAux = (char *) malloc (1000*sizeof(char));
	int estadosTam = strlen(estadoSiguiente);
	
	for(i=0;i<estadosTam;i++){
		if(estadoSiguiente[i]!=','){
			estadosSeparados[j][k]= estadoSiguiente[i];
			k++;
		}else{
			k=0;
			j++;
		}
	}
	k=0,i=0;
	while(estadosSeparados[i][0]!='\0'){
		j=i+1;
		while(estadosSeparados[j][0]!='\0'){
			
			int sonIguales = strcmp(estadosSeparados[i],estadosSeparados[j]);
			if(sonIguales==0){
				k=1;
				break;
			}
			j++;
		}
		if (k==0 && (strcmp(estadosSeparados[i],"!")!=0 && estadosSeparados[1][0]!='\0')){
			strcat(estadosSinRepeticion, estadosSeparados[i]);
			strcat(estadosSinRepeticion, ",");
		}else if(k==0 && (strcmp(estadosSeparados[i],"!")!=0)&& estadosSeparados[1][0]=='\0'){
			strcat(estadosSinRepeticion, estadosSeparados[i]);
		}else if(strcmp(estadosSeparados[i],"!")==0 && estadosSeparados[1][0]=='\0'){
			strcat(estadosSinRepeticion, estadosSeparados[i]);
		}
		k=0;
		i++;
	}
	if(estadosSinRepeticion[strlen(estadosSinRepeticion)-1]==','){
		estadosSinRepeticion[strlen(estadosSinRepeticion)-1] = '\0';
	}
	return estadosSinRepeticion;
}
/*
	Funcion que evalua un meta estado con respecto a un simbolo y devuelve el meta estado siguiente

	__name__:				siguienteMeta	
    @param MetaEstado: 	El meta estado que se va a evaluar
    @param simbolo: 	el simbolo con el que se evaluara el meta
    @param t: 			el conjunto de todas las transiciones de todos los estados
    @return char*: 		el meta estado ya evaluado
*/
char* siguienteMeta(char* MetaEstado,char* simbolo, Transicion* t){
	int i=0,j=0;
	char* meta_siguiente = (char *) malloc (1000*sizeof(char));
	char* meta_auxiliar = (char *) malloc (1000*sizeof(char));
	Transicion transicionTemp; 
	while(MetaEstado[i] != '\0'){
		if(MetaEstado[i]=='!'){
			meta_siguiente = MetaEstado;
		}else if (MetaEstado[i+1]=='q'|| MetaEstado[i+1]=='\0'){
			meta_auxiliar[strlen(meta_auxiliar)]=MetaEstado[i];
			Transicion estado=buscarEstado(meta_auxiliar, t, simbolo[0]);
			strcat(meta_siguiente, estado.estadosiguiente);
			strcat(meta_siguiente, ",");
			meta_auxiliar= (char *) malloc (1000*sizeof(char));
		}else if (MetaEstado[i+1]!='q'){
			meta_auxiliar[strlen(meta_auxiliar)]=MetaEstado[i];
		}
		i++;
	}
	if(meta_siguiente[strlen(meta_siguiente)-1]==','){
		meta_siguiente[strlen(meta_siguiente)-1] = '\0';
	}
	meta_siguiente = EliminarRepeticion(meta_siguiente);
	return meta_siguiente;
}

/*
	Funcion que imprime los metasy los meta estados siguientes luego de evaluarlos

	__name__:			evaluarMetas	
    @param MetaEstados: conjunto de MetaEstados que se evaluaran
    @param alfabeto: 	los simbolo del alfabeto
    @param t: 			el conjunto de todas las transiciones de todos los estados
    @return void: 		solo imprime los resultados
*/
void evaluarMetas(char** MetaEstados, char** alfabeto, Transicion* t){
	int j=0,i=0;
	int cantidadAlfabeto = obtenerCantidadEstados(alfabeto);
	
	for(i=0;i<cantidadAlfabeto;i++){
			alfabeto[i][strlen(alfabeto[i])-1]='\0';
	}
	while(MetaEstados[j][0]!='\0'){
		for(i=0;i<cantidadAlfabeto;i++){
			char* estadoSiguiente=siguienteMeta(MetaEstados[j],alfabeto[i],t);
			printf("T([%s],%s)={%s}\n\n",MetaEstados[j],alfabeto[i],estadoSiguiente);
		}
		j++;
	}
}
/*
	Funcion que evalua cuales meta estados son finales 

	__name__:				obtener_metas_estados_finales	
    @param MetaEstados: 	conjunto de MetaEstados que se evaluaran
    @param estadosFinales: 	Los estados finales originales
    @return char**: 		doble puntero de los meta estados finales
*/
char ** obtener_metas_estados_finales(char** MetaEstados, char** estadosFinales){
	int i=0,j=0,k=0;
	char** metasFinales = (char **)malloc (1000*sizeof(char *));
	for (i=0;i<1000;i++)
		metasFinales[i] = (char *) malloc (1000*sizeof(char));
	int contadorFinales= obtenerCantidadEstados(estadosFinales);
	for(i=0;i<contadorFinales;i++){
		estadosFinales[i][strlen(estadosFinales[i])-1]='\0';
		while(MetaEstados[j][0]!='\0'){
			int x = comparar_meta_con_estado(MetaEstados[j],estadosFinales[i]);
			if(x==1){
				metasFinales[k]= MetaEstados[j];
				k++;
			}
			j++;
		}
		j=0;
	}
	return metasFinales;
}
/*
	Funcion que evalua la cantidad del un elevado a un n 

	__name__:				potencia	
    @param b: 		base
    @param e: 		exponente
    @return int: 	potencia
*/
int potencia(int b,int e){
    int i;
    int pot=1;
    for(i=1;i<=e;i++){
          pot=pot*b;
    }
    return pot;
}
/*
	Funcion que elimina delimitadores del arreglo de estados 

	__name__:				potencia	
    @param estados: 		estados que se quieren limpiar
    @param cantidadEstados: cantidad de estados
    @return char **: 		estos sin delimitadores
*/
char** cleanStates(char** estados, int cantidadEstados){
	int i =0;
	char** estadosLimpios = (char **)malloc (1000*sizeof(char *));
	for (i=0;i<1000;i++)
		estadosLimpios[i] = (char *) malloc (1000*sizeof(char));
		
	for(i=0; i<cantidadEstados; i++){
		estados[i][strlen(estados[i])-1]='\0';
		estadosLimpios[i] = estados[i];
	}
	return	estadosLimpios;
}
/*
	Funcion que genera los meta estados

	__name__:				obtenerMetas	
    @param estados: 		todos los estados
    @param cantidadEstados: cantidad de meta estados
    @return char **: 		los meta estados
*/
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
        metaEstados[i] =(strlen(metaTemp)!=0)? metaTemp:"!";
    }
    return metaEstados;
}
/*
	Funcion busca un estado en especifico en base a un valor especificado y a un estado

	__name__:				buscarEstado	
    @param estado: 			todos los estados
    @param todosLosEstados: todos los estados con sus transiciones
    @param valor: 			el valor que conlleva a la transicion
    @return Transicion: 	devuelve una estructura de estadoActual, estadoSiguiente y valor que genera esa transicion.
*/
Transicion buscarEstado(char* estado, Transicion* todosLosEstados, char valor){
	int sizeEstados= (sizeof(todosLosEstados));
	Transicion def;
	int i = 0, j = 0;
	for(i=0; i<sizeEstados; i++){
		int sizeEstado = (sizeof(todosLosEstados[i].estado));
		int flag = 0;
		for (j=0; j<sizeEstado; j++){
			if (todosLosEstados[i].estado != NULL && todosLosEstados[i].estado[j] == estado[j] && todosLosEstados[i].valor == valor){
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

/** 
	Funcion que lee todas las transiciones pertenecientes a la definicion de la funcion
	de transicion del NDFA.

	__name__:				obtenerTransiciones	
    @param NDFA: 			contenido leido desde el archivo de texto
    @return transiciones: 	puntero hacia el conjunto de estructuras del tipo Transicion
*/
Transicion* obtenerTransiciones(const char* NDFA){
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

/** 
	Funcion que lee el contenido completo de un archivo como una sola cadena.

	__name__:				leerArchivo	
    @param nombre_archivo: 	nombre del archivo del cual se leera el contenido 
    @return contenido: 		cadena leida del archivo pasado como parametro	
*/
const char * leerArchivo(char * nombre_archivo){
	FILE *archivo;
 	char* contenido = (char*) malloc(sizeof(archivo)*TAM);
 	archivo = fopen ( nombre_archivo, "r" );
 	fscanf(archivo, "%s" ,contenido);
 	fclose (archivo);
 	return contenido; 
}

/** 
	Funcion que lee el contenido completo de un archivo caracter a caracter.

	__name__:				leerArchivoCompleto	
    @param nombre_archivo: 	nombre del archivo del cual se leera el contenido 
    @return contenido: 		cadena leida del archivo pasado como parametro	
*/
const char * leerArchivoCompleto(char * nombre_archivo){
	FILE *archivo;
 	char* contenido = (char*) malloc(sizeof(archivo)*TAM);
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

/** 
	se utiliza para saber cuantos estado se encuentran en el doble puntero

	__name__:			obtenerCantidadEstados	
    @param estados: 	doble puntero de estados;
    @return i:			la cantidad de estados	
*/
int obtenerCantidadEstados(char** estados){
	int i=0;
	while(estados[i][0] != '|'){
		i++;
	}
	return i;
}
char* obtener_estado_inicial(const char* NDFA){
	int i=0,flag=0,k=0;
	char* estadoInicial = (char *) malloc (1000*sizeof(char));
	int fileLenght = ( strlen(NDFA));
	for (i=0;i <=fileLenght ; i++)
	{
		if(flag == 1 && NDFA[i]!='\n'){
			estadoInicial[k]= NDFA[i];
			k++;
		}else if(NDFA[i]=='S'){
			flag =1;
			i++;
		}else if(NDFA[i]=='\n'){
			flag =0;
		}
	}
	return estadoInicial;
}
/** 
	Genera los estados

	__name__:			obtener_estados	
    @param NDFA: 		Todo el contenido del archivo esta contenido aca
    @param tipo: 		que tipo de datos se quiere sacar de alli(estados, estados finales, alfabeto, etc)
    @return estados:	un doble puntero con los valos solicitados.	
*/
char **obtener_estados(const char* NDFA, char tipo ){
	int i=0,j=0,k=0,l=0;
	char** estados= (char **)malloc (1000*sizeof(char *));
	for (i=0;i<1000;i++)
		estados[i] = (char *) malloc (1000*sizeof(char));
	int flag = 0;
	char caracter;
	int fileLenght = ( strlen(NDFA));
	char* contenido = (char*) malloc(sizeof(char));
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
				estados[l][k] = caracter;
				k++;
				aumentarL = 1;
			}else if (flag == 1 && caracter == '}' || caracter == 0 ){
				estados[l][k] = '|';
				l++;
				j++;
				flag = 0;
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

/** 
	Funcion que verifica el modo en el que se trabajara en el modulo 3 (1:DFA, 2:NDFA)

	__name__:			obtenerModo	
    @param DFA: 		contenido leido desde el archivo de texto
    @return DFA[i+1]:	caracter que indica el modo en el que se trabajara	
*/
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

/** 
	Funcion que verifica la palabra a evaluar en el modulo 3

	__name__:			obtenerPalabra	
    @param DFA: 		contenido leido desde el archivo de texto
    @return palabra:	palabra que sera evaluada por el modulo 3	
*/
char* obtenerPalabra(const char* DFA){
	int i = 0;
	char* palabra = (char *) malloc(sizeof(char)*TAM);
	while(DFA[i] != '\n'){
		palabra[i]=DFA[i];
		i++;
	}
	return palabra;
}

/** 
	Funcion que verifica el estado inicial del automata

	__name__:				obtenerEstadoInicial	
    @param DFA: 			contenido leido desde el archivo de texto
    @return estado_inicial:	cadena que contiene el estado inicial del automata	
*/
char* obtenerEstadoInicial(const char* DFA){
	int i = 0;
	int j = 0;
	char* estado_inicial = (char *) malloc(sizeof(char)*TAM);
	while(DFA[i] != 'S'){
		i++;
	}
	i=i+2;
	while(DFA[i] != '\n'){
		estado_inicial[j]=DFA[i];
		i++;
		j++;
	}
	return estado_inicial;
}

/** 
	Funcion que verifica el conjunto de estados finales del automata

	__name__:					obtenerEstadosFinales	
    @param DFA: 				contenido leido desde el archivo de texto
    @return estados_finales:	cadena que contiene el conjunto de los estados finales del automata	
*/
char* obtenerEstadosFinales(const char* DFA){
	int i = 0;
	int j = 0;
	char* estados_finales = (char *) malloc(sizeof(char)*TAM);
	while(DFA[i] != 'F'){
		i++;
	}
	i=i+2;
	while(DFA[i] != '\n'){
		estados_finales[j]=DFA[i];
		i++;
		j++;
	}
	return estados_finales;
}

/** 
	Funcion que cuenta el numero de estados presentes en la cadena pasada por parametro

	__name__:				contarEstados	
    @param cadena: 			cadena que contiene un conjunto de estados
    @return contador+1:		entero que representa el numero de estados presentes en la cadena	
*/
int contarEstados(char * cadena){
	int contador = 0;
	int i = 0;
	if(strlen(cadena)==0){
		return -1;
	}
	while(i < strlen(cadena)){
		if(cadena[i]==','){
			contador++;
		}
		i++;
	}
	return contador+1;
}

/** 
	Funcion que elimina estados repetidos en la cadena pasada por parametro

	__name__:				eliminarRepetidos	
    @param cadena: 			cadena que contiene un conjunto de estados
    @return cadena_aux:		cadena con estados repetidos eliminados	
*/
char* eliminarRepetidos(char * cadena){
	char* cadena_aux = (char *) malloc(sizeof(char)*TAM);
	char* estado = (char *) malloc(sizeof(char)*TAM);
	int i = 1;
	int k = 1;
	cadena_aux[0] = '{';
	while(i<(strlen(cadena)-1)){
		int j = 0;
		while(cadena[i]!=',' && cadena[i]!='}' && cadena[i]!='!'){
			estado[j]=cadena[i];
			j++;
			i++;
		}
		i++;
		char* repetido = strstr(cadena_aux, estado);
		j=0;
		if(repetido == NULL){
			while(j<strlen(estado)){
				cadena_aux[k]=estado[j];
				k++;
				j++;
			}
			cadena_aux[k]=',';
			k++;
		}
	}
	cadena_aux[k-1]='}';
	return cadena_aux;
}

/** 
	Funcion que lee todas las transiciones pertenecientes a la definicion de la funcion
	de transicion del DFA.

	__name__:				obtenerTransicionesDFA	
    @param DFA: 			contenido leido desde el archivo de texto
    @return transiciones: 	puntero hacia el conjunto de estructuras del tipo Transicion
*/
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
				while(DFA[i]!='\n'){
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
