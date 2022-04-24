//https://beginnersbook.com/2014/01/2d-arrays-in-c-example/
//https://stackoverflow.com/questions/7343833/srand-why-call-it-only-once

#include <stdio.h>
#include<stdlib.h> // in C, for rand() 
#include <unistd.h>
#include<time.h>    //for time()

struct Marciano {
  int posX;
  int posY;
  int energy;
  int period;
  int id;
};

// Matrix size
#define N 4

//x positive is to the right
//y positive is down

//1 is the way
//0 is blocked

//Function to print the matrix
void printCurrentMatrix(int sol[N][N])
{
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            printf(" %d ", sol[i][j]);
        printf("\n");
    }
}

//helps 1 martian to get out of the labyrinth
void solve_matrix(int matrix[N][N], struct Marciano marciano){
    //loads martian in first position if available

    if(matrix[0][0]==1){
        matrix[0][0]=marciano.id;
    }


    //move martian
    while(!(marciano.posX==(N-1) && marciano.posY==(N-1))){
        //gives random number between 0-99
        //to generate random numbers. Generate "decent" random numbers in c seems awfully complicated
        srand(clock()); 
    	int random_number=rand(); 
	    int random_in_range=random_number%100;

        /*
        printf("numero aleaotrio");
        printf("%d",random_in_range);
        printf("\n");*/

        printCurrentMatrix(matrix);
        printf("************************\n");

        //moves →
        if(marciano.posX<N && random_in_range<=25 && matrix[marciano.posY][marciano.posX+1]==1){
            matrix[marciano.posY][marciano.posX]=1;
            matrix[marciano.posY][marciano.posX+1]=marciano.id;
            marciano.posX++;
           // printf("1\n");
        }

        //moves ← 
        else if(marciano.posX>0 && random_in_range>25 && random_in_range<=50 && matrix[marciano.posY][marciano.posX-1]==1){
            matrix[marciano.posY][marciano.posX]=1;
            matrix[marciano.posY][marciano.posX-1]=marciano.id;
            marciano.posX--;
           // printf("2\n");
        }

        //moves ↑
        else if(marciano.posY>0 && random_in_range>50 && random_in_range<=75 && matrix[marciano.posY-1][marciano.posX]==1){
            matrix[marciano.posY][marciano.posX]=1;
            matrix[marciano.posY-1][marciano.posX]=marciano.id;
            marciano.posY--;
           //printf("3\n");
        }

        //moves ↓
        else if(marciano.posY<N && random_in_range>75 && random_in_range<=99 && matrix[marciano.posY+1][marciano.posX]==1){
            matrix[marciano.posY][marciano.posX]=1;
            matrix[marciano.posY+1][marciano.posX]=marciano.id;
            marciano.posY++;
            //printf("4\n");
        }
        //NOP
        else{
            //printf("5\n");
            ;
        }

    //usleep(1000000);
    usleep(900000);


    }
}


int main() {
    int matrix[N][N] = { { 1, 0, 0, 0 },
                       { 1, 1, 0, 1 },
                       { 0, 1, 0, 0 },
                       { 1, 1, 1, 1 } };

    struct Marciano marciano1 ; //= {10,0,0,50,2};
    
    marciano1.energy= 10;
    marciano1.posX=0;
    marciano1.posY=0;
    marciano1.period=50;
    marciano1.id=2;

    solve_matrix(matrix,marciano1);

    printCurrentMatrix(matrix);

    return 0;
}

