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

#endif // FILEOPS_H
