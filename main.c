#include <stdio.h>
#include "contacto.h"
#include "fileops.h"
#include "ui.h"

int main(void) {
	int opcion;
	contacto persona;
	FILE *archivo = fopen("info.dat", "ab+");
	if (!archivo) { perror("No se puede abrir info.dat"); return 1; }
	fclose(archivo);
	
	while ((opcion = menu()) != 0) {
		switch (opcion) {
		case 1:
			archivo = fopen("info.dat", "ab");
			persona = pedirDatos();
			if (buscarContacto(archivo, &persona))
				puts("Ya existe ese contacto.");
			else {
				agregarContacto(archivo, &persona);
				puts("Contacto guardado.");
			}
			fclose(archivo);
			break;
		case 2:
			archivo = fopen("info.dat", "rb");
			persona = pedirNombre();
			if (buscarContacto(archivo, &persona)) {
				eliminarContacto(&persona);
			} else
				printf("No existe: %s", persona.nombre);
			fclose(archivo);
			break;
		case 3:
			persona = pedirNombre();
			archivo = fopen("info.dat", "rb+");
			if (buscarContacto(archivo, &persona)) {
				editarContacto(archivo, &persona);
				puts("Contacto modificado.");
			} else
				printf("No existe: %s", persona.nombre);
			fclose(archivo);
			break;
		case 4:
			archivo = fopen("info.dat", "rb");
			listarContactos(archivo);
			fclose(archivo);
			break;
		case 5:
			persona = pedirNombre();
			archivo = fopen("info.dat", "rb");
			if (buscarContacto(archivo, &persona))
				puts("\t-----");
			else
				puts("Contacto no encontrado.");
			fclose(archivo);
			break;
		}
		puts("Pulse ENTER para continuar...");
		getchar();
	}
	
	puts("Programa terminado.");
	return 0;
}
