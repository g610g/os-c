#include <stdio.h>
#include <stdlib.h>
#define MAX 100
typedef struct Process
{
    int burst_time;
    int arrival_time;
//    int waiting_time;
//    int turnaround_time;
    int id;
    struct Process* next; 
    struct Process* prev;
}Process;
//we have to sort this part right here
Process* initialize(Process* head, int val){
    // Process* processes = malloc(sizeof(Process) * val);
    int burst_time = 0, id, arrival_time; 
    Process* prev = NULL;
    for (int i = 0; i < val; i++){
        printf("Enter burst time for process:%d ", i);
        scanf("%d", &burst_time);    
        printf("Enter arrival time for process %d ", i);
        scanf("%d", &arrival_time);
        Process* node = malloc(sizeof(Process));
        node->burst_time = burst_time;
        node->arrival_time = arrival_time;
        node->id = i;
        node->next = NULL;
        node->prev = NULL;
        if (head == NULL){
            head = node;
            prev = node;
            continue;
        }
        prev->next = node;
        node->prev = prev;
        prev = node;
    }
    return head;
}

void print_current_nodes(Process** nodes, int length){
    printf("Current list in the array: ");
    for (int i = 0; i < length; i++)
    {
        printf("Burst time: %d id: %d", nodes[i]->burst_time, nodes[i]->id);
    }
    
}
void process_nodes_array(Process** nodes, int length, int current_time){
    for (int i = 0; i < length; i++)
    {
        //there is a bug right here the calculation of burst time and current time 
        if (current_time == 0){
            current_time = nodes[i]->burst_time;
            //remove the node in the list
            nodes[i]->prev->next = nodes[i]->next;
            nodes[i] 
        }
        if (current_time < nodes[i]->burst_time){

            nodes[i]->burst_time -= current_time;
            current_time+=nodes[i]->burst_time;
        }
    }
    
}
//load the task that has the same time into the array
Process** load_array(Process*head, int arrival_time){
    Process** nodes = malloc(sizeof(Process*) * MAX);
    Process* temp = head;
    int i = 0;
    while (temp != NULL){
        if (temp->arrival_time == arrival_time){
            nodes[i] = temp;
            i++;
        }
        temp = temp->next;
    }
    print_current_nodes(nodes, i);
    return nodes;
    
}



void print_list(Process* head){
    Process* temp = head;
    while(temp != NULL){
        printf("%d-> ", temp->burst_time);
        temp = temp->next;
    }

}

int main(void){
    Process* processes = NULL;
    int arrival = 0;
    processes = initialize(processes, 5);
    load_array(processes, arrival);
    // print_current_nodes(nodes, &start,&end);
    // print_list(processes);
    int current_process_index = 0;

}