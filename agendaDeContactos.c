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
void eliminar(FILE*, contacto);
void editar();
int buscar(FILE*, contacto);
void listar(FILE*);
contacto pedirDatos();
void limpiarBuffer();

int main(){
	printf("\033[%dm", 50);
	int opcion=1;
	FILE *archivo;
	contacto persona;
	int existe;
	
	archivo = fopen("info.dat", "wb+");
	
		
		while(opcion){
			opcion = menu();
			switch(opcion){
				case 1:
					persona = pedirDatos();
					existe = buscar(archivo, persona);
						if(existe){
							printf("El contacto ya se encuentra registrado");
						}
						else {
							agregar(archivo, persona);
							printf("Se ha guardado el nuevo contacto\n");
						}
				break;
				case 2:
					printf("Nombre del contacto a eliminar...");
					fgets(persona.nombre, sizeof(persona.nombre), stdin);
					existe = buscar(archivo, persona);
						if(existe){
							eliminar(archivo, persona);
							printf("El contacto fue eliminado de la lista");
						}
						else {
							printf("No existe contacto llamado: %s", persona.nombre);
						}
						archivo = fopen("info.dat", "ab+");
				break;
				case 3:
					printf("Nombre del contacto a modificar...");
					fgets(persona.nombre, sizeof(persona.nombre), stdin);
					existe = buscar(archivo, persona);
					if(existe){
						editar(archivo);
						printf("El contacto fue modificado");
					}
					else {
						printf("No existe contacto llamado %s", persona.nombre);
					}
				break;
				case 4:
					listar(archivo);
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
				if(strcmp(aux.nombre, pers.nombre))
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
		limpiarBuffer();
		fgets(c.nombre, sizeof(c.nombre), stdin);
		printf("Ingresar telefono: ");
		fgets(c.numeroTelefono, sizeof(c.numeroTelefono), stdin);
		printf("Ingresar correo electronico: ");
		fgets(c.email, sizeof(c.email), stdin);
		
		printf("%s", c.nombre);
		printf("%s", c.numeroTelefono);
		printf("%s", c.email);
		getchar();
		return c;
	}
/******************************************************************************/
/*ELIMINA EL CONTACTO ELEGIDO                                                 */
/******************************************************************************/	
	void eliminar(FILE *arch, contacto pers){
		contacto aux;
		
		FILE *temp = fopen("temp.bin", "wb");
		if (temp == NULL) {
			perror("No se pudo abrir el archivo temporal");
			return;
		}
		
		rewind(arch);
		while (fread(&aux, sizeof(contacto), 1, arch) == 1) {
			if (strcmp(aux.nombre, pers.nombre) != 0) {
				fwrite(&aux, sizeof(contacto), 1, temp);
			}
		}
		
		fclose(arch);
		fclose(temp);
		
		remove("info.dat");
		rename("temp.bin", "info.dat");
		
		
	}
/******************************************************************************/
/*BUSCA EL CONTACTO A MODIFICAR Y SE PISAN LOS NUEVOS DATOS                   */		
/******************************************************************************/		
	void editar(FILE* arch){
		contacto c;
		
		c = pedirDatos();
		agregar(arch, c);
	}
/******************************************************************************/
/*BUSCA EL CONTACTO A MODIFICAR Y SE PISAN LOS NUEVOS DATOS                   */		
/******************************************************************************/		
	void listar(FILE* arch){
		
		contacto aux;
		
		rewind(arch);
		while(!feof(arch)){
			fread(&aux, sizeof(contacto), 1, arch);
			printf("nombre: %s\t Telefono: %s\t Email: %s\t\n", aux.nombre, aux.numeroTelefono, aux.email);
			getchar();
		}	
	}
/******************************************************************************/
/*LIMPIA EL BUFER DE ENTRADA                                                  */		
/******************************************************************************/
		void limpiarBuffer() {
			int c;
			while ((c = getchar()) != '\n' && c != EOF);
		}
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/******************************************************************************/		
