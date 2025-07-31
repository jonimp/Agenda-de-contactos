#include <gtk/gtk.h>
#include "contacto.h"
#include "fileops.h"

static void on_activate(GtkApplication *app, gpointer user_data);
static void on_agregar_contacto_clicked(GtkWidget *widget, gpointer data);

/*---------------------| ARRANQUE DEL ENTORNO GRAFICO |-----------------------*/
void iniciarGTK(int argc, char *argv[]) {
	GtkApplication *app;
	int status;
	
	app = gtk_application_new("com.ejemplo.agenda", G_APPLICATION_FLAGS_NONE);
	g_signal_connect(app, "activate", G_CALLBACK(on_activate), NULL);
	status = g_application_run(G_APPLICATION(app), argc, argv);
	g_object_unref(app);
}
/*----------------------------------------------------------------------------*/


/*----------------| CONTRUCTOR DE LA INTERFAZ GRAFICA |-----------------------*/
static void on_activate(GtkApplication *app, gpointer user_data) {
	GtkWidget *window;
	GtkWidget *button;
	GtkWidget *box;
	
	// Crear ventana
	window = gtk_application_window_new(app);
	gtk_window_set_title(GTK_WINDOW(window), "Agenda de Contactos");
	gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);
	
	// Crear contenedor vertical (GtkBox)
	box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
	gtk_container_add(GTK_CONTAINER(window), box);
	
	// Crear botón
	button = gtk_button_new_with_label("Agregar Contacto");
	g_signal_connect(button, "clicked", G_CALLBACK(on_agregar_contacto_clicked), NULL);
	
	// Agregar botón al contenedor
	gtk_box_pack_start(GTK_BOX(box), button, TRUE, TRUE, 0);
	
	// Mostrar todo
	gtk_widget_show_all(window);
}
/*----------------------------------------------------------------------------*/

/*---------------------| BOTON AGREGAR CONTACTO |-----------------------------*/
static void on_agregar_contacto_clicked(GtkWidget *widget, gpointer data) {
	GtkWidget *dialog, *content_area;
	GtkWidget *grid;
	GtkWidget *nombre_label, *telefono_label, *email_label;
	GtkWidget *nombre_entry, *telefono_entry, *email_entry;
	
	GtkWindow *parent_window = GTK_WINDOW(gtk_widget_get_toplevel(widget));
	
	// Crear el diálogo modal
	dialog = gtk_dialog_new_with_buttons("Agregar Contacto",
										 parent_window,
										 GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
										 "_Guardar", GTK_RESPONSE_OK,
										 "_Cancelar", GTK_RESPONSE_CANCEL,
										 NULL);
	
	content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
	
	// Crear un grid para organizar los elementos
	grid = gtk_grid_new();
	gtk_grid_set_row_spacing(GTK_GRID(grid), 5);
	gtk_grid_set_column_spacing(GTK_GRID(grid), 5);
	gtk_container_set_border_width(GTK_CONTAINER(grid), 10);
	gtk_container_add(GTK_CONTAINER(content_area), grid);
	
	// Etiquetas y campos de entrada
	nombre_label = gtk_label_new("Nombre:");
	nombre_entry = gtk_entry_new();
	gtk_grid_attach(GTK_GRID(grid), nombre_label, 0, 0, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), nombre_entry, 1, 0, 1, 1);
	
	telefono_label = gtk_label_new("Teléfono:");
	telefono_entry = gtk_entry_new();
	gtk_grid_attach(GTK_GRID(grid), telefono_label, 0, 1, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), telefono_entry, 1, 1, 1, 1);
	
	email_label = gtk_label_new("Email:");
	email_entry = gtk_entry_new();
	gtk_grid_attach(GTK_GRID(grid), email_label, 0, 2, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), email_entry, 1, 2, 1, 1);
	
	gtk_widget_show_all(dialog);
	
	// Esperar respuesta del usuario
	gint result = gtk_dialog_run(GTK_DIALOG(dialog));
	if (result == GTK_RESPONSE_OK) {
		const char *nombre = gtk_entry_get_text(GTK_ENTRY(nombre_entry));
		const char *telefono = gtk_entry_get_text(GTK_ENTRY(telefono_entry));
		const char *email = gtk_entry_get_text(GTK_ENTRY(email_entry));
		
		// Crear estructura contacto y guardar
		contacto nuevo;
		strncpy(nuevo.nombre, nombre, sizeof(nuevo.nombre));
		strncpy(nuevo.numeroTelefono, telefono, sizeof(nuevo.numeroTelefono));
		strncpy(nuevo.eMail, email, sizeof(nuevo.eMail));
		
		// Guardar el contacto
		agregarContacto(nuevo);
		
		// Mensaje de éxito
		GtkWidget *msg = gtk_message_dialog_new(parent_window,
												GTK_DIALOG_DESTROY_WITH_PARENT,
												GTK_MESSAGE_INFO,
												GTK_BUTTONS_OK,
												"¡Contacto guardado con éxito!");
		gtk_dialog_run(GTK_DIALOG(msg));
		gtk_widget_destroy(msg);
	}
	
	gtk_widget_destroy(dialog);
}

