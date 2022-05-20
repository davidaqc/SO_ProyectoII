// gcc -o priority priority.c
// https://www.thecrazyprogrammer.com/2014/11/c-cpp-program-for-priority-scheduling-algorithm.html
/*gcc `pkg-config --cflags gtk+-3.0` -o priority  priority.c `pkg-config --libs gtk+-3.0` -export-dynamic*/
#include <gtk/gtk.h>
#include<stdio.h>
static void activate (GtkApplication *app, gpointer user_data);
int bt[20],p[20],wt[20],tat[20],pr[20],i,j,n,total=0,pos,temp,avg_wt,avg_tat;
int main (int argc, char ** argv)
{
   
    printf("Enter Total Number of Process:");
    scanf("%d",&n);
 
    printf("\nEnter Burst Time and Priority\n");
    for(i=0;i<n;i++)
    {
        printf("\nP[%d]\n",i+1);
        printf("Burst Time:");
        scanf("%d",&bt[i]);
        printf("Priority:");
        scanf("%d",&pr[i]);
        p[i]=i+1;           //contains process number
    }
 
    //sorting burst time, priority and process number in ascending order using selection sort
    for(i=0;i<n;i++)
    {
        pos=i;
        for(j=i+1;j<n;j++)
        {
            if(pr[j]<pr[pos])
                pos=j;
        }
 
        temp=pr[i];
        pr[i]=pr[pos];
        pr[pos]=temp;
 
        temp=bt[i];
        bt[i]=bt[pos];
        bt[pos]=temp;
 
        temp=p[i];
        p[i]=p[pos];
        p[pos]=temp;
    }
 
    wt[0]=0; //waiting time for first process is zero
 
    //calculate waiting time
    for(i=1;i<n;i++)
    {
        wt[i]=0;
        for(j=0;j<i;j++)
            wt[i]+=bt[j];
 
        total+=wt[i];
    }
 
    avg_wt=total/n;      //average waiting time
    total=0;
 
    printf("\nProcess\t    Burst Time    \tWaiting Time\tTurnaround Time");
    for(i=0;i<n;i++)
    {
        tat[i]=bt[i]+wt[i];     //calculate turnaround time
        total+=tat[i];
        printf("\nP[%d]\t\t  %d\t\t    %d\t\t\t%d",p[i],bt[i],wt[i],tat[i]);
    }
 
    avg_tat=total/n;     //average turnaround time
    printf("\n\nAverage Waiting Time=%d",avg_wt);
    printf("\nAverage Turnaround Time=%d\n",avg_tat);
 
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
for(j=0; j<tat[0]; j++){
        img = gtk_image_new_from_file("wall.jpg");
        gtk_fixed_put(GTK_FIXED(fixed), img, 18*j , 20 );
        
        
    }
 for(i=1; i<n; i++){
        for(j=tat[i-1]; j<tat[i]; j++){
        img = gtk_image_new_from_file("wall.jpg");
        gtk_fixed_put(GTK_FIXED(fixed), img, 18*j , 20*(i+1) );
    }
    
     sprintf(str, "%d", p[i]);
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
