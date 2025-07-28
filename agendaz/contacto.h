#ifndef CONTACTO_H
#define CONTACTO_H

#define NOMBRE_MAX 70
#define TELEFONO_MAX 20
#define EMAIL_MAX 50

typedef struct {
	char nombre[NOMBRE_MAX];
	char numeroTelefono[TELEFONO_MAX];
	char eMail[EMAIL_MAX];
}contacto;

contacto pedirDatos(void);
contacto pedirNombre(void);

#endif
