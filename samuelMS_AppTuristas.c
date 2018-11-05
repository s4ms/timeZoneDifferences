/**
 ____________________________________________________________________________________________
| ----------------------Universidad Michoacana de San Nicolás de Hidalgo---------------------|
| ------------------------------Facultad de Ingeniería Eléctrica---------------------------- |
| --------------------------------Programación en Tiempo Real--------------------------------|
| Aplicación que compara dos ciudades seleccionadas por el usuario y muestra la diferencia 	 |
| de horas entre ambas y la diferencia de horas de la primer ciudad con respecto a México.	 |
| Si el usuario lo desea puede consultar el tiempo unix presionando un boton.				 |
| Programó: Samuel Medina Salgado															 |
|____________________________________________________________________________________________|


NOTA: Asegúrese de tener instalada y actualizada la librería gtk+3.
**/

#include<stdio.h>
#include<time.h>
#include<gtk/gtk.h>
#include<string.h>

void close_clicked(GtkWidget *widget, gpointer window);
void unix_time();
void compare_func();
static gboolean getLocalTime(gpointer data);


GtkWidget *menu1, *menu2;

GtkWidget *msg1, *msg2;
GtkWidget *unixLabel;

void compare_func(){
    gchar *inMenu1, *inMenu2,*message1, *message2;
    gint hour1 = 0;
	gint hour2 = 0;
	gint mexico = -5;
    gint difference, difBtwnMexico;
	GtkWidget *emWindow, *alertLabel, *okButton, *cont;
	emWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_default_size(GTK_WINDOW(emWindow), 250, 80);
	gtk_window_set_title(GTK_WINDOW(emWindow), "Error");
	cont = gtk_layout_new(NULL,NULL);
	okButton = gtk_button_new_with_label("OK");
	alertLabel = gtk_label_new("¡Please select 2 cities!");
	gtk_layout_put(GTK_LAYOUT(cont),alertLabel,65,20);
	gtk_layout_put(GTK_LAYOUT(cont), okButton, 100,45);
	gtk_container_add(GTK_CONTAINER(emWindow),cont);
	inMenu1 = gtk_combo_box_text_get_active_text (GTK_COMBO_BOX_TEXT(menu1));
	inMenu2 = gtk_combo_box_text_get_active_text (GTK_COMBO_BOX_TEXT(menu2));
	if(inMenu1 == NULL || inMenu2 == NULL){
		gtk_widget_show_all(emWindow);
		g_signal_connect(okButton,"clicked",G_CALLBACK(close_clicked),G_OBJECT(emWindow));
	}
	else {
		if(strcmp(inMenu1, "Barcelona (Spain)")==0) hour1 = 2;
		if(strcmp(inMenu1, "San Francisco (USA)")==0) hour1 = -7;
		if(strcmp(inMenu1, "Hong Kong (China)")==0) hour1 = 8;
		if(strcmp(inMenu1, "Beirut (Lebanon)")==0) hour1 = 3;
		if(strcmp(inMenu1, "Santiago de Chile (Chile)")==0) hour1 = -4;
		if(strcmp(inMenu1, "New York (USA)")==0) hour1 = -4;
		if(strcmp(inMenu1, "Rio de Janeiro (Brazil)")==0) hour1 = -3;
		if(strcmp(inMenu1, "Sidney (Australia)")==0) hour1 = 10;
		if(strcmp(inMenu1, "Cancún (México)")==0) hour1 = mexico;
		if(strcmp(inMenu1, "New Delhi (India)")==0) hour1 = 5;
		if(strcmp(inMenu2, "Barcelona (Spain)")==0) hour2 = 2;
		if(strcmp(inMenu2, "San Francisco (USA)")==0) hour2 = -7;
		if(strcmp(inMenu2, "Hong Kong (China)")==0) hour2 = 8;
		if(strcmp(inMenu2, "Beirut (Lebanon)")==0) hour2 = 3;
		if(strcmp(inMenu2, "Santiago de Chile (Chile)")==0) hour2 = -4;
		if(strcmp(inMenu2, "New York (USA)")==0) hour2 = -4;
		if(strcmp(inMenu2, "Rio de Janeiro (Brazil)")==0) hour2 = -3;
		if(strcmp(inMenu2, "Sidney (Australia)")==0) hour2 = 10;
		if(strcmp(inMenu2, "Cancún (México)")==0) hour2 = mexico;
		if(strcmp(inMenu2, "New Delhi (India)")==0) hour2 = 5;
		
		difference = (hour1 - hour2);
		if(difference <= 0) message2 = g_strdup_printf("The difference of hour between %s and %s is: %d hours", inMenu1, inMenu2, difference);
		else message2 = g_strdup_printf("The difference of hour between %s and %s is: +%d hours", inMenu1, inMenu2, difference);
		difBtwnMexico = (hour1 - mexico);
		if(difBtwnMexico <= 0)message1 = g_strdup_printf("The difference of hours of %s with respect to México is: %d hours", inMenu1, difBtwnMexico);
		else message1 = g_strdup_printf("The difference of hours of %s with respect to México is: +%d hours", inMenu1, difBtwnMexico);		
		gtk_label_set_text(GTK_LABEL(msg1),message1);
		gtk_label_set_text(GTK_LABEL(msg2),message2);	
	}
	
}
void unix_time(){
	time_t tiempoU = time(NULL);
	gchar *label;
	label = g_strdup_printf("%d",(int)time(NULL));
	gtk_label_set_text(GTK_LABEL(unixLabel),label);
}
static gboolean getLocalTime( gpointer data ){
    gint progress = 0;
    G_LOCK_DEFINE_STATIC( progress );
    gchar *label;
    time_t tim = time(0);
	struct tm *c_time = localtime(&tim);
    G_LOCK( progress );
    char output[128];
    strftime(output,128,"%c",c_time);
    label = g_strdup_printf( "%s", output);
    G_UNLOCK( progress );
    gtk_button_set_label( GTK_BUTTON( data ), label );
    g_free( label );
    return TRUE;
}


void close_clicked(GtkWidget *widget, gpointer window){
	gtk_widget_destroy(GTK_WIDGET(window));
}

int main(int argc, char *argv[]){
	GtkWidget *window, *welcome, *compareButton, *closeButton,*container;
	GtkWidget *utc,*changeZone, *compareWith, *unixTimeButton, *utcTimeButton;
	GtkWidget *close,*compare;

	
	
    gtk_init(&argc,&argv);
	
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(window), 570, 250);
    gtk_window_set_title(GTK_WINDOW(window), "World Time - Samuel Medina Salgado");
    
    container = gtk_layout_new(NULL,NULL);
	
	changeZone = gtk_label_new("Change Zone");
	utc = gtk_label_new("UTC time:");
	compareWith = gtk_label_new("Compare With");
	unixLabel =gtk_label_new(NULL);
	msg1 = gtk_label_new(NULL);
	msg2 = gtk_label_new(NULL);
	welcome = gtk_label_new("Select 2 cities: ");
	
	compare = gtk_button_new_with_label("Compare");
	close = gtk_button_new_with_label("Close App");
	utcTimeButton = gtk_button_new_with_label("UTC");
	unixTimeButton = gtk_button_new_with_label("Display Current Unix Time:");
	
	
	
	
	menu1 = gtk_combo_box_text_new();
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(menu1),"Barcelona (Spain)");
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(menu1),"San Francisco (USA)");
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(menu1),"Hong Kong (China)");
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(menu1),"Beirut (Lebanon)");
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(menu1),"Santiago de Chile (Chile)");
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(menu1),"New York (USA)");
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(menu1),"Rio de Janeiro (Brazil)");
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(menu1),"Sidney (Australia)");
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(menu1),"Cancún (México)");
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(menu1),"New Delhi (India)");
	menu2 = gtk_combo_box_text_new();
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(menu2),"Barcelona (Spain)");
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(menu2),"San Francisco (USA)");
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(menu2),"Hong Kong (China)");
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(menu1),"Beirut (Lebanon)");
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(menu2),"Santiago de Chile (Chile)");
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(menu2),"New York (USA)");
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(menu2),"Rio de Janeiro (Brazil)");
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(menu2),"Sidney (Australia)");
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(menu2),"Cancún (México)");
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(menu2),"New Delhi (India)");
	gtk_layout_put(GTK_LAYOUT(container), compare, 350,200);
	gtk_layout_put(GTK_LAYOUT(container),close, 450,200);
	gtk_layout_put(GTK_LAYOUT(container),changeZone,10,40);
	gtk_layout_put(GTK_LAYOUT(container),utc, 300, 40);
	gtk_layout_put(GTK_LAYOUT(container),utcTimeButton, 360, 35);
	gtk_layout_put(GTK_LAYOUT(container),compareWith, 10, 80);
	gtk_layout_put(GTK_LAYOUT(container), unixLabel, 200, 207);
	gtk_layout_put(GTK_LAYOUT(container),unixTimeButton, 10, 200);
	gtk_layout_put(GTK_LAYOUT(container), menu1, 100, 35);
	gtk_layout_put(GTK_LAYOUT(container), menu2, 100, 75);
	gtk_layout_put(GTK_LAYOUT(container), msg1,10,130);
	gtk_layout_put(GTK_LAYOUT(container), msg2,10,160);
	gtk_layout_put(GTK_LAYOUT(container), welcome,15,10);
	gtk_container_add(GTK_CONTAINER(window), container);
	
	g_signal_connect(unixTimeButton,"clicked", G_CALLBACK(unix_time),NULL);
	gdk_threads_add_timeout( 100, getLocalTime, (gpointer)utcTimeButton );
	
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_widget_show_all(window);
	g_signal_connect(compare,"clicked", G_CALLBACK(compare_func),NULL);
	g_signal_connect(close,"clicked",G_CALLBACK(close_clicked),G_OBJECT(window));
	
    gtk_main();
    return 0;
}
