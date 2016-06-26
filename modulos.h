#include "cabeceras.h"
/*
OPERADORES:
	40	(  delimitador apertura
	41	)  delimitador cierre
	42	*  cerradura de Kleene
	94	^  cerradura positiva de Kleene
	43	+  OR
	46	.  Y
*/
void modulo1(void){
	const char* expresion_regular = leerArchivo("expresion_regular.txt");
	int longitud = strlen(expresion_regular);
	int i=0;
	int contador_apertura=0;
	int contador_cierre=0;

	printf("\n%s es el lenguaje que contiene ", expresion_regular);
	while(i<longitud){
		//Validación de parentesis
		if(contador_apertura<contador_cierre){
			i=longitud+1;
			printf("\n\n%s\n", error_parentesis);
			contador_apertura=contador_cierre;
		}
		switch(expresion_regular[i]){
			case 40: // (
				printf("(");
				contador_apertura++;
				if(i+1<longitud){
					//Validación del simbolo (
					if(expresion_regular[i+1]==')' || expresion_regular[i+1]=='+' || expresion_regular[i+1]=='*' || expresion_regular[i+1]=='.' || expresion_regular[i+1]=='^'){
						i=longitud+1;
						printf("\n\n%s\n", error_apertura);
						contador_apertura=contador_cierre;
					}
				}
				break;
			case 41:// )
				printf("), esto");
				contador_cierre++;
				if(i+1<longitud){
					//Validación del simbolo )
					if(expresion_regular[i+1]!='+' && expresion_regular[i+1]!='.' && expresion_regular[i+1]!='*' && expresion_regular[i+1]!='^'){
						i=longitud+1;
						printf("\n\n%s\n", error_cierre);
						contador_apertura=contador_cierre;
					}
				}
				break;
			case 42:// *
				printf(", cero o mas veces");
				if(i+1<longitud){
					//Validación del simbolo *
					if(expresion_regular[i+1]!='+' && expresion_regular[i+1]!='.' && expresion_regular[i+1]!=')'){
						i=longitud+1;
						printf("\n\n%s\n", error_kleene);
						contador_apertura=contador_cierre;
					}
				}
				break;
			case 94:// ^
				printf(" una o mas veces");
				if(i+1<longitud){
					//Validación del simbolo ^
					if(expresion_regular[i+1]!='+' && expresion_regular[i+1]!='.' && expresion_regular[i+1]!=')'){
						i=longitud+1;
						printf("\n\n%s\n", error_kleene_positiva);
						contador_apertura=contador_cierre;
					}
				}
				break;
			case 43:// +
				printf(" o ");
				if(i+1<longitud){
					//Validación del simbolo +
					if(expresion_regular[i+1]==')' || expresion_regular[i+1]=='+' || expresion_regular[i+1]=='*' || expresion_regular[i+1]=='.' || expresion_regular[i+1]=='^'){
						i=longitud+1;
						printf("\n\n%s\n", error_or);
						contador_apertura=contador_cierre;
					}
				}
				break;
			case 46:// .
				printf(" concatenado con ");
				if(i+1<longitud){
					//Validación del simbolo .
					if(expresion_regular[i+1]==')' || expresion_regular[i+1]=='+' || expresion_regular[i+1]=='*' || expresion_regular[i+1]=='.' || expresion_regular[i+1]=='^'){
						i=longitud+1;
						printf("\n\n%s\n", error_and);
						contador_apertura=contador_cierre;
					}
				}
				break;
			default:
				printf("%c", expresion_regular[i]);
				if(i+1<longitud){
					//Validación de los simbolos del alfabeto
					if(expresion_regular[i+1]!='+' && expresion_regular[i+1]!='.' && expresion_regular[i+1]!=')' && expresion_regular[i+1]!='*' && expresion_regular[i+1]!='^'){
						printf("\n\n%s", error_simbolo);
						printf("%c", expresion_regular[i]);
						i=longitud+1;
						contador_apertura=contador_cierre;
					}
				}
				break;
		}
		i++;
	}
	printf(".");
	if(contador_apertura != contador_cierre){
		printf("\n\n%s\n", error_parentesis);
	}
	printf("\n\n\n%s", continuar);
	getchar();
}

void modulo2(void){
	int i=0,j=0,k=0,pos =0; 
	const char* NDFA = leerArchivoCompleto("simulador.txt");
	char** estados= obtener_estados(NDFA, 'Q');
	int cantidadEstados = obtenerCantidadEstados(estados);
	char** estadosLimpios = cleanStates(estados,cantidadEstados);
	char** MetaEstados = obtenerMetas(estadosLimpios,cantidadEstados);
	int aux = potencia(2,cantidadEstados);
	for (i=0; i<aux;i++){
		printf("%s\n",MetaEstados[i]);
	}
	/*Transicion* t = obtenerTransiciones(NDFA);
	printf("\n---------------------Buscar estado--------------------------\n");
	buscarEstado("q3", t);
	printf("\n-----------------------------------------------\n");
	printf("\n---------------------Ejemplo de como accesar a transiciones  --------------------------\n");
	int aux= (sizeof(t));
	while (t[i].estado != NULL )
	{
		printf ("estado: %s, valor: %c, estadosSiguientes %s\n",t[i].estado, t[i].valor, t[i].estadosiguiente);	
		i++;
	}
	i=0;
	printf("\n-----------------------------------------------\n");
	char** metaEstados= (char **)malloc (2000*sizeof(char *));
	for (i=0;i<2000;i++)
		metaEstados[i] = (char *) malloc (2000*sizeof(char));
	for (i=0; i < cantidadEstados; i++){
		for(j=i;j<cantidadEstados; j++){
			metaEstados[pos]= concatenarEstado(estados[j], estados[j+1]);
			pos++;
		}
		k=1;
	}*/
	
	printf("Cantidad de estados: %d\n" , obtenerCantidadEstados(estados));
}

void modulo3(void){
	char* archivo = (char *) leerArchivoCompleto("simulador.txt");
	char* palabra = obtenerPalabra(archivo);
	char modo = obtenerModo(archivo);
	char* estado_finales = obtenerEstadosFinales(archivo);
	char* estado_actual = obtenerEstadoInicial(archivo);
	printf("\nEvaluación de la palabra: %s\n\n", palabra);
	
	if(modo == '1'){ //Se trabaja con DFA
		Transicion* t = obtenerTransicionesDFA(archivo);
		int i = 0;
		int j = 0;
		int k = 0;
		for(j=0; j<strlen(palabra); j++){
			char* palabra_aux = (char *) malloc(sizeof(char)*TAM);
			int l = 0;
			for(k=j+1; k<(strlen(palabra)); ++k){
				palabra_aux[l] = palabra[k];
				l++;
			}
			
			while (t[i+1].estado != NULL ){
				if((t[i].valor == palabra[j]) && (strcmp(t[i].estado,estado_actual) == 0)){
					if(j!=strlen(palabra)-1){
						printf("T(T(%s,%c),%s)=%s", t[i].estado,t[i].valor,palabra_aux,t[i].estadosiguiente);
					}else{
						printf("T(%s,%c)=%s", t[i].estado,t[i].valor,t[i].estadosiguiente);
					}
					estado_actual=t[i].estadosiguiente;
					break;
				}
				i++;
			}
			getchar();
			i=0;
		}
		char* aceptacion = strstr(estado_finales, estado_actual);
		if(aceptacion != NULL){
			printf("La palabra: %s, pertenece al L(M)\n",palabra);
		}else{
			printf("La palabra: %s, no pertenece al L(M)\n",palabra);
		}
	}else{
		int i = 0;
		int j = 0;
		int k = 0;
		Transicion* t = obtenerTransicionesDFA(archivo);
		for(j=0; j<strlen(palabra); j++){
			char* palabra_aux = (char *) malloc(sizeof(char)*TAM);
			char* estado_aux = (char *) malloc(sizeof(char)*TAM);
			int l = 0;
			for(k=j+1; k<(strlen(palabra)); ++k){
				palabra_aux[l] = palabra[k];
				l++;
			}
			while (t[i+1].estado != NULL ){
				if(j==0){ //Se vealua solamente el simbolo inicial
					if((t[i].valor == palabra[j]) && (strcmp(t[i].estado,estado_actual) == 0)){
						if(j!=strlen(palabra)-1){
							printf("T(T(%s,%c),%s)=%s\n", t[i].estado,t[i].valor,palabra_aux,t[i].estadosiguiente);
						}else{
							printf("T(%s,%c)=%s\n", t[i].estado,t[i].valor,t[i].estadosiguiente);
						}
						estado_actual=t[i].estadosiguiente;
						break;
					}
				}else{
					if(estado_actual[0]=='!'){// Si despues de evaluar el simbolo incial queda vacio entonces se rechaza
						printf("\nLa palabra: %s, no pertenece al L(M)\n",palabra);
						j=strlen(palabra);
						break;
					}
					//Falta evaluar el resto de la palabra con los estados del tipo {q0,q2}, {q1}, {q0,q1,q2}, etc...



					/* INTENTO FALLIDO
					int m = 1;
					int n = 0;
					//printf("%s\n", estado_actual);
					for(m=1; m<(strlen(estado_actual)-1); m++){
						//printf("%c\n",estado_actual[m]);
						while(estado_actual[m]!=','){
							estado_aux[n]=estado_actual[m];
							n++;
							m++;
						}
						printf("ESTADO_AUX: %s\n", estado_aux);
						if((t[i].valor == palabra[j]) && (strcmp(t[i].estado,estado_aux) == 0)){
							printf("T(T(%s,%c),%s)=", estado_actual,palabra[j],palabra_aux);
						}
					}*/

				}
				i++;
			}
		}
	}

	printf("\n\n\n%s", continuar);
	getchar();
}
