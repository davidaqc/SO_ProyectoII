
//http://www.cse.cuhk.edu.hk/~ericlo/teaching/os/lab/9-PThread/Pass.html
//https://www.geeksforgeeks.org/multithreading-c-2/
//https://stackoverflow.com/questions/35403892/creating-threads-in-a-loop
//https://stackoverflow.com/questions/13339462/thread-stops-randomly-in-the-middle-of-a-while-loop

/*
gcc -c matriz_logica.c
gcc -c main.c -lpthread
gcc -o principal matriz_logica.o main.o -lpthread
./principal
*/



#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "matriz_logica.h"
#include <pthread.h>


// Matrix size
#define N 10

//Max number of processes
#define Martians 10


struct Marciano {
  int posX;
  int posY;
  int energy;
  int period;
  int id;
};


/*fixed size to avoid error:
main.c:59:28: error: expected ‘)’ before ‘+’ token
         pthread_t *(threads+i);
when creating threads
*/

struct Marciano marcianos[Martians];
pthread_t threads[Martians];
int start_martian_no=0;


//function that calls the solver file
void *call_solve(){
    solve_matrix(marcianos[start_martian_no]);
    return NULL;
}

struct PCB
{
    int pid, arrival, burst, turnaround;
};


int main() {
    //user input with number of processes
    int no_procesos;
    printf("Modo automatico, ingrese la cantidad de procesos por crear \n");  
    scanf("%d", &no_procesos);
    

    for(int i = 0; i < no_procesos; ++i) {
        
        
        //create new martian 
        struct Marciano marciano = {0,0,0,0,i+2};
        marcianos[i] = marciano;


        //create martian thread
        pthread_t threads[i];

        pthread_create(&threads[i], NULL, call_solve, NULL);

        //so start_martian_no has time to update 
        usleep(9000000);

        start_martian_no++;
        
    }

    for(int i = 0; i < no_procesos; ++i) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}