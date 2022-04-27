// gcc -o fcfs fcfs.c
// https://www.youtube.com/watch?v=EvyBpOQYgYE

#include <stdio.h>

struct PCB
{
    int pid, arrival, burst, turnaround;
};

void pline(int x);

void main(){

    int i, num, j;
    float avg = 0.0, sum = 0.0;
    struct PCB p[10], temp;
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
}

void pline(int x)
{
    int i;
    for(i=0; i<x; i++){
        printf("-");
    }
    printf("\n");
}