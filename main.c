#include <stdio.h>
#include "contacto.h"
#include "fileops.h"
#include "ui.h"

int main(void) {
	int opcion;
	contacto persona;
	FILE *archivo = fopen("info.dat", "ab+");
	if (!archivo) { perror("No se puede abrir info.dat"); return 1; }
	
	while ((opcion = menu()) != 0) {
		switch (opcion) {
		case 1:
			persona = pedirDatos();
			if (buscarContacto(archivo, &persona))
				puts("Ya existe ese contacto.");
			else {
				agregarContacto(archivo, &persona);
				puts("Contacto guardado.");
			}
			break;
		case 2:
			persona = pedirNombre();
			if (buscarContacto(archivo, &persona)) {
				eliminarContacto(&persona);
				puts("Contacto eliminado.");
			} else
							   printf("No existe: %s", persona.nombre);
			break;
		case 3:
			persona = pedirNombre();
			if (buscarContacto(archivo, &persona)) {
				persona = pedirDatos();
				editarContacto(archivo, &persona);
				puts("Contacto modificado.");
			} else
							   printf("No existe: %s", persona.nombre);
			break;
		case 4:
			listarContactos(archivo);
			break;
		case 5:
			persona = pedirNombre();
			if (buscarContacto(archivo, &persona))
				puts("¡Contacto encontrado!");
			else
				puts("No lo hallé.");
			break;
		}
		puts("Pulse ENTER para continuar...");
		getchar();
	}
	
	fclose(archivo);
	puts("Programa terminado.");
	return 0;
}
