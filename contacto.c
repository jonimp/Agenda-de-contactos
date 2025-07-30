#include <stdio.h>
#include <string.h>
#include "contacto.h"
#include "ui.h"      // si usas limpiarBuffer() de ui.c

contacto pedirDatos(void) {
	contacto c;
	printf("Ingresar nombre: ");
	fgets(c.nombre, NOMBRE_MAX, stdin);
	c.nombre[strcspn(c.nombre, "\n")] = '\0';
	
	printf("Ingresar telefono: ");
	fgets(c.numeroTelefono, TELEFONO_MAX, stdin);
	c.numeroTelefono[strcspn(c.numeroTelefono, "\n")] = '\0';
	
	printf("Ingresar correo electronico: ");
	fgets(c.eMail, EMAIL_MAX, stdin);
	c.eMail[strcspn(c.eMail, "\n")] = '\0';
	
	return c;
}

contacto pedirNombre(void) {
	contacto c;
	printf("Ingresar nombre: ");
	fgets(c.nombre, NOMBRE_MAX, stdin);
	c.nombre[strcspn(c.nombre, "\n")] = '\0';
	
	return c;
}
