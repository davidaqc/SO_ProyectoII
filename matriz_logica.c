#include <gtk/gtk.h>

#include <stdio.h>
#include<stdlib.h> // in C, for rand() 
#include <unistd.h>
#include<time.h>    //for time()
#include "matriz_logica.h"


int moves = 0;

// Matrix size
#define M 10
//matrix that represents the board
int matrix[M][M] = { { 1, 1, 0, 0 ,0 ,0 ,0 ,0 ,0 ,0},
                    { 0, 1, 0, 0 ,0 ,0 ,1 ,1 ,0 ,0},
                    { 0, 1, 1, 1 ,1 ,1 ,1 ,0 ,0 ,0},
                    { 0, 0, 1, 0 ,0 ,0 ,0 ,0 ,0 ,0},
                    { 1, 1, 1, 1 ,0 ,0 ,0 ,0 ,0 ,0},
                    { 1, 0, 0, 1 ,0 ,0 ,1 ,1 ,1 ,0},
                    { 1, 0, 1, 1 ,1 ,1 ,1 ,0 ,1 ,0},
                    { 0, 0, 0, 1 ,0 ,0 ,1 ,0 ,1 ,0},
                    { 0, 0, 0, 1 ,0 ,0 ,1 ,0 ,1 ,0},
                    { 0, 0, 0, 0 ,0 ,1 ,1 ,0 ,1 ,1}};



//x positive is to the right
//y positive is down

//1 is the way
//0 is blocked


//Function to print the matrix
void printCurrentMatrix(int sol[M][M])
{
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < M; j++)
            printf(" %d ", sol[i][j]);
        printf("\n");
    }
}

//void solve_matrix(struct Marciano marciano, GtkWidget *fixed, GtkWidget *martian, GtkWidget *label)

//helps 1 martian to get out of the labyrinth
void solve_matrix(struct Marciano1 marciano, GtkWidget *fixed, GtkWidget *martian, int burst){

    g_print("Hola David\n");
    //loads martian in first position if available    

    /*if(matrix[0][0]==1){
        matrix[0][0]=marciano.id;
    }
    else{
        printf("Space not available");
        return;
    }*/




    //waits until first spacec is available
    /*
    while(1==1){
        if(matrix[0][0]==1){
            matrix[0][0]=marciano.id;
            break;
        } 
    }*/

    //TEEEEESST GUI -DELETE
    marciano.id = 2;

    while(matrix[0][0]!=1){
        ;//NOP, this just waits for the position to be freed
    }

    matrix[0][0]= marciano.id;


    //move martian
    while(!(marciano.posX==(M-1) && marciano.posY==(M-1))){
        //gives random number between 0-99
        //to generate random numbers. Generate "decent" random numbers in c seems awfully complicated
        srand(clock()); 
    	int random_number=rand(); 
	    int random_in_range=random_number%100;

        /*
        printf("numero aleaotrio");
        printf("%d",random_in_range);
        printf("\n");*/

        /*printf("ID: %d\n", marciano.id);
        printf("X: %d\n", marciano.posX);
        printf("Y: %d\n", marciano.posY);
        printCurrentMatrix(matrix);
        printf("************************\n");*/

        //moves →
        if(marciano.posX<M && random_in_range<=25 && matrix[marciano.posY][marciano.posX+1]==1){
            matrix[marciano.posY][marciano.posX]=1;
            matrix[marciano.posY][marciano.posX+1]=marciano.id;
            marciano.posX++;
            moves++;
           // printf("1\n");
        }

        //moves ← 
        else if(marciano.posX>0 && random_in_range>25 && random_in_range<=50 && matrix[marciano.posY][marciano.posX-1]==1){
            matrix[marciano.posY][marciano.posX]=1;
            matrix[marciano.posY][marciano.posX-1]=marciano.id;
            marciano.posX--;
            moves++;
           // printf("2\n");
        }

        //moves ↑
        else if(marciano.posY>0 && random_in_range>50 && random_in_range<=75 && matrix[marciano.posY-1][marciano.posX]==1){
            matrix[marciano.posY][marciano.posX]=1;
            matrix[marciano.posY-1][marciano.posX]=marciano.id;
            marciano.posY--;
            moves++;
           //printf("3\n");
        }

        //moves ↓
        else if(marciano.posY<M && random_in_range>65 && random_in_range<=99 && matrix[marciano.posY+1][marciano.posX]==1){
            matrix[marciano.posY][marciano.posX]=1;
            matrix[marciano.posY+1][marciano.posX]=marciano.id;
            marciano.posY++;
            moves++;
            //printf("4\n");
        }
        //NOP
        else{
            //printf("5\n");
            ;
        }

    /*gchar *display;
    display = g_strdup_printf("Martian %d: %d moves", numberMartian, moves);         //convert num to str
    gtk_label_set_text (GTK_LABEL(label), display); //set label to "display"
    g_free(display);   */                       //free display



    gtk_fixed_move(GTK_FIXED(fixed), martian, marciano.posX*20, marciano.posY*20);
    

    usleep(100000);
    //usleep(200000/2);


    }
    g_print("El marciano termino\n");
    gtk_fixed_move(GTK_FIXED(fixed), martian, marciano.posX*20, marciano.posY*20);

    matrix[M-1][M-1]=0;


}
