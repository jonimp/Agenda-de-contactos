#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fileops.h"
#include "contacto.h"

static const char *FILENAME = "info.dat";

int buscarContacto(FILE *arch, const contacto *pers) {
	contacto aux;
	rewind(arch);
	while (fread(&aux, sizeof(contacto), 1, arch) == 1) {
		if (strcmp(aux.nombre, pers->nombre) == 0){
			mostrarContacto(aux);
			return 1;
		}	
	}
	return 0;
}

void agregarContacto(FILE *arch, const contacto *pers) {
	fseek(arch, 0, SEEK_END);
	fwrite(pers, sizeof(contacto), 1, arch);
}

void eliminarContacto(const contacto *pers) {
	FILE *arch = fopen(FILENAME, "rb");
	FILE *temp = fopen("temp.dat", "wb");
	if (!arch || !temp) { perror("Error archivo"); return; }
	
	contacto aux;
	int encontrado=0;
	
	while (fread(&aux, sizeof(contacto), 1, arch) == 1) {
		if (strcmp(aux.nombre, pers->nombre) != 0){
			fwrite(&aux, sizeof(contacto), 1, temp);
		}
		else {
			encontrado = 1;
		}
	}
	
	if (encontrado)
		printf("Contacto eliminado exitosamente.\n");
	else
		printf("Contacto no encontrado.\n");
	
	fclose(arch); fclose(temp);
	remove(FILENAME);
	rename("temp.dat", FILENAME);
}

void editarContacto(FILE *arch, const contacto *pers) {
	contacto aux;
	rewind(arch);
	while (fread(&aux, sizeof(contacto), 1, arch) == 1) {
		if (strcmp(aux.nombre, pers->nombre) == 0){
			printf("Ingresar nuevamente los datos...\n");
			aux = pedirDatos();
			fseek(arch, -sizeof(contacto), SEEK_CUR);
			fwrite(&aux, sizeof(contacto), 1, arch);
			fflush(arch);
		}	
	}
}

void listarContactos(FILE *arch) {
	contacto aux;
	rewind(arch);
	while (fread(&aux, sizeof(contacto), 1, arch) == 1) {
		printf("Nombre: %s \nTel: %s \nEmail: %s\n",
			   aux.nombre, aux.numeroTelefono, aux.eMail);
		printf("\t -----\n");
	}
}

void mostrarContacto(contacto persona) {
	printf("Nombre: %s\n", persona.nombre);
	printf("Telefono: %s\n", persona.numeroTelefono);
	printf("E-mail: %s\n", persona.eMail);
}
	
	
	
