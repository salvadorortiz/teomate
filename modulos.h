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
	//char lenguaje[TAM] = " es el lenguaje que contiene ";
	int longitud = strlen(expresion_regular);
	int i=0;
	int contador=0;

	printf("\n%s es el lenguaje que contiene ", expresion_regular);
	while(i<longitud){
		//concatenar(lenguaje,expresion_regular[i]);
		//strcat(lenguaje,"Hola");
		switch(expresion_regular[i]){
			case 40:
				contador++;
				break;
			case 41:
				//strcat(lenguaje,", esto");
				printf(", esto");
				contador--;
				break;
			case 42:
				printf(", cero o mas veces");
				//strcat(lenguaje," cero o más veces");
				break;
			case 94:
				printf(" una o mas veces");
				//strcat(lenguaje," una o más veces");
				break;
			case 43:
				printf(" o ");
				//strcat(lenguaje," o ");
				break;
			case 46:
				printf(" concatenado con ");
				//strcat(lenguaje," concatenado con ");
				break;
			default:
				printf("%c", expresion_regular[i]);
				//concatenar_caracter(lenguaje,expresion_regular[i]);
				break;
		}
		i++;
	}
	if(contador!=0){
		printf("\n\n%s\n\n%s",error_modulo1,continuar);
	}else{
		printf("\n\n\n%s", continuar);
		//printf("\n\n%s%s\n\n%s", expresion_regular,lenguaje,continuar);
	}
	getchar();

}

void modulo2(void){
	printf("Modulo 2\n");
}

void modulo3(void){
	printf("Modulo 3\n");
}