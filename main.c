#include <stdio.h>
#include "contacto.h"
#include "fileops.h"
#include "ui.h"
#include "gtkiu.h"

#define MAX 500

int main(int argc, char *argv[]) {
	iniciarGTK(argc, argv);
	int opcion;
	contacto persona;
	contacto listaPersonas[MAX];
	/*FILE *archivo = fopen("info.dat", "ab+");
	if (!archivo) { perror("No se puede abrir info.dat"); return 1; }
	fclose(archivo);*/
	
	while ((opcion = menu()) != 0) {
		switch (opcion) {
		case 1:
			persona = pedirDatos();
			if (buscarContacto(&persona))
				puts("Ya existe ese contacto.");
			else {
				agregarContacto(&persona);
				puts("Contacto guardado.");
			}
			break;
		case 2:
			persona = pedirNombre();
			if (buscarContacto(&persona)) {
				eliminarContacto(&persona);
			} else
				printf("No existe: %s", persona.nombre);
			break;
		case 3:
			persona = pedirNombre();
			if (buscarContacto(&persona)) {
				editarContacto(&persona);
				puts("Contacto modificado.");
			} else
				printf("No existe: %s", persona.nombre);
			break;
		case 4:
			listarContactos();
			break;
		case 5:
			persona = pedirNombre();
			if (buscarContacto(&persona))
				puts("\t-----");
			else
				puts("Contacto no encontrado.");
			break;
		}
		puts("Pulse ENTER para continuar...");
		getchar();
	}
	
	puts("Programa terminado.");
	
	return 0;
}
