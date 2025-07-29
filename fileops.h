#ifndef FILEOPS_H
#define FILEOPS_H

#include <stdio.h>
#include "contacto.h"

int buscarContacto(FILE *arch, const contacto *pers);
void agregarContacto(FILE *arch, const contacto *pers);
void eliminarContacto(const contacto *pers);
void editarContacto(FILE *arch, const contacto *pers);
void listarContactos(FILE *arch);
void mostrarContacto(contacto);

#endif // FILEOPS_H
