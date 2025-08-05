#ifndef FILEOPS_H
#define FILEOPS_H

#include <stdio.h>
#include "contacto.h"

int buscarContacto(const contacto *pers);
void agregarContacto(const contacto *pers);
void eliminarContacto(const contacto *pers);
void editarContacto(const contacto *pers);
void listarContactos();
void mostrarContacto(contacto);
int obtenerContactos(contacto[], int);
int eliminarContactoPorNombre(const char *nombre);

#endif // FILEOPS_H
