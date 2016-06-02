#include "stdio.h"
#include "modulos.h"


int main(void){
	system("clear");
	while(TRUE){
		system("clear");
		int opcion=-1;
		while(TRUE){
			printf("		----------------------MENÚ----------------------\n");
			printf("		||||                                        ||||\n");
			printf("		||||                                        ||||\n");
			printf("		|||| 1. Interprete de expresiones regulares ||||\n");
			printf("		||||       2. Traductor de NDFA a DFA       ||||\n");
			printf("		||||       3. Simulador de NDFA o DFA       ||||\n");
			printf("		||||                4. Salir                ||||\n");
			printf("		||||                                        ||||\n");
			printf("		||||                                        ||||\n");
			printf("		------------------------------------------------\n");
			printf("Ingrese el número de la opción a escoger: ");
			scanf("%d",&opcion);
			//Verificando que se ingrese una opción válida
			while (getchar() != '\n');
			if(opcion>4 || opcion<1){
				printf("\n\nOpción inválida\n");
			}else{
				break;
			}
		}

		switch(opcion){
			case 1: //Interprete de expresiones regulares
				modulo1();
				break;
			case 2: //Traductor de NDFA a DFA
				modulo2();
				break;
			case 3: //Simulador de NDFA o DFA
				modulo3();
				break;
			case 4: //Salir	
				return 0;
		}
	}

}