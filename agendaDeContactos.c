#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char nombre[70];
	char numeroTelefono[20];
	char email[50];
} contacto;

int menu();
void agregar(FILE*, contacto);
void eliminar();
void editar();
int buscar(FILE*, contacto);
contacto pedirDatos();

int main(){
	system("color 0B");
	int opcion=1;
	FILE *archivo;
	contacto persona;
	int existe;
	
	archivo = fopen("info.dat", "wb+");
	
		
		while(opcion){
			opcion = menu();
			switch(opcion){
				case 1:
					existe = buscar(archivo, persona);
					if(existe){
						printf("El contacto ya se encuentra registrado");
					}
					else {
						persona = pedirDatos();
						agregar(archivo, persona);
						printf("Se ha guardado el nuevo contacto\n");
					}
					break;
				case 2:
						
					break;
				case 3:
					break;
				case 4:
					break;	
				case 0:
					printf("programa finalizado...");
					break;
				default:
					printf("Opcion incorrecta, reingresar numero...\n");
					break;
			}
		};
	
	
	fclose(archivo);
	return 0;
}
/******************************************************************************/
/*FUNCION DE MENU PRINCIPAL, SIMPLE IMPRESION DE PANTALLA                     */
/******************************************************************************/	
	int menu(){
		int opcion;
		do{
		system("clear");	
		printf("\t-ELEGIR ACCION-\n");
		printf("\t  [1] AGREGAR\n");
		printf("\t  [2] ELIMINAR\n");
		printf("\t  [3] EDITAR\n");
		printf("\t  [4] LISTAR AGENDA\n");
		printf("\t  [5] BUSCAR\n");
		printf("\t  [0] SALIR\n");
		scanf("%d", &opcion);
		}while(opcion<0 || opcion>5);
	
	return opcion;	
	}
		
/******************************************************************************/
/*RECIBE UNA CORRIENTE DE DATOS DE TIPO ARCHIVO PARA AGREGAR NUEVO CONTACTO   */		
/******************************************************************************/		
	void agregar(FILE* arch, contacto pers){
		fseek(arch,sizeof(contacto)*(-1L),SEEK_CUR);
		fwrite(&pers, sizeof(contacto) ,1,arch);
	}
		
/******************************************************************************/
/*RECIBE VARIABLE TIPO CONTACTO E INDICA SI YA EXISTE EN LA AGENDA            */
/******************************************************************************/
	int buscar(FILE *arch, contacto pers){
		contacto aux;
		
		rewind(arch);
		while(!feof(arch)){
			fread(&aux, sizeof(contacto), 1, arch);
				if(aux.nombre == pers.nombre)
					return 1;
		}
	return 0;		
	}
		
/******************************************************************************/
/*PIDE LOS DATOS PARA GUARDAR UN NUEVO CONTACTO                               */
/******************************************************************************/		
	contacto pedirDatos(){
		contacto c;
		printf("Ingresar nombre: ");
		scanf("%s", &c.nombre);
		printf("Ingresar telefono: ");
		scanf("%s", &c.numeroTelefono);
		printf("Ingresar correo electronico: ");
		scanf("%s", &c.email);
		return c;
	}
/******************************************************************************/
/*PIDE LOS DATOS PARA GUARDAR UN NUEVO CONTACTO                               */
/******************************************************************************/	
	void eliminar(FILE *arch, contacto pers){
		
	}
/******************************************************************************/
		
/******************************************************************************/		
