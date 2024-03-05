#include <stdio.h>
#include <stdlib.h>

typedef struct Process{
    int burst_time;
    int waiting_time;
    int turnaround_time;
    int process_value;
}Process;

Process* initialize_processes(int * length){
    int processes_length = 0;
    printf("Enter the number of processes: ");
    scanf("%d", &processes_length);
    *length = processes_length;
    Process* processes = malloc(sizeof(Process) * processes_length);
    for(int i = 0; i < processes_length; i++){
        printf("Enter Burst Time for Process %d:", i);
        scanf("%d", &processes[i].burst_time);
        processes[i].process_value = i;
    }
    
    return processes;
}
Process* sort_processes(Process* processes, int length){
    int temp;
    for (int i = 0; i < length; i++){
        if (i == length - 1)
            break;
        for(int j = i + 1; j < length; j++){
            if (processes[j].burst_time < processes[i].burst_time){
                temp = processes[i].burst_time;
                processes[i].burst_time = processes[j].burst_time;
                processes[j].burst_time = temp;
            }
        }
    }
    int waiting_time = 0;
    for(int i = 0; i < length; i++){
        processes[i].waiting_time = waiting_time;
        waiting_time+=processes[i].burst_time;
    }
    int turnaround_time = processes[0].waiting_time;
    for (int i = 0; i < length; i++){
        processes[i].turnaround_time = processes[i].waiting_time + processes[i].burst_time;
    }
    // for(int i = 0; i < length; i++){
    //     printf("values:%d\n", processes[i].turnaround_time);
    // }
    return processes;
}
void calculate(Process* processes, int length){
    printf("Output\n");
    printf("Process\t\tBurst Time\t\tWaiting Time\t\t Turn Around Time\n");
    float total_waiting = 0;
    float total_turnaround = 0;
    for(int i = 0; i < length; i++){
        printf("P:%d\t\t%d\t\t\t\t%d\t\t\t\t%d\n", processes[i].process_value, processes[i].burst_time, processes[i].waiting_time, processes[i].turnaround_time);
        total_waiting+=processes[i].waiting_time;
        total_turnaround+=processes[i].turnaround_time;
    }
    printf("Average Waiting Time: %f\n",  total_waiting / length);
    printf("Average Turnaround Time: %f", total_turnaround / length);
}
int main(void){
    int length = 0; 
    Process* processes_pointer;
    processes_pointer = initialize_processes(&length);
    processes_pointer = sort_processes(processes_pointer, length);
    calculate(processes_pointer, length);
    free(processes_pointer);
}
