#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fileops.h"
#include "contacto.h"

static const char *FILENAME = "info.dat";
FILE *archivo;

int buscarContacto(const contacto *pers) {
	archivo = fopen(FILENAME, "ab");
	contacto aux;
	rewind(archivo);
	while (fread(&aux, sizeof(contacto), 1, archivo) == 1) {
		if (strcmp(aux.nombre, pers->nombre) == 0){
			mostrarContacto(aux);
			return 1;
		}	
	}
	fclose(archivo);
	return 0;
}

void agregarContacto(const contacto *pers) {
	archivo = fopen(FILENAME, "ab");
	fseek(archivo, 0, SEEK_END);
	fwrite(pers, sizeof(contacto), 1, archivo);
	fclose(archivo);
}

void eliminarContacto(const contacto *pers) {
	archivo = fopen(FILENAME, "rb");
	FILE *temp = fopen("temp.dat", "wb");
	if (!archivo || !temp) { perror("Error archivo"); return; }
	
	contacto aux;
	int encontrado=0;
	
	while (fread(&aux, sizeof(contacto), 1, archivo) == 1) {
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
	
	fclose(archivo); fclose(temp);
	remove(FILENAME);
	rename("temp.dat", FILENAME);
}

void editarContacto(const contacto *pers) {
	archivo = fopen(FILENAME, "rb+");
	contacto aux;
	rewind(archivo);
	while (fread(&aux, sizeof(contacto), 1, archivo) == 1) {
		if (strcmp(aux.nombre, pers->nombre) == 0){
			printf("Ingresar nuevamente los datos...\n");
			aux = pedirDatos();
			fseek(archivo, -sizeof(contacto), SEEK_CUR);
			fwrite(&aux, sizeof(contacto), 1, archivo);
			fflush(archivo);
		}	
	}
	fclose(archivo);
}

void listarContactos(FILE *arch) {
	archivo = fopen(FILENAME, "rb");
	contacto aux;
	rewind(archivo);
	while (fread(&aux, sizeof(contacto), 1, archivo) == 1) {
		printf("Nombre: %s \nTel: %s \nEmail: %s\n",
			   aux.nombre, aux.numeroTelefono, aux.eMail);
		printf("\t -----\n");
	}
	fclose(archivo);
}

void mostrarContacto(contacto persona) {
	printf("Nombre: %s\n", persona.nombre);
	printf("Telefono: %s\n", persona.numeroTelefono);
	printf("E-mail: %s\n", persona.eMail);
}
	
	
	
