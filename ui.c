#include <stdio.h>
#include <stdlib.h>
#include "ui.h"

int menu(void) {
	int opcion;
	do {
		system("clear");
		puts("\t-ELEGIR ACCION-");
		puts("\t [1] AGREGAR");
		puts("\t [2] ELIMINAR");
		puts("\t [3] EDITAR");
		puts("\t [4] LISTAR");
		puts("\t [5] BUSCAR");
		puts("\t [0] SALIR");
		scanf("%d", &opcion);
		limpiarBuffer();
	} while (opcion < 0 || opcion > 5);
	
	return opcion;
}

void limpiarBuffer(void) {
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}
