#include "stdio.h"
#include "modulos.h"

/** 
	Funcion principal que se encarga de la gestion del menu y sus respectivas opciones

	__name__:	main	
*/
int main(void){
	while(TRUE){
		//system("clear");
		printf("\n\n\n");
		int opcion=-1;
		while(TRUE){
			printf("		----------------------MENU----------------------\n");
			printf("		||||                                        ||||\n");
			printf("		||||                                        ||||\n");
			printf("		|||| 1. Interprete de expresiones regulares ||||\n");
			printf("		||||       2. Traductor de NDFA a DFA       ||||\n");
			printf("		||||       3. Simulador de NDFA o DFA       ||||\n");
			printf("		||||                4. Salir                ||||\n");
			printf("		||||                                        ||||\n");
			printf("		||||                                        ||||\n");
			printf("		------------------------------------------------\n");
			printf("Ingrese el numero de la opcion a escoger: ");
			scanf("%d",&opcion);
			//VERIFICACION DE INGRESO DE OPCION VALIDA
			while (getchar() != '\n');
			if(opcion>4 || opcion<1){
				printf("\n\nOpción inválida\n");
			}else{
				break;
			}
		}

		switch(opcion){
			case 1: //INTERPRETE DE EXPRESIONES REGULARES
				modulo1();
				break;
			case 2: //TRADUCTOR DE NDFA A DFA
				modulo2();
				break;
			case 3: //SIMULADOR DE NDFA O DFA
				modulo3();
				break;
			case 4: //SALIR
				return 0;
		}
	}

}