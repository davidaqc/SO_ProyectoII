// gcc `pkg-config --cflags gtk+-3.0` -c  matriz_logica.c `pkg-config --libs gtk+-3.0`
// gcc `pkg-config --cflags gtk+-3.0` -o example-0 matriz_logica.o  main.c -lpthread `pkg-config --libs gtk+-3.0`

#include <gtk/gtk.h>


#include <time.h> //for time()
#include <stdio.h>

#include <stdlib.h>
#include <unistd.h>
#include "matriz_logica.c"
#include <pthread.h>

#define WINDOW_SIZE 50

#define N 50

struct Marciano1 {
  int posX;
  int posY;
  int energy;
  int period;
  int id;
  int priority;
  int arrivalTime;
};



/*gcc `pkg-config --cflags gtk+-3.0` -o UI  Ui.c -lpthread `pkg-config --libs gtk+-3.0` -export-dynamic*/

gboolean threadController(gpointer);
gboolean updatePosition(gpointer);

int start_martian_no = 0;

GtkWidget *windowLAB;
GtkWidget *fixed;
GtkWidget *img;
GtkWidget *label[10];
GtkWidget *martian[10];

int started = 0;

int no_procesos;

int id = 0;

int x = 60;

pthread_t threads[10];

int martian_Started = -1;

struct Marciano marcianosFinal[N];

int laberinto[N][N] = {{1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
                       {1, 1, 0, 0, 0, 0, 1, 1, 0, 0},
                       {0, 1, 1, 1, 1, 1, 1, 0, 0, 0},
                       {0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
                       {1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
                       {1, 0, 0, 1, 0, 0, 1, 1, 1, 0},
                       {1, 0, 1, 1, 1, 1, 1, 0, 1, 0},
                       {0, 0, 0, 1, 0, 0, 1, 0, 1, 0},
                       {0, 0, 0, 1, 0, 0, 1, 0, 1, 0},
                       {0, 0, 0, 0, 0, 1, 1, 0, 1, 1}};

// function that calls the solver file

GtkWidget *window;
GtkWidget *rtos;
GtkWidget *container;
GtkWidget *interactive;
GtkWidget *text1;
GtkWidget *text2;
GtkBuilder *builder;
int tipo;
int algoritmo;
int modo;
int cantMarcianos = 0;
struct Marciano marcianosInteractivos[N];
struct Marciano marcianosRTOS[N];

void destroy(GtkWidget *, gpointer);

void *call_solve(void *arg)
{
  //martian_Started++;
  //g_print("Hola desde solve");
  //solve_matrix(marcianosInteractivos[start_martian_no], fixed, martian[martian_Started]);

  // solve_matrix(marcianos[start_martian_no], fixed, martian[*iptr], label[*iptr]);
  return NULL;
}

struct PCB
{
  int pid, arrival, burst, turnaround;
};

struct PCB p[10], temp;

static void activate(GtkApplication *app, gpointer user_data)
{
  builder = gtk_builder_new_from_file("UIP2.glade");
  window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
  g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
  gtk_builder_connect_signals(builder, NULL);
  container = GTK_WIDGET(gtk_builder_get_object(builder, "container"));
  rtos = GTK_WIDGET(gtk_builder_get_object(builder, "rtos"));
  interactive = GTK_WIDGET(gtk_builder_get_object(builder, "interactive"));
  text1 = GTK_WIDGET(gtk_builder_get_object(builder, "tit"));
  text2 = GTK_WIDGET(gtk_builder_get_object(builder, "selectionText"));
  gtk_widget_show_all(window);
  gtk_main();
}

int main(int argc, char **argv)
{
  GtkApplication *app;
  int ret;
  app = gtk_application_new("in.aducators", G_APPLICATION_FLAGS_NONE);
  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
  ret = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);
  return ret;
}

void interactive_clicked_cb(GtkButton *b)
{
  tipo = 1;
  GtkWidget *interactive_Window;
  GtkWidget *interactiveContainer;
  GtkWidget *interactiveText;
  GtkWidget *fcfsButton;
  GtkWidget *priorityButton;
  GtkWidget *srtnButton;
  interactive_Window = GTK_WIDGET(gtk_builder_get_object(builder, "interactive_Window"));
  g_signal_connect(interactive_Window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
  gtk_builder_connect_signals(builder, NULL);
  interactiveContainer = GTK_WIDGET(gtk_builder_get_object(builder, "interactiveContainer"));
  interactiveText = GTK_WIDGET(gtk_builder_get_object(builder, "interactiveText"));
  fcfsButton = GTK_WIDGET(gtk_builder_get_object(builder, "fcfsButton"));
  priorityButton = GTK_WIDGET(gtk_builder_get_object(builder, "priorityButton"));
  srtnButton = GTK_WIDGET(gtk_builder_get_object(builder, "srtnButton"));
  gtk_widget_show_all(interactive_Window);
  gtk_widget_hide(window);
}

void rtos_clicked_cb(GtkButton *b)
{
  tipo = 2;
  GtkWidget *rtos_Window;
  GtkWidget *rtosContainer;
  GtkWidget *rtosText;
  GtkWidget *rmButton;
  GtkWidget *edfButton;
  rtos_Window = GTK_WIDGET(gtk_builder_get_object(builder, "rtos_Window"));
  g_signal_connect(rtos_Window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
  gtk_builder_connect_signals(builder, NULL);
  rtosContainer = GTK_WIDGET(gtk_builder_get_object(builder, "rtosContainer"));
  rtosText = GTK_WIDGET(gtk_builder_get_object(builder, "rtosText"));
  rmButton = GTK_WIDGET(gtk_builder_get_object(builder, "rmButton"));
  edfButton = GTK_WIDGET(gtk_builder_get_object(builder, "edfButton"));
  gtk_widget_show_all(rtos_Window);
  gtk_widget_hide(window);
}
void back(GtkButton *b, GtkWidget *win)
{
  gtk_widget_show_all(window);
  gtk_widget_hide(win);
}

void showGameWin(GtkWidget *win)
{

  windowLAB = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(windowLAB), "Laberinto");
  gtk_window_set_default_size(GTK_WINDOW(windowLAB), 100, 100);

  g_signal_connect(windowLAB, "destroy", G_CALLBACK(destroy), NULL);

  fixed = gtk_fixed_new();
  gtk_container_add(GTK_CONTAINER(windowLAB), fixed);

  char *type = "free.jpg";

  for (int i = 0; i < 10; i++)
  {
    for (int j = 0; j < 10; j++)
    {
      type = "free.jpg";
      if (laberinto[i][j] == 0)
        type = "wall.jpg";

      img = gtk_image_new_from_file(type);
      gtk_fixed_put(GTK_FIXED(fixed), img, 20 * j, 20 * i);
    }
  }

  for (int martians = 0; martians < no_procesos; martians++)
  {
    martian[martians] = gtk_image_new_from_file("martian.jpg");
    gtk_fixed_put(GTK_FIXED(fixed), martian[martians], 0, 0);

    /*label[martians] = gtk_label_new("Marciano ");
    gtk_fixed_put(GTK_FIXED(fixed), label[martians], 200, 20 * martians);*/
  }

  gdk_threads_add_idle(threadController, NULL);
  // gdk_threads_add_idle(updatePosition, martian);

  gtk_widget_show_all(windowLAB);

  // gtk_widget_show_all(windowLAB);
  gtk_widget_hide(win);
}

void showOpWin(GtkWidget *win)
{
  GtkWidget *windowOp;
  windowOp = GTK_WIDGET(gtk_builder_get_object(builder, "opWindow"));
  g_signal_connect(windowOp, "destroy", G_CALLBACK(gtk_main_quit), NULL);
  gtk_builder_connect_signals(builder, NULL);
  gtk_widget_show_all(windowOp);
  gtk_widget_hide(win);
}

void showrtosMartiansWindow()
{
  GtkWidget *windowRtosMartians;
  windowRtosMartians = GTK_WIDGET(gtk_builder_get_object(builder, "rtosMartiansWindows"));
  gtk_builder_connect_signals(builder, NULL);
  gtk_widget_show_all(windowRtosMartians);
}

void showinteractiveMartiansWindow()
{
  GtkWidget *windowInteractiveMartians;
  windowInteractiveMartians = GTK_WIDGET(gtk_builder_get_object(builder, "interactiveMartiansWindows"));
  gtk_builder_connect_signals(builder, NULL);
  gtk_widget_show_all(windowInteractiveMartians);
}

void on_edfButton_clicked(GtkButton *b, GtkWidget *win)
{
  algoritmo = 1;
  showOpWin(win);
}
void on_rmButton_clicked(GtkButton *b, GtkWidget *win)
{
  algoritmo = 2;
  showOpWin(win);
}
void on_fcfsButton_clicked(GtkButton *b, GtkWidget *win)
{
  algoritmo = 3;
  showOpWin(win);
}
void on_priorityButton_clicked(GtkButton *b, GtkWidget *win)
{
  algoritmo = 4;
  showOpWin(win);
}
void on_srtnButton_clicked(GtkButton *b, GtkWidget *win)
{
  algoritmo = 5;
  showOpWin(win);
}

void on_manualButton_clicked(GtkButton *b, GtkWidget *win)
{
  modo = 1;
  showGameWin(win);
}
void on_automaticButton_clicked(GtkButton *b, GtkWidget *win)
{
  modo = 0;
  if (tipo == 1)
  {
    // showGameWin(win);
    cantMarcianos = 0;
    showinteractiveMartiansWindow();
  }
  else
  {
    // showGameWin(win);
    showrtosMartiansWindow();
  }
}

void on_contButtonR_clicked(GtkButton *b, GtkWidget *win)
{
  for (int i = 0; i < cantMarcianos; i++)
  {

    g_print("%d ", marcianosRTOS[i].energy);

    printf("\n");
  }

  showGameWin(win);
  gtk_widget_hide(win);
}

void on_addrtosButton_clicked(GtkButton *b)
{
  GtkEntry *energyRtos;
  GtkEntry *periodRtos;
  energyRtos = GTK_ENTRY(gtk_builder_get_object(builder, "energyRtos"));
  periodRtos = GTK_ENTRY(gtk_builder_get_object(builder, "periodRtos"));
  gtk_builder_connect_signals(builder, NULL);

  struct Marciano marciano1 = {0, 0, 0, 0, 0, 0, 0};
  marciano1.energy = atoi(gtk_entry_get_text(energyRtos));
  marciano1.period = atoi(gtk_entry_get_text(periodRtos));
  marcianosRTOS[cantMarcianos] = marciano1;
  cantMarcianos = cantMarcianos + 1;
  gtk_editable_delete_text(GTK_EDITABLE(energyRtos), 0, -1);
  gtk_editable_delete_text(GTK_EDITABLE(periodRtos), 0, -1);
}

void on_contIntButton_clicked(GtkButton *b, GtkWidget *win)
{
  // g_print("Cantidad de marcianos: %d", cantMarcianos);

  no_procesos = cantMarcianos;

  if (algoritmo == 3)
  {
    for (int i = 0; i < no_procesos - 1; i++)
    {
      for (int j = 0; j < no_procesos - 1; j++)
      {
        if (p[j].arrival > p[j + 1].arrival)
        {
          temp = p[j];
          p[j] = p[j + 1];
          p[j + 1] = temp;
        }
      }
    }
  }

  showGameWin(win);

  gtk_widget_hide(win);
}

void on_addInteractiveButton_clicked(GtkButton *b)
{
  GtkEntry *priorityInteractive;
  GtkEntry *arrivalInteractive;
  GtkEntry *energyInteractiv;
  GtkEntry *periodInteractiv;
  priorityInteractive = GTK_ENTRY(gtk_builder_get_object(builder, "priorityInteractive"));
  periodInteractiv = GTK_ENTRY(gtk_builder_get_object(builder, "periodInteractiv"));
  energyInteractiv = GTK_ENTRY(gtk_builder_get_object(builder, "energyInteractiv"));
  arrivalInteractive = GTK_ENTRY(gtk_builder_get_object(builder, "arrivalInteractive"));
  gtk_builder_connect_signals(builder, NULL);
  struct Marciano marciano1 = {0, 0, 0, 0, 0, 0, 0};
  marciano1.priority = atoi(gtk_entry_get_text(priorityInteractive));
  marciano1.energy = atoi(gtk_entry_get_text(energyInteractiv));
  marciano1.period = atoi(gtk_entry_get_text(periodInteractiv));
  marciano1.arrivalTime = atoi(gtk_entry_get_text(arrivalInteractive));
  marcianosInteractivos[cantMarcianos] = marciano1;

  p[cantMarcianos].arrival = marciano1.arrivalTime;
  p[cantMarcianos].burst = marciano1.energy;

  cantMarcianos = cantMarcianos + 1;

  gtk_editable_delete_text(GTK_EDITABLE(priorityInteractive), 0, -1);
  gtk_editable_delete_text(GTK_EDITABLE(energyInteractiv), 0, -1);
  gtk_editable_delete_text(GTK_EDITABLE(periodInteractiv), 0, -1);
  gtk_editable_delete_text(GTK_EDITABLE(arrivalInteractive), 0, -1);
}

gboolean threadController(gpointer data)
{
  if (started == 0)
  {
    started = 1;
    for (int i = 0; i < no_procesos; ++i)
    {

      // create new martian
      /*struct Marciano marciano = {0, 0, 0, 0, i};
      marcianosFinal[i] = marciano;

      // create martian thread
      pthread_t threads[i];

      int v = i; // free display

      pthread_create(&threads[i], NULL, call_solve, &v);

      start_martian_no++;*/

      // create new martian
      struct Marciano marciano = {0, 0, 0, 0, i + 2};
      marcianosFinal[i] = marciano;

      // create martian thread
      // pthread_t threads[i];

      // pthread_create(&threads[i], NULL, call_solve, NULL);
      int burst_time;
      if (algoritmo == 1)
      {
        burst_time = p[i].burst;
      }
      /*else if (algoritmo == 2)
      {
        burst_time = bt[i];
      }
      else
      {
        burst_time = p2[i];
      }*/
      martian_Started++;
      g_print("Hola desde solve\n");
      solve_matrix(marcianosFinal[start_martian_no], fixed, martian[martian_Started], burst_time);

      // so start_martian_no has time to update
      usleep(9000000);

      start_martian_no++;
    }

    for (int i = 0; i < no_procesos; ++i)
    {
      pthread_join(threads[i], NULL);
    }
  }
  else
  {
    return 0;
  }
}

void destroy(GtkWidget *widget, gpointer data)
{
  gtk_main_quit();
}