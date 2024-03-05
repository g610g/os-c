#include <stdio.h>
#include <stdlib.h>
#define BUFFER_SIZE 10
typedef struct QueueList{
    int val;
    struct QueueList* next;
    int size;
}QueueList;
QueueList* consume(QueueList* queue, int* counter){
    if (*counter <= 0 || queue == NULL){
        printf("Nothing to consume! Empty\n");
        return queue;
    }
    QueueList* temp = queue;
    printf("Consumed Value is %d", temp->val);
    queue = temp->next;
    free(temp);
    --(*counter);
    return queue;
}
QueueList* produce(QueueList* queue, int* counter){

    int val;
    printf("Enter Value: ");
    scanf("%d", &val);
    QueueList* new_list = malloc(sizeof(QueueList));   
    new_list->val = val;
    new_list->next= NULL;
    if (*counter >= BUFFER_SIZE){
        printf("FULL!");
        return queue;
    }
    if (queue == NULL){
        queue = new_list;
        ++(*counter);
            // printf("counteR: %d\n", *counter);

        return queue;
    }
    QueueList* temp = queue;
    while(temp->next != NULL){
        temp = temp->next;
    }
    temp->next = new_list;
    ++(*counter);
    // printf("counteR: %d\n", *counter);
    return queue;
}
void print_list(QueueList* list){
    QueueList* temp = list;
    printf("List: ");
    while(temp != NULL){
        printf("%d ", temp->val);
        temp = temp->next;
    }
}
int main(void){
    QueueList* queue_head = NULL;
    int counter = 0;
    int choice;
    start:
    printf("\nEnter choice:\n");
    printf("1. Produce\n2.Consume\n3.Exit:\n");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        queue_head = produce(queue_head, &counter);
        print_list(queue_head);
        break;
    
    case 2:
        queue_head = consume(queue_head, &counter);
        break;
    default:
        exit(0);
    }
    
    goto start;
}