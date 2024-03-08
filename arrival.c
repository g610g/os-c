#include <stdio.h>
#include <stdlib.h>
#define MAX 100
typedef struct Process
{
    int burst_time;
    int arrival_time;
    int waiting_time;
    int turnaround_time;
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
    int burst_time = 0, id, arrival_time = 0, prev_arrival = 0; 
    Process* prev = NULL;
    for (int i = 0; i < val; i++){
        printf("Enter arrival time and burst time  for process:%d ", i + 1);
        scanf("%d %d", &arrival_time, &burst_time);
        if (prev_arrival > arrival_time){
            printf("Invalid input arrival time\n");
            exit(0);
        }
        Process* node = malloc(sizeof(Process));
        node->burst_time = burst_time;
        node->arrival_time = arrival_time;
        node->id = i + 1;
        node->next = NULL;
        node->prev = NULL;
        if (head == NULL){
            head = node;
            prev = node;
            prev_arrival = arrival_time;
            continue;
        }
        prev->next = node;
        node->prev = prev;
        prev = node;
        prev_arrival = arrival_time;
    }
    // print_list(head);
    return head;
}

void print_current_nodes(Process** nodes, int length){
    printf("Current list in the array: \n");
    for (int i = 0; i < length; i++)
    {
        printf("Burst time: %d id: %d\n", nodes[i]->burst_time, nodes[i]->id);
    }
}
//problem here for finding the arrival time
int get_next_arrival_time(int* current_time, Process* head){
    Process* temp = head;
    while(temp != NULL){
        if (temp->arrival_time != (*current_time) && temp->arrival_time > (*current_time)){
            return temp->arrival_time;
        }
        temp = temp->next;
    }
}
Process* update_list(Process* head, int id_arr_length, int* ids){
    Process* temp = head, *next = NULL;
    int i = 0;
    while(i < id_arr_length && temp != NULL){
        //if the to be deleted is the head of the list
        if (temp == head && ids[i] == temp->id){
            head = temp->next;
            if (head == NULL){
                free(temp);
                return head;
            }
            head->prev = NULL;
            free(temp);
            temp = head;
            i++;
        }else if(ids[i] == temp->id){
            next = temp->next;
            //seg fault happens here
            if (next == NULL){
                temp->prev->next = NULL;
                Process* new_temp = temp->prev;
                free(temp);
                temp = new_temp;
                i++;
                continue;
            }
            next->prev = temp->prev;
            temp->prev->next = next;
            free(temp);
            temp = next;
            i++;
        }else{
            temp = temp->next;
        }
    }
    return head;
}
void sort_process_array(Process** nodes, int length){
    for(int i = 0; i < length; i++){
        for (int j = i + 1; j < length; j++){
            if (nodes[i]->burst_time > nodes[j]->burst_time){
                Process* temp = nodes[i];
                nodes[i] = nodes[j];
                nodes[j] = temp;
            }
        }
    }
}
//we have to get the next arrival time of this
int process_nodes_array(Process** nodes, int length, int* current_time, int next_time, int* ids, int id_index, int* waiting_time, int* last_executed_id){
    //might be the last or all nodes have the same arrival time
    //if all of the process has the same time arrival then we can just process each of it 
    sort_process_array(nodes, length);
    if (next_time == 0){      
        for (int i = 0; i < length; i++){
            ids[id_index] = nodes[i]->id;
            id_index++;
            (*current_time) += nodes[i]->burst_time;
            printf("P%d\t\t\t\t%d\t\t%d\t\t%d\n", nodes[i]->id,nodes[i]->burst_time,(*waiting_time), (nodes[i]->burst_time + (*waiting_time)));
            (*waiting_time) += nodes[i]->burst_time;
        }
        return id_index;
    }
    for (int i = 0; i < length; i++)
    {
        int difference = next_time - (*current_time);
        //might be the head of the list 
        //head might be updated
        
        if (difference >= nodes[i]->burst_time){
            (*current_time) += nodes[i]->burst_time;
            //push the id to be deleted in the list
            ids[id_index] = nodes[i]->id;
            printf("P%d\t\t\t\t%d\t\t%d\t\t%d\n",nodes[i]->id, nodes[i]->burst_time, (*waiting_time), (nodes[i]->burst_time + (*waiting_time)));
            (*waiting_time) += nodes[i]->burst_time;
            id_index += 1;
        }else if (difference == 0){
                //ireturn lang sa para na maka process napod og another nga nodes
        }
        // else if (difference < nodes[i]->burst_time){
        //     if ((*last_executed_id) != nodes[i]->id){
        //         //do not print it yet,
        //         nodes[i]->waiting_time = (*waiting_time);

        //     }
        // }
        else if (difference < nodes[i]->burst_time){
            //updates only in the node no need to put in array
            nodes[i]->burst_time -= difference;
            (*last_executed_id) = nodes[i]->id;
            printf("P%d\t\t\t\t%d\t\t%d\t\t%d\n", nodes[i]->id, difference, (*waiting_time), (difference + (*waiting_time)));
            (*waiting_time) += difference;
            nodes[i]->waiting_time = (*waiting_time); 
            (*current_time) = next_time;
            //load again into the array
            }
    }
    (*current_time) = next_time;
    (*waiting_time) = next_time;
    return id_index;
}

//load the task that has the same time into the array
Process* load_array(Process*head, int* arrival_time, int* waiting_time, int* last_executed_id){
    Process** nodes = malloc(sizeof(Process*) * MAX);
    int ids[MAX];
    Process* temp = head;
    int i = 0;
    while (temp != NULL){
        if (temp->arrival_time == (*arrival_time) || temp->arrival_time < (*arrival_time)){
            nodes[i] = temp;
            i++;
        }
        temp = temp->next;
    }
    // print_current_nodes(nodes, i);
    // printf("at time: %d\n", (*arrival_time));
    int id_arr_length = process_nodes_array(nodes, i, arrival_time, get_next_arrival_time(arrival_time, head), ids, 0, waiting_time, last_executed_id);
    head = update_list(head, id_arr_length, ids);
    free(nodes);
    // print_list(head);
    return head;
}


int main(void){
    Process* processes = NULL;
    int arrival = 0, waiting_time = 0, last_executed_id = 0;

    processes = initialize(processes, 3);
    // processes = load_array(processes, &arrival);
    // processes = load_array(processes, &arrival);
    printf("Output:\n");
    printf("Process\t\t Burst Time\t\tWaiting Time\t\tTurn-around Time\n");
    while (processes != NULL)
    {
        processes = load_array(processes, &arrival, &waiting_time, &last_executed_id);
    }
    // print_list(processes);
    int current_process_index = 0;

}