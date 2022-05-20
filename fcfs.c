// gcc -o fcfs fcfs.c
// https://www.youtube.com/watch?v=EvyBpOQYgYE
/*gcc `pkg-config --cflags gtk+-3.0` -o fc  fcfs.c `pkg-config --libs gtk+-3.0` -export-dynamic*/

#include <stdio.h>
#include <gtk/gtk.h>
struct PCB
{
    int pid, arrival, burst, turnaround;
};

int i, num, j;
    float avg = 0.0, sum = 0.0;
    struct PCB p[10], temp;

void pline(int x);
static void activate (GtkApplication *app, gpointer user_data);
int main (int argc, char ** argv){

    
    printf("Enter the total number of processes: ");
    scanf("%d", &num);
    for(i=0; i<num; i++){
        printf("Enter Arrival time and Burst time for Process %d: \n", i+1);
        scanf("%d %d", &p[i].arrival, &p[i].burst);
        p[i].pid = i + 1;
    }
    for(i=0; i<num-1; i++){
        for(j=0; j<num-1; j++){
            if(p[j].arrival > p[j+1].arrival){
                temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }
    for(i=0; i<num; i++){
        sum = sum + p[i].burst;
        p[i].turnaround = sum;
    }
    sum = 0;
    pline(44);
    printf("PID\tArrival\tBurst\tTurnaround");
    pline(44);
    for(i=0; i<num; i++){
        printf("%d\t%d\t%d\t%d\n", p[i].pid, p[i].arrival, p[i].burst, p[i].turnaround);
        sum += p[i].turnaround; 
    }
    pline(44);
    avg = sum/(float)num;
    printf("\nTotal Turnaround Time : %f.", sum);
    printf("\nAverage Turnaround Time : %.3f.", avg);
    GtkApplication *app;
 int ret;
 app = gtk_application_new ("in.aducators", G_APPLICATION_FLAGS_NONE);
 g_signal_connect (app, "activate", G_CALLBACK(activate), NULL);
 ret = g_application_run (G_APPLICATION(app), argc, argv);
 g_object_unref (app);
 return ret;

}

void pline(int x)
{
    int i;
    for(i=0; i<x; i++){
        printf("-");
    }
    printf("\n");
}
static void activate (GtkApplication *app, gpointer user_data) {
GtkWidget *window;
GtkWidget *fixed;
GtkWidget *img;
GtkWidget *label;
window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
gtk_window_set_title(GTK_WINDOW(window), "Window");
gtk_window_set_default_size(GTK_WINDOW(window), 700, 400);
fixed = gtk_fixed_new();
gtk_container_add(GTK_CONTAINER(window), fixed);
g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
char str[12];


sprintf(str, "%d", p[0].pid);
        label = gtk_label_new(str);
        gtk_fixed_put(GTK_FIXED(fixed), label, 650 ,  20 );
for(j=p[0].arrival; j<p[0].turnaround; j++){
        img = gtk_image_new_from_file("wall.jpg");
        gtk_fixed_put(GTK_FIXED(fixed), img, 18*j , 20 );
        
        
    }
 for(i=1; i<num; i++){
        for(j=p[i-1].turnaround; j<p[i].turnaround; j++){
        img = gtk_image_new_from_file("wall.jpg");
        gtk_fixed_put(GTK_FIXED(fixed), img, 18*j , 20*(i+1) );
    }
    
     sprintf(str, "%d", p[i].pid);
        label = gtk_label_new(str);
        gtk_fixed_put(GTK_FIXED(fixed), label, 650 , (i*20) + 20 );
    }
    
     for(i=0; i<36; i++){
     sprintf(str, "%d", i);
        label = gtk_label_new(str);
        gtk_fixed_put(GTK_FIXED(fixed), label,i*18 , 350 );

    }
    
 
        gtk_widget_show_all(window);
  gtk_main();
}
