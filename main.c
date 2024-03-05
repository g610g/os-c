#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100
//creates queue structure for the sake of FIFO behavior
typedef struct Queue{
    int storage[MAX_SIZE];
    int waiting_time[MAX_SIZE];
    int turnaround_time[MAX_SIZE];
    int length;
    float average_waiting_time;
    float average_turaround_time;
}Queue;

//initialize a queue
Queue* initialize_queue(int process_value){
    Queue* queue = malloc(sizeof(Queue));
    queue->length = process_value;
    queue->average_waiting_time = 0;
    queue->average_turaround_time = 0;
    int burst_time;
    for (int i = 0; i < process_value; i++)
    {
        printf("Enter burst Time for Process %d:", i);
        scanf("%d", &burst_time);
        queue->storage[i] = burst_time;
    }
    
    return queue;
}
void calculate_waiting_time(Queue* queue){
    int waiting_time = 0;
    for(int i = 0; i < queue->length; i++){
        queue->waiting_time[i] = waiting_time;
        waiting_time+=queue->storage[i];
    }
    
}
void calculate_everything(Queue* queue){
    int turaround_time = queue->storage[0];
    printf("Process\t\tBurst Time\t\tWaiting Time\t\t Turn Around Time\n");
 
    for(int i = 0; i < queue->length; i++){
        printf("Output\n");
        printf("P:%d\t\t%d\t\t\t\t%d\t\t\t\t%d\n", i, queue->storage[i], queue->waiting_time[i], turaround_time);
        queue->turnaround_time[i] = turaround_time;
        turaround_time+=queue->storage[i + 1];
    }
    for(int i = 0; i < queue->length; i++){
        queue->average_waiting_time+=queue->waiting_time[i];
    }
    for(int i = 0; i < queue->length; i++){
        // printf("%d\n", queue->turnaround_time[i]);
        queue->average_turaround_time+=queue->turnaround_time[i];
    }
    printf("Average Waiting Time-- %f\n", queue->average_waiting_time / queue->length);
    printf("Average Turnaround Time: %f", queue->average_turaround_time / queue->length);
}
int main(void)
{
    int processes_number;
    Queue* queue;
    printf("Enter the number of processes");
    scanf("%d", &processes_number);
    queue = initialize_queue(processes_number);
    calculate_waiting_time(queue);
    calculate_everything(queue);
    free(queue);
    return 0;
}

