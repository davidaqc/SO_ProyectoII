
// http://www.cse.cuhk.edu.hk/~ericlo/teaching/os/lab/9-PThread/Pass.html
// https://www.geeksforgeeks.org/multithreading-c-2/
// https://stackoverflow.com/questions/35403892/creating-threads-in-a-loop
// https://stackoverflow.com/questions/13339462/thread-stops-randomly-in-the-middle-of-a-while-loop

/*
gcc -c matriz_logica.c
gcc -c main.c -lpthread
gcc -o principal matriz_logica.o main.o -lpthread
./principal
*/

// sudo apt-get install libgtk-3-dev

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "matriz_logica.h"
#include <pthread.h>

// Matrix size
#define N 10

// Max number of processes
#define Martians 10

struct Marciano
{
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
int start_martian_no = 0;

// function that calls the solver file
void *call_solve()
{
    // solve_matrix(marcianos[start_martian_no]);
    return NULL;
}

struct PCB
{
    int pid, arrival, burst, turnaround;
};

int main()
{

    // Variables
    int modo, algoritmo;
    int i, no_procesos, j;
    struct PCB p[10], temp;
    int bt[20], p1[20], pr[20], pos = 0, temp1;
    int pointer, pre, a[15], b[15], r[15], count = 0, small, m, s = 0, k = 0, p2[10], t[15] = {0}, w[15] = {0}, x, y, bs, temp2, d = 0;
    int p3[10];
    int aa;

    // Menú
    printf("\n   1. Modo manual: ");
    printf("\n   2. Modo automatico: ");
    printf("\n\n   Introduzca opcion (1-2): ");
    scanf("%d", &modo);

    switch (modo)
    {
    case 1:
        break;

    case 2:
        printf("\n   1. FCFS: ");
        printf("\n   2. Prioridad: ");
        printf("\n   3. SRTF: ");
        printf("\n\n   Introduzca opcion (1-3): ");
        scanf("%d", &algoritmo);

        switch (algoritmo)
        {
        case 1:
            printf("\n  Algoritmo a utilizar FCFS! \n\n");
            printf("Ingrese el numero de procesos: ");
            scanf("%d", &no_procesos);
            for (i = 0; i < no_procesos; i++)
            {
                printf("Ingrese el tiempo de llegada y el tiempo de ejecucion para el proceso %d: \n", i + 1);
                scanf("%d %d", &p[i].arrival, &p[i].burst);
                p[i].pid = i + 1;
            }
            for (i = 0; i < no_procesos - 1; i++)
            {
                for (j = 0; j < no_procesos - 1; j++)
                {
                    if (p[j].arrival > p[j + 1].arrival)
                    {
                        temp = p[j];
                        p[j] = p[j + 1];
                        p[j + 1] = temp;
                    }
                }
            }
            break;
        case 2:
            printf("\n Algoritmo a utilizar Prioridad! \n\n");
            printf("Ingrese el numero de procesos: ");
            scanf("%d", &no_procesos);

            printf("Ingrese el tiempo de ejecucion y la prioridad \n");
            for (i = 0; i < no_procesos; i++)
            {
                printf("\nP[%d]\n", i + 1);
                printf("Tiempo de ejecucion:");
                scanf("%d", &bt[i]);
                printf("Prioridad:");
                scanf("%d", &pr[i]);
                p1[i] = i + 1; // contains process number
            }

            // sorting burst time, priority and process number in ascending order using selection sort
            for (i = 0; i < no_procesos; i++)
            {
                pos = i;
                for (j = i + 1; j < no_procesos; j++)
                {
                    if (pr[j] < pr[pos])
                        pos = j;
                }

                temp1 = pr[i];
                pr[i] = pr[pos];
                pr[pos] = temp1;

                temp1 = bt[i];
                bt[i] = bt[pos];
                bt[pos] = temp1;

                temp1 = p1[i];
                p1[i] = p1[pos];
                p1[pos] = temp1;
            }
            break;
        case 3:
            printf("\n  Algoritmo a utilizar SRTF! \n\n");
            printf("Ingrese el numero de procesos: ");
            scanf("%d", &no_procesos);

            for (i = 0; i < no_procesos; i++)
            {

                printf("Ingrese el tiempo de llegada y el tiempo de ejecucion para el proceso %d:", i + 1);
                p2[i] = i + 1;
                scanf("%d%d", &a[i], &b[i]);
                count += b[i];
                r[i] = b[i];
            }

            for (x = 0; x < no_procesos; x++)
                for (y = 0; y < no_procesos - 1; y++)
                    if (a[y] > a[y + 1])
                    {

                        temp2 = a[y + 1];
                        a[y + 1] = a[y];
                        a[y] = temp2;
                        temp2 = b[y + 1];
                        b[y + 1] = b[y];
                        b[y] = temp2;
                        temp2 = p2[y + 1];
                        p2[y + 1] = p2[y];
                        p2[y] = temp2;
                    }

            while (pointer <= count)
            {
                i = j = m = 0;
                pre = pointer;
                k = d + 1;
                small = 9999;

                for (i = no_procesos - 1; i >= 0; i--)
                {
                    if (pointer < a[no_procesos - 1])
                    {
                        if (r[i] <= small && r[i] > 0 && a[i] <= pointer)
                        {
                            small = r[i];
                            j = i;
                        }
                    }
                    else if (pointer >= a[no_procesos - 1])
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
                    pointer = (s + d == no_procesos - 1) ? (small <= a[no_procesos - 2] - pointer) ? pointer + small : a[no_procesos - 2] : (pointer >= a[no_procesos - 1]) ? pointer + small
                                                                                                          : (s + d < no_procesos - 1)         ? ((small <= a[s + d] - pointer) ? pointer + small : a[s + d])
                                                                                                                                    : ((small <= a[no_procesos - 1] - pointer) ? pointer + small : a[no_procesos - 1]);
                if (pointer - pre > 0)
                    r[j] = r[j] - pointer + pre;

                if (pointer - pre > 0 && r[j] >= 0){
                    printf(" process %d : executed %d/%d remaining %d\n", p2[j], pointer - pre, b[j], r[j]);
                    p3[aa] = p2[j];
                    aa++;
                }

                if (r[j] == 0)
                    t[j] = pointer - a[j];
            }
        }
    }

    /*for(int i = 0; i <= aa; i++){
        printf(" process %d);
    }*/

    // Laberinto
    for (int i = 0; i < no_procesos; ++i)
    {

        // create new martian
        struct Marciano marciano = {0, 0, 0, 0, i + 2};
        marcianos[i] = marciano;

        // create martian thread
        // pthread_t threads[i];

        // pthread_create(&threads[i], NULL, call_solve, NULL);
        int burst_time;
        if (algoritmo == 1)
        {
            burst_time = p[i].burst;
        }
        else if (algoritmo == 2)
        {
            burst_time = bt[i];
        }
        else
        {
            burst_time = p2[i];
        }
        solve_matrix(marcianos[start_martian_no], burst_time);

        // so start_martian_no has time to update
        usleep(9000000);

        start_martian_no++;
    }

    return 0;
}

// matrix that represents the board
int matrix[N][N] = {{1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 1, 0, 0, 0, 0, 1, 1, 0, 0},
                    {0, 1, 1, 1, 1, 1, 1, 0, 0, 0},
                    {0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
                    {1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
                    {1, 0, 0, 1, 0, 0, 1, 1, 1, 0},
                    {1, 0, 1, 1, 1, 1, 1, 0, 1, 0},
                    {0, 0, 0, 1, 0, 0, 1, 0, 1, 0},
                    {0, 0, 0, 1, 0, 0, 1, 0, 1, 0},
                    {0, 0, 0, 0, 0, 1, 1, 0, 1, 1}};

// x positive is to the right
// y positive is down

// 1 is the way
// 0 is blocked

// Function to print the matrix
void printCurrentMatrix(int sol[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            printf(" %d ", sol[i][j]);
        printf("\n");
    }
}

// helps 1 martian to get out of the labyrinth
void solve_matrix(struct Marciano marciano, int burst)
{
    // loads martian in first position if available

    printf("Tiempo de ejecucion: %d \n", burst);
    int times = 0;

    /*if(matrix[0][0]==1){
        matrix[0][0]=marciano.id;
    }
    else{
        printf("Space not available");
        return;
    }*/

    // waits until first space is available
    /*
    while(1==1){
        if(matrix[0][0]==1){
            matrix[0][0]=marciano.id;
            break;
        }
    }*/
    while (matrix[0][0] != 1)
    {
        ; // NOP, this just waits for the position to be freed
    }

    matrix[0][0] = marciano.id;

    // move martian
    while (!(marciano.posX == (N - 1) && marciano.posY == (N - 1)) && times < burst * 10)
    {
        // gives random number between 0-99
        // to generate random numbers. Generate "decent" random numbers in c seems awfully complicated
        srand(clock());
        int random_number = rand();
        int random_in_range = random_number % 100;

        /*
        printf("numero aleaotrio");
        printf("%d",random_in_range);
        printf("\n");*/

        printCurrentMatrix(matrix);
        printf("************************\n");

        //avoid the marcian getting stuck in the first posistion
        if(marciano.posX==1 && marciano.posY==0 ){
            matrix[marciano.posY][marciano.posX] = 1;
            matrix[marciano.posY + 1][marciano.posX] = marciano.id;
            marciano.posY++;
        }

        else if(marciano.posX==0 && marciano.posY==0){
            matrix[marciano.posY][marciano.posX] = 1;
            matrix[marciano.posY][marciano.posX + 1] = marciano.id;
            marciano.posX++;
        }

        //martian finished:
        else if(marciano.posX==(N-1) && marciano.posY==(N-1)){
            matrix[marciano.posY][marciano.posX] = 1;
            printf("El marciano completo el laberinto \n");
        }

        // moves →
        else if (marciano.posX < N && random_in_range <= 25 && matrix[marciano.posY][marciano.posX + 1] == 1)
        {
            matrix[marciano.posY][marciano.posX] = 1;
            matrix[marciano.posY][marciano.posX + 1] = marciano.id;
            marciano.posX++;
            // printf("1\n");
        }

        // moves ←
        else if (marciano.posX > 0 && random_in_range > 25 && random_in_range <= 50 && matrix[marciano.posY][marciano.posX - 1] == 1)
        {
            matrix[marciano.posY][marciano.posX] = 1;
            matrix[marciano.posY][marciano.posX - 1] = marciano.id;
            marciano.posX--;
            // printf("2\n");
        }

        // moves ↑
        else if (marciano.posY > 0 && random_in_range > 50 && random_in_range <= 75 && matrix[marciano.posY - 1][marciano.posX] == 1)
        {
            matrix[marciano.posY][marciano.posX] = 1;
            matrix[marciano.posY - 1][marciano.posX] = marciano.id;
            marciano.posY--;
            // printf("3\n");
        }

        // moves ↓
        else if (marciano.posY < N && random_in_range > 65 && random_in_range <= 99 && matrix[marciano.posY + 1][marciano.posX] == 1)
        {
            matrix[marciano.posY][marciano.posX] = 1;
            matrix[marciano.posY + 1][marciano.posX] = marciano.id;
            marciano.posY++;
            // printf("4\n");
        }
        // NOP
        else
        {
            // printf("5\n");
            ;
        }
        int valorUsuario;
        scanf("%d", &valorUsuario);
        if (valorUsuario == 0)
        {
            break;
        }

        // usleep(1000000);
        usleep(100000);
        times++;
        printf("Times: %d  \n", times);
    }
    printf("El tiempo para este marciano termino\n");

    matrix[N - 1][N - 1] = 0;
}