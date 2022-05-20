// gcc -o srtf srtf.c
// https://www.quora.com/How-do-I-write-a-C-program-to-implement-a-SRTF-Shortest-Remaining-Time-First-scheduling-algorithm-along-with-displaying-the-Gantt-chart
/*gcc `pkg-config --cflags gtk+-3.0` -o srtf  srtf.c `pkg-config --libs gtk+-3.0` -export-dynamic*/
#include <gtk/gtk.h>
#include <stdio.h>
static void activate (GtkApplication *app, gpointer user_data);
int pointer, pre, a[15], b[15], r[15], count = 0, n, small, i, j, m, s = 0, k = 0, p[10], t[15] = {0}, w[15] = {0}, x, y, bs, temp, d = 0;

float att = 0, awt = 0;

int main (int argc, char ** argv)

{

    printf("enter the number of process\n");

    scanf("%d", &n);

    for (i = 0; i < n; i++)

    {

        printf("enter the process %d arrival time and burst time\n", i + 1);

        p[i] = i + 1;

        scanf("%d%d", &a[i], &b[i]);

        count += b[i];

        r[i] = b[i];
    }

    for (x = 0; x < n; x++)

        for (y = 0; y < n - 1; y++)

            if (a[y] > a[y + 1])

            {

                temp = a[y + 1];

                a[y + 1] = a[y];

                a[y] = temp;

                temp = b[y + 1];

                b[y + 1] = b[y];

                b[y] = temp;

                temp = p[y + 1];

                p[y + 1] = p[y];

                p[y] = temp;
            }

    while (pointer <= count)

    {

        i = j = m = 0;

        pre = pointer;

        k = d + 1;

        small = 9999;

        for (i = n - 1; i >= 0; i--)

        {

            if (pointer < a[n - 1])

            {

                if (r[i] <= small && r[i] > 0 && a[i] <= pointer)

                {

                    small = r[i];

                    j = i;
                }
            }

            else if (pointer >= a[n - 1])

            {

                if (r[i] <= small && r[i] > 0)

                {

                    small = r[i];

                    j = i;
                }
            }
        }

        d = k;

        while (a[s + d] == pointer)

            d++;

        if (pointer == 0)

            pointer = (a[d] > small) ? small : a[d];

        else

            pointer = (s + d == n - 1) ? (small <= a[n - 2] - pointer) ? pointer + small : a[n - 2] : (pointer >= a[n - 1]) ? pointer + small
                                                                                                  : (s + d < n - 1)         ? ((small <= a[s + d] - pointer) ? pointer + small : a[s + d])
                                                                                                                            : ((small <= a[n - 1] - pointer) ? pointer + small : a[n - 1]);

        if (pointer - pre > 0)

            r[j] = r[j] - pointer + pre;

        if (pointer - pre > 0 && r[j] >= 0)

            printf(" process %d : executed %d/%d remaining %d\n", p[j], pointer - pre, b[j], r[j]);

        if (r[j] == 0)

            t[j] = pointer - a[j];
    }

    printf("\n ******OVERALL REVIEW OF SCHEDULING*****\n");

    for (i = 0; i < n; i++)

    {

        att += t[i];

        w[i] = t[i] - b[i];

        awt += w[i];

        printf("process %d: waiting time:%d turnaround time:%d\n", p[i], w[i], t[i]);
    }

    printf("\n avarage waiting time :%f\n avarage turnaround time:%f \n \n", awt / n, att / n);
 GtkApplication *app;
    int ret;
 app = gtk_application_new ("in.aducators", G_APPLICATION_FLAGS_NONE);
 g_signal_connect (app, "activate", G_CALLBACK(activate), NULL);
 ret = g_application_run (G_APPLICATION(app), argc, argv);
 g_object_unref (app);
 return ret;
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


sprintf(str, "%d", p[0]);
        label = gtk_label_new(str);
        gtk_fixed_put(GTK_FIXED(fixed), label, 650 ,  20 );
     for(i=0; i<36; i++){
     sprintf(str, "%d", i);
        label = gtk_label_new(str);
        gtk_fixed_put(GTK_FIXED(fixed), label,i*18 , 350 );

    }
    
 
        gtk_widget_show_all(window);
  gtk_main();
}
