
//http://www.cse.cuhk.edu.hk/~ericlo/teaching/os/lab/9-PThread/Pass.html
//https://www.geeksforgeeks.org/multithreading-c-2/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "matriz_logica.h"
#include <pthread.h>
//gcc -o principal matriz_logica.o main.o

// Matrix size
#define N 10


struct Marciano {
  int posX;
  int posY;
  int energy;
  int period;
  int id;
};

struct Marciano marcianos[N];
pthread_t threads[N];
int ff=0;


void *call_solve(void *vargp){
    printf("sadsdsadsadsa");
    printf("%d",ff);
    printf("\n");
    solve_matrix(marcianos[ff]);
    return NULL;
}


int main() {
    //user input with number of processes
    int no_procesos;
    printf("Modo automatico, ingrese la cantidad de procesos por crear \n");  
    scanf("%d", &no_procesos);

    int i=0;

    struct Marciano marciano1 = {0,0,0,0,2};

    marcianos[i] = marciano1;

    pthread_t p1;

    pthread_create(&p1, NULL, call_solve, NULL);

    usleep(9000000);

    i++;
    
    struct Marciano marciano2 = {0,0,0,0,3};

    marcianos[i] = marciano2;
    ff++;

    pthread_t p2;

    pthread_create(&p2, NULL, call_solve, NULL);


    /*
    int i=0;
    for(int i = 0; i < no_procesos; ++i) {
        //create martian thread
        pthread_t i;
        
        struct Marciano marciano = {0,0,0,0,i+2};

        marcianos[i] = marciano;

        printf("gokuuuuuuuaaaa");

        pthread_create(&i, NULL, call_solve, NULL);
        

        //solve_matrix(marcianos[i]);
        //printf("%d\n", values[i]);
    }
    pthread_join(0, NULL);
    pthread_join(1, NULL);*/

    pthread_join(p1, NULL);

    pthread_join(p2, NULL);

    
    return 0;
}