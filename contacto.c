#include <stdio.h>
#include "contacto.h"
#include "ui.h"      // si usas limpiarBuffer() de ui.c

contacto pedirDatos(void) {
	contacto c;
	printf("Ingresar nombre: ");
	limpiarBuffer();                     // o getchar() según tu ui
	fgets(c.nombre, NOMBRE_MAX, stdin);
	
	printf("Ingresar teléfono: ");
	fgets(c.numeroTelefono, TELEFONO_MAX, stdin);
	
	printf("Ingresar correo electrónico: ");
	fgets(c.eMail, EMAIL_MAX, stdin);
	
	return c;
}

contacto pedirNombre(void) {
	contacto c;
	printf("Ingresar nombre: ");
	limpiarBuffer();
	fgets(c.nombre, NOMBRE_MAX, stdin);
	return c;
}
