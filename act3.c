#include <stdio.h>
#include <stdlib.h>
#define MAX_LEN 100
typedef struct Process
{
   int burst_time;
   int waiting_time;
   int turnaround_time;
   int id;
   int priority_id;
}Process;

Process* initialize_process(int* length){
    printf("Enter the no of processes: ");
    scanf("%d", length);
    Process* processes = malloc(sizeof(Process) * (*length));
    for (int i = 0; i < *length; i++){
        printf("Enter Burst Time and Priority for process %d : ", i);
        scanf("%d \t %d", &processes[i].burst_time, &processes[i].priority_id);
        if (processes[i].priority_id > *length || processes[i].priority_id <= 0){
            printf("Out of range! priority ID!");
            exit(1);
        }
        processes[i].id = i;
    }
  
    return processes;
}
Process * sort_process(Process *processes, int length){
    Process temp;
    for (int i = 0; i < length; i++){
        if (i == length - 1)
            break;
        for(int j = i + 1; j < length; j++){
            if (processes[j].priority_id < processes[i].priority_id){
                temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }
    return processes;
}

void calculate(Process* processes, int length){
    printf("Output\n");
    printf("Process\t\tPriority\t\tBurst Time\t\tWaiting Time\t\t Turn Around Time\n");
    float total_waiting = 0;
    float overall_waiting = 0;
    float overall_turnaround = 0;
    float total_turnaround = 0;
    for(int i = 0; i < length; i++){
        processes[i].waiting_time = total_waiting;
        processes[i].turnaround_time = processes[i].waiting_time + processes[i].burst_time;
        printf("P:%d\t\t %d\t\t%d\t\t\t\t%d\t\t\t\t%d\n", processes[i].id,processes[i].priority_id, processes[i].burst_time, processes[i].waiting_time, processes[i].turnaround_time);
        total_waiting= processes[i].burst_time + total_waiting;
        total_turnaround+=processes[i].turnaround_time;
    }
    for (int i = 0;  i < length; i++){
        overall_waiting+=processes[i].waiting_time;
        overall_turnaround+=processes[i].turnaround_time;
    }
    printf("Average Waiting Time: %f\n",  overall_waiting / length);
    printf("Average Turnaround Time: %f", overall_turnaround / length);
}
int main(void){
    int length = 0, slice_time;
    Process* processes; 
    processes = initialize_process(&length);
    processes = sort_process(processes, length);
    calculate(processes, length);
    free(processes);
}