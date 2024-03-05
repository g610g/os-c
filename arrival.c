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

void print_list(Process* head){
    Process* temp = head;
    printf("List elements:\n");
    while(temp != NULL){
        if (temp->prev == NULL){
            printf("current value: %d prev NULL \n", temp->burst_time);
            
        }else{
            printf("current value: %d prev value: %d\n", temp->burst_time, temp->prev->burst_time);
        }
        temp = temp->next;
    }

}
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
    // print_list(head);
    return head;
}

void print_current_nodes(Process** nodes, int length){
    printf("Current list in the array: ");
    for (int i = 0; i < length; i++)
    {
        printf("Burst time: %d id: %d\n", nodes[i]->burst_time, nodes[i]->id);
    }
    
}
int get_next_arrival_time(int current_time, Process* head){
    Process* temp = head;
    while(temp != NULL){
        if (temp->arrival_time != current_time){
            return temp->arrival_time;
        }
        temp = temp->next;
    }
}
Process* update_list(Process* head, int id_arr_length, int* ids){
    Process* temp = head, *next = NULL;
    int i = 0;
    while(i < id_arr_length || temp != NULL){
        //if the to be deleted is the head of the list
        if (temp == head && ids[i] == temp->id){
            head = temp->next;
            temp->next->prev = NULL;
            free(temp);
            temp = head->next;
            i++;
        }else if(ids[i] == temp->id){
            temp->next->prev = temp->prev;
            temp->prev->next = temp->next;
            next = temp->next;
            free(temp);
            temp = next;
            i++;
        
        }else{
            temp = temp->next;
        }
    }
    return head;
}
//we have to get the next arrival time of this
int process_nodes_array(Process** nodes, int length, int current_time, int next_time, int* ids, int id_index){
    for (int i = 0; i < length; i++)
    {
        int difference = next_time - current_time;
        //might be the head of the list 
        //head might be updated
        if (nodes[i]->burst_time <= next_time){
            if (difference > nodes[i]->burst_time){
                current_time = nodes[i]->burst_time;
                //push the id to be deleted in the list
                ids[id_index] = nodes[i]->id;
                id_index++;
                continue;
            }else if (difference < nodes[i]->burst_time){
                //updates only in the node
                nodes[i]->burst_time -= difference;
                current_time = next_time;
                //load again into the array
            }

        }
    }
    return id_index;
}

//load the task that has the same time into the array
Process* load_array(Process*head, int arrival_time){
    Process** nodes = malloc(sizeof(Process*) * MAX);
    int ids[MAX];
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
    int id_arr_length = process_nodes_array(nodes, i, arrival_time, get_next_arrival_time(arrival_time, head), ids, 0);
    head = update_list(head, id_arr_length, ids);
    free(nodes);
    print_list(head);
    return head;
}


int main(void){
    Process* processes = NULL;
    int arrival = 0;
    processes = initialize(processes, 5);
    load_array(processes, arrival);
    // while (processes != NULL)
    // {
    //     load_array(processes, arrival);
    // }
    // print_current_nodes(nodes, &start,&end);
    // print_list(processes);
    int current_process_index = 0;

}