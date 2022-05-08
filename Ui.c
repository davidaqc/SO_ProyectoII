#include <gtk/gtk.h>
#include "Marcianos.c"

#define N 50


/*gcc `pkg-config --cflags gtk+-3.0` -o UI  Ui.c `pkg-config --libs gtk+-3.0` -export-dynamic*/

GtkWidget  *window;
GtkWidget  *rtos;
GtkWidget  *container;
GtkWidget  *interactive;
GtkWidget  *text1;
GtkWidget  *text2;
GtkBuilder *builder;
int tipo;
int algoritmo;
int modo;
int cantMarcianos = 0;
struct Marciano marcianosInteractivos[N];
struct Marciano marcianosRTOS[N];

static void activate (GtkApplication *app, gpointer user_data) {
  builder = gtk_builder_new_from_file("UIP2.glade");
  window = GTK_WIDGET( gtk_builder_get_object(builder, "window"));
  g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
  gtk_builder_connect_signals(builder, NULL);
  container = GTK_WIDGET( gtk_builder_get_object(builder, "container"));
  rtos = GTK_WIDGET( gtk_builder_get_object(builder, "rtos"));
  interactive = GTK_WIDGET( gtk_builder_get_object(builder, "interactive"));
  text1 = GTK_WIDGET( gtk_builder_get_object(builder, "tit"));
  text2 = GTK_WIDGET( gtk_builder_get_object(builder, "selectionText"));
  gtk_widget_show_all(window);
  gtk_main();
}

int main (int argc, char ** argv) {
 GtkApplication *app;
 int ret;
 app = gtk_application_new ("in.aducators", G_APPLICATION_FLAGS_NONE);
 g_signal_connect (app, "activate", G_CALLBACK(activate), NULL);
 ret = g_application_run (G_APPLICATION(app), argc, argv);
 g_object_unref (app);
 return ret;
}

void interactive_clicked_cb(GtkButton *b){
  tipo = 1;
  GtkWidget  *interactive_Window;
  GtkWidget  *interactiveContainer;
  GtkWidget  *interactiveText;
  GtkWidget  *fcfsButton;
  GtkWidget  *priorityButton;
  GtkWidget  *srtnButton;
  interactive_Window = GTK_WIDGET( gtk_builder_get_object(builder,       "interactive_Window"));
  g_signal_connect(interactive_Window, "destroy", G_CALLBACK(gtk_main_quit),   NULL);
  gtk_builder_connect_signals(builder, NULL);
  interactiveContainer = GTK_WIDGET( gtk_builder_get_object(builder,  "interactiveContainer"));
  interactiveText = GTK_WIDGET( gtk_builder_get_object(builder, "interactiveText"));
  fcfsButton = GTK_WIDGET( gtk_builder_get_object(builder, "fcfsButton"));
  priorityButton = GTK_WIDGET( gtk_builder_get_object(builder, "priorityButton"));
  srtnButton = GTK_WIDGET( gtk_builder_get_object(builder, "srtnButton"));
  gtk_widget_show_all(interactive_Window);
  gtk_widget_hide(window);
}

void rtos_clicked_cb(GtkButton *b){
  tipo = 2;
  GtkWidget  *rtos_Window;
  GtkWidget  *rtosContainer;
  GtkWidget  *rtosText;
  GtkWidget  *rmButton;
  GtkWidget  *edfButton;
  rtos_Window = GTK_WIDGET( gtk_builder_get_object(builder, "rtos_Window"));
  g_signal_connect(rtos_Window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
  gtk_builder_connect_signals(builder, NULL);
  rtosContainer = GTK_WIDGET( gtk_builder_get_object(builder, "rtosContainer"));
  rtosText = GTK_WIDGET( gtk_builder_get_object(builder, "rtosText"));
  rmButton = GTK_WIDGET( gtk_builder_get_object(builder, "rmButton"));
  edfButton = GTK_WIDGET( gtk_builder_get_object(builder, "edfButton"));
  gtk_widget_show_all(rtos_Window);
  gtk_widget_hide(window);
}
void back(GtkButton *b,GtkWidget  *win ){
  gtk_widget_show_all(window);
  gtk_widget_hide(win);
}

void showGameWin(GtkWidget  *win){
  GtkWidget  *windowGame;
  windowGame = GTK_WIDGET( gtk_builder_get_object(builder, "gameWindow"));
  g_signal_connect(windowGame, "destroy", G_CALLBACK(gtk_main_quit), NULL);
  gtk_builder_connect_signals(builder, NULL);
  gtk_widget_show_all(windowGame);
  gtk_widget_hide(win);
}

void showOpWin(GtkWidget  *win){
  GtkWidget  *windowOp;
  windowOp = GTK_WIDGET( gtk_builder_get_object(builder, "opWindow"));
  g_signal_connect(windowOp, "destroy", G_CALLBACK(gtk_main_quit), NULL);
  gtk_builder_connect_signals(builder, NULL);
  gtk_widget_show_all(windowOp);
  gtk_widget_hide(win);

}

void showrtosMartiansWindow(){
  GtkWidget  *windowRtosMartians;
  windowRtosMartians = GTK_WIDGET( gtk_builder_get_object(builder, "rtosMartiansWindows"));
  gtk_builder_connect_signals(builder, NULL);
  gtk_widget_show_all(windowRtosMartians);
}

void showinteractiveMartiansWindow(){
  GtkWidget  *windowInteractiveMartians;
  windowInteractiveMartians = GTK_WIDGET( gtk_builder_get_object(builder, "interactiveMartiansWindows"));
  gtk_builder_connect_signals(builder, NULL);
  gtk_widget_show_all(windowInteractiveMartians);
}


void on_edfButton_clicked(GtkButton *b ,GtkWidget  *win ){
  algoritmo = 1;
  showOpWin(win);
}
void on_rmButton_clicked(GtkButton *b,GtkWidget  *win  ){
  algoritmo = 2;
  showOpWin(win);
}
void on_fcfsButton_clicked(GtkButton *b ,GtkWidget  *win ){
  algoritmo = 3;
  showOpWin(win);
}
void on_priorityButton_clicked(GtkButton *b ,GtkWidget  *win ){
  algoritmo = 4;
  showOpWin(win);
}
void on_srtnButton_clicked(GtkButton *b ,GtkWidget  *win ){
  algoritmo = 5;
  showOpWin(win);
}

void on_manualButton_clicked(GtkButton *b ,GtkWidget  *win ){
  modo = 1;
  showGameWin(win);
}
void on_automaticButton_clicked(GtkButton *b ,GtkWidget  *win ){
  modo = 0;
  if(tipo == 1){
    showGameWin(win);
    cantMarcianos = 0;
    showinteractiveMartiansWindow();
    
  }else{
    showGameWin(win);
    showrtosMartiansWindow();
  }

}

void on_contButtonR_clicked(GtkButton *b, GtkWidget  *win){
	for(int i = 0; i < cantMarcianos; i++) {

        printf("%d ", marcianosRTOS[i].energy);
    
    printf("\n");
} 

	showGameWin(win);
gtk_widget_hide(win);
}

void on_addrtosButton_clicked(GtkButton *b){
  GtkEntry  *energyRtos;
  GtkEntry  *periodRtos;
  energyRtos = GTK_ENTRY( gtk_builder_get_object(builder, "energyRtos"));
  periodRtos = GTK_ENTRY( gtk_builder_get_object(builder, "periodRtos"));
  gtk_builder_connect_signals(builder, NULL);

  struct Marciano marciano1 = {0,0,0,0,0,0,0};
  marciano1.energy =  atoi(gtk_entry_get_text(energyRtos));
  marciano1.period =  atoi(gtk_entry_get_text(periodRtos));
  marcianosRTOS[cantMarcianos] = marciano1;
  cantMarcianos = cantMarcianos + 1;
  gtk_editable_delete_text(GTK_EDITABLE(energyRtos),0,-1);
  gtk_editable_delete_text(GTK_EDITABLE(periodRtos),0,-1);

}

void on_contIntButton_clicked(GtkButton *b, GtkWidget  *win){
  showGameWin(win);
  gtk_widget_hide(win);
}

void on_addInteractiveButton_clicked(GtkButton *b){
  GtkEntry  *priorityInteractive;
  GtkEntry *arrivalInteractive;
  GtkEntry  *energyInteractiv;
  GtkEntry  *periodInteractiv;
  priorityInteractive = GTK_ENTRY( gtk_builder_get_object(builder, "priorityInteractive"));
  periodInteractiv = GTK_ENTRY( gtk_builder_get_object(builder, "periodInteractiv"));
  energyInteractiv = GTK_ENTRY( gtk_builder_get_object(builder, "energyInteractiv"));
  arrivalInteractive = GTK_ENTRY( gtk_builder_get_object(builder, "arrivalInteractive"));
  gtk_builder_connect_signals(builder, NULL);
    struct Marciano marciano1 = {0,0,0,0,0,0,0};
    marciano1.priority =  atoi(gtk_entry_get_text(priorityInteractive));
    marciano1.energy =  atoi(gtk_entry_get_text(energyInteractiv));
    marciano1.period =  atoi(gtk_entry_get_text(periodInteractiv));
    marciano1.arrivalTime =  atoi(gtk_entry_get_text(arrivalInteractive));
    marcianosInteractivos[cantMarcianos] = marciano1;
    cantMarcianos = cantMarcianos + 1;
    gtk_editable_delete_text(GTK_EDITABLE(priorityInteractive),0,-1);
    gtk_editable_delete_text(GTK_EDITABLE(energyInteractiv),0,-1);
    gtk_editable_delete_text(GTK_EDITABLE(periodInteractiv),0,-1);
    gtk_editable_delete_text(GTK_EDITABLE(arrivalInteractive),0,-1);
}
















