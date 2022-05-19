// gcc `pkg-config --cflags gtk+-3.0` -c  matriz_logica.c `pkg-config --libs gtk+-3.0`
// gcc `pkg-config --cflags gtk+-3.0` -o example-0 matriz_logica.o  main.c -lpthread `pkg-config --libs gtk+-3.0`

#include <gtk/gtk.h>
#include <time.h> //for time()
#include <stdio.h>

#include <stdlib.h>
#include <unistd.h>
#include "matriz_logica.h"
#include <pthread.h>

#define WINDOW_SIZE 50

// Matrix size
#define N 10

// Max number of processes
#define Martians 10

void destroy(GtkWidget *, gpointer);
gboolean threadController(gpointer);
gboolean updatePosition(gpointer);

struct Marciano
{
    int posX;
    int posY;
    int energy;
    int period;
    int id;
};

struct Marciano marcianos[Martians];
pthread_t threads[Martians];
int start_martian_no = 0;

GtkWidget *window;
GtkWidget *fixed;
GtkWidget *img;
GtkWidget *label[10];
GtkWidget *martian[10];

int started = 0;

int no_procesos;

int id = 0;

int x = 60;

int martian_Started = -1;

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
void *call_solve(void * arg)
{
    martian_Started++;
    solve_matrix(marcianos[start_martian_no], fixed, martian[martian_Started]);
    
    //solve_matrix(marcianos[start_martian_no], fixed, martian[*iptr], label[*iptr]);
    return NULL;
}

int main(int argc, char **argv)
{

    printf("Modo automatico, ingrese la cantidad de procesos por crear \n");
    scanf("%d", &no_procesos);

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Window");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 200);

    g_signal_connect(window, "destroy", G_CALLBACK(destroy), NULL);

    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), fixed);

    char *type = "free.jpg";

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            type = "free.jpg";
            if (laberinto[i][j] == 0)
                type = "wall.jpg";

            img = gtk_image_new_from_file(type);
            gtk_fixed_put(GTK_FIXED(fixed), img, 20 * j, 20 * i);
        }
    }  


    for(int martians = 0; martians < no_procesos; martians++){
        martian[martians] = gtk_image_new_from_file("martian.jpg");
        gtk_fixed_put(GTK_FIXED(fixed), martian[martians], 0, 0);

        /*label[martians] = gtk_label_new("Marciano ");
        gtk_fixed_put(GTK_FIXED(fixed), label[martians], 200, 20 * martians);*/
    } 
        

    gdk_threads_add_idle(threadController, NULL);
    // gdk_threads_add_idle(updatePosition, martian);

    gtk_widget_show_all(window);

    gtk_main();
}

void destroy(GtkWidget *widget, gpointer data)
{
    gtk_main_quit();
}


gboolean threadController(gpointer data)
{
    if (started == 0)
    {
        started = 1;
        for (int i = 0; i < no_procesos; ++i)
        {

            // create new martian
            struct Marciano marciano = {0, 0, 0, 0, i};
            marcianos[i] = marciano;

            //printf("ID MARTIAN %d\n", marcianos[0].id);

            // create martian thread
            pthread_t threads[i];

            int v = i;

            //martian[i] = gtk_image_new_from_file("martian.jpg");
            //gtk_fixed_put(GTK_FIXED(fixed), martian[i], 0, 0);

            //printf("Marciano creado\n");

            //label[i] = gtk_label_new("Marciano ");
            //gtk_fixed_put(GTK_FIXED(fixed), label[i], 300, 0);

            /*gchar *display;
            display = g_strdup_printf("Marciano numero: %d, movimientos: 0", i + 1);         //convert num to str
            gtk_label_set_text (GTK_LABEL(label), display); //set label to "display"
            g_free(display);                              //free display*/

            pthread_create(&threads[i], NULL, call_solve,&v);
            

            // so start_martian_no has time to update
            //usleep(9000000);

            start_martian_no++;
            
        }

        for (int i = 0; i < no_procesos; ++i)
        {
            pthread_join(threads[i], NULL);
        }
    }else{
        return 0;
    }
}