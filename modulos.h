#include "cabeceras.h"

/** 
	Funcion encargada de interpretar la expresion regular ingresada en el archivo modulo1.txt
	Interpretacion realizada en tiempo de evaluacion, es decir, a medida se lee el caracter 
	este es interpretado y mostrado al usuario en pantalla.

	__name__:	modulo1		
*/
void modulo1(void){
	const char* expresion_regular = leerArchivo("modulo1.txt");
	int longitud = strlen(expresion_regular);
	int i=0;
	int contador_apertura=0;
	int contador_cierre=0;

	printf("\n%s es el lenguaje que contiene ", expresion_regular);
	while(i<longitud){
		//VALIDACION DE PARENTESIS APERTURA-CIERRE
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
					//VALIDACION DEL SIMBOLO (
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
					//VALIDACION DEL SIMBOLO )
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
					//VALIDACION DEL SIMBOLO *
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
					//VALIDACION DEL SIMBOLO ^
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
					//VALIDACION DEL SIMBOLO +
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
					//VALIDACION DEL SIMBOLO .
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
					//VALIDACIONES DE LOS SIMBOLOS DEL ALFABETO
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

/** 
	Funcion encargada de traducir el NDFA ingresado en el archivo modulo2.txt a un DFA.
	-----------------AGREGAR UN POCO DE DETALLE-----------------------

	__name__:	modulo2		
*/
void modulo2(void){
	int i=0,j=0,k=0,pos =0; 
	const char* NDFA = leerArchivoCompleto("NDFA.txt");
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

/** 
	Funcion encargada de evaluar la cadena segun el modo y la definicion del automata especificado
	en el archivo modulo3.txt.

	__name__:	modulo3		
*/
void modulo3(void){
	char* archivo = (char *) leerArchivoCompleto("modulo3.txt");
	char* palabra = obtenerPalabra(archivo);
	char modo = obtenerModo(archivo);
	char* estado_finales = obtenerEstadosFinales(archivo);
	char* estado_actual = obtenerEstadoInicial(archivo);
	printf("\nEvaluacion de la palabra: %s\n\n", palabra);
	if(modo == '1'){ //SE TRABAJA CON DFA
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
			
			while (t[i].estado != NULL ){
				if((t[i].valor == palabra[j]) && (strcmp(t[i].estado,estado_actual) == 0)){
					if(j!=strlen(palabra)-1){
						printf("T'(T(%s,%c),%s) = %s\n", t[i].estado,t[i].valor,palabra_aux,t[i].estadosiguiente);
					}else{
						printf("T(%s,%c) = %s\n", t[i].estado,t[i].valor,t[i].estadosiguiente);
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
	}else{//SE TRABAJA CON NDFA
		int i = 0;	//INDICE DE TRANSICIONES
		int j = 0;	//INDICE PARA RECORRER LA PALABRA A EVALUAR
		int k = 0;	//INDICE PARA RECORRER PORCION NO EVALUADA DE LA PALABRA
		int rechazo = 0;
		
		Transicion* t = obtenerTransicionesDFA(archivo);
		for(j=0; j<strlen(palabra); j++){
			char* palabra_aux = (char *) malloc(sizeof(char)*TAM);
			char* estado_aux = (char *) malloc(sizeof(char)*TAM);
			char* estado_actual_aux = (char *) malloc(sizeof(char)*TAM);
			int l = 0;
			int n = 1;
			for(k=j+1; k<(strlen(palabra)); ++k){
				palabra_aux[l] = palabra[k];
				l++;
			}
			while (t[i+1].estado != NULL ){
				if(j==0){ //SE EVALUA SOLAMENTE EL SIMBOLO INCIAL
					if((t[i].valor == palabra[j]) && (strcmp(t[i].estado,estado_actual) == 0)){
						if(j!=strlen(palabra)-1){
							printf("T'(T(%s,%c),%s) = %s\n", t[i].estado,t[i].valor,palabra_aux,t[i].estadosiguiente);
						}else{
							printf("T(%s,%c) = %s\n", t[i].estado,t[i].valor,t[i].estadosiguiente);
						}
						estado_actual=t[i].estadosiguiente;
						break;
					}
				}else{
					if(estado_actual[0]=='!'){ //SE RECHAZA LA PALABRA DE QUEDAR CONJUNTO VACIO AL EVALUAR EL SIMBOLO INICIAL
						printf("\n\nLa palabra: %s, no pertenece al L(M)\n",palabra);
						j=strlen(palabra);
						rechazo = 1;
						break;
					}
				}
				i++;
			}
			if(j>0 && rechazo == 0){ //SE EVALUAN LOS DEMAS SIMBOLOS DE LA PALABRA, SI ES QUE LOS HAY.
				if(j!=strlen(palabra)-1){ //IMPRESION EN PANTALLA DE LAS TRANSICIONES A EVALUAR
					printf("T'(T(%s,%c),%s) = ", estado_actual,palabra[j],palabra_aux);
				}else{
					printf("T(%s,%c) = ", estado_actual,palabra[j]);
				}
				int m;
				int g = 1;
				int cantidad = contarEstados(estado_actual);
				int bandera = 0;
				int bandera2 = 0;
				estado_actual_aux[0]='{';
				for(m=0; m<(strlen(estado_actual)-1); m++){
					int h = 0;//INDICE DE ESTADO_AUX
					while(estado_actual[n]!=',' && estado_actual[n]!='}'){
						estado_aux[h]=estado_actual[n];
						n++;
						h++;
					}
					int i=0;
					while (t[i].estado != NULL ){ //CONJUNTO DE ESTADOS RESULTADOS DE LAS EVALUACIONES INDIVIDUALES
						if((t[i].valor == palabra[j]) && (strcmp(t[i].estado,estado_aux) == 0)){
							printf("T(%s,%c)", t[i].estado,t[i].valor);
							bandera++;
							if(bandera == cantidad){
								printf(" = ");
							}else{
								printf(" U ");
							}
						}
						i++;
					}
					n++;
					m=n;
				}
				n=1;
				for(m=0; m<(strlen(estado_actual)-1); m++){ //UNION DE LOS CONJUNTOS DE ESTADOS
					int h = 0;//INDICE DE ESTADO_AUX
					while(estado_actual[n]!=',' && estado_actual[n]!='}'){
						estado_aux[h]=estado_actual[n];
						n++;
						h++;
					}
					i=0;
					int f=0;
					while (t[i].estado != NULL ){
						if((t[i].valor == palabra[j]) && (strcmp(t[i].estado,estado_aux) == 0)){
							printf("%s", t[i].estadosiguiente);
							bandera2++;
							if(bandera2 == cantidad){
								printf(" = ");
							}else{
								printf(" U ");
							}
							while(f < strlen(t[i].estadosiguiente)){
								if(t[i].estadosiguiente[f]!='{' && t[i].estadosiguiente[f]!='}'){
									estado_actual_aux[g]=t[i].estadosiguiente[f];
									g++;
								}
								f++;
							}
							if(bandera2 != cantidad){
								estado_actual_aux[g]=',';
								g++;
							}
						}
						i++;
					}
					estado_actual_aux[g]='}';
					n++;
					m=n;
				}

				estado_actual = eliminarRepetidos(estado_actual_aux);
				if(estado_actual[0]=='}'){ //SI NO HAY TRANSICION VALIDA, LA PALABRA ES RECHAZADA POR EL AUTOMATA
					printf("!\n\nLa palabra: %s, no pertenece al L(M)\n",palabra);
					j=strlen(palabra);
					rechazo = 1;
				}else{
					printf("%s\n", estado_actual);
				}
			}
			getchar();
		}
		i = 1;
		k = 0;
		while(i < strlen(estado_actual)){ //EVALUACION FINAL DE LA PALABRA
			char* estado_actual_aux = (char *) malloc(sizeof(char)*TAM);
			j = 0;
			while(estado_actual[i] != ',' && estado_actual[i] != '}'){
				estado_actual_aux[j]=estado_actual[i];
				j++;
				i++;
			}
			if(strstr(estado_finales, estado_actual_aux)!=NULL){ //SI EXISTE AL MENOS UN ESTADO FINAL, LA PALABRA SE ACEPTA
				printf("La palabra: %s, pertenece al L(M)\n",palabra);
				i = strlen(estado_actual);
				k = 1;
			}
			i++;
		}
		if(k == 0 && rechazo == 0){ //SI NO EXISTE NINGUN ESTADO FINAL PRESENTE, LA PALABRA SE RECHAZA
			printf("La palabra: %s, no pertenece al L(M)\n",palabra);
		}
	}

	printf("\n\n\n%s", continuar);
	getchar();
}
