#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fileops.h"

static const char *FILENAME = "info.dat";

int buscarContacto(FILE *arch, const contacto *pers) {
	contacto aux;
	rewind(arch);
	while (fread(&aux, sizeof contacto, 1, arch) == 1) {
		if (strcmp(aux.nombre, pers->nombre) == 0)
			return 1;
	}
	return 0;
}

void agregarContacto(FILE *arch, const contacto *pers) {
	fseek(arch, 0, SEEK_END);
	fwrite(pers, sizeof contacto, 1, arch);
}

void eliminarContacto(const contacto *pers) {
	FILE *arch = fopen(FILENAME, "rb");
	FILE *temp = fopen("temp.dat", "wb");
	if (!arch || !temp) { perror("Error archivo"); return; }
	
	contacto aux;
	while (fread(&aux, sizeof aux, 1, arch) == 1) {
		if (strcmp(aux.nombre, pers->nombre) != 0)
			fwrite(&aux, sizeof aux, 1, temp);
	}
	fclose(arch); fclose(temp);
	remove(FILENAME);
	rename("temp.dat", FILENAME);
}

void editarContacto(FILE *arch, const contacto *pers) {
	// Una estrategia: eliminar el viejo y agregar el nuevo
	eliminarContacto(pers);
	agregarContacto(arch, pers);
}

void listarContactos(FILE *arch) {
	contacto aux;
	rewind(arch);
	while (fread(&aux, sizeof aux, 1, arch) == 1) {
		printf("Nombre: %sTel: %sEmail: %s\n",
			   aux.nombre, aux.numeroTelefono, aux.email);
	}
}
