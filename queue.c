#include <stdio.h>
#include <stdlib.h>
#define  SIZE 20
#define MAX_BUF 10
typedef struct Queue{
    int buffer[SIZE];
    int front;
    int tail;
    int counter;
}Queue;

void push_q(Queue* q, int val){
    if ((q->counter) >= MAX_BUF){
        printf("Buffer is full cannot add more to the queue");
        return;
    }
    if (q->front == -1 && q->tail == 0){
        q->buffer[q->tail] = val;
        q->counter++;
        q->front++;
        q->tail++;
        return;
    }
    q->buffer[q->tail] = val;
    q->counter++;
    q->tail++;
    return;
}
void pop_q(Queue* q){
    if (q->front == -1){
        printf("Error nothing to be popped on empty list\n");
        return;
    }
    if (q->front == (q->tail - 1) && q->counter <= 0){
        printf("Popped element: %d\n", q->buffer[q->front]);
        q->counter--;
        return;
    }
    printf("Popped element: %d\n", q->buffer[q->front]);
    q->counter--;
    q->front++;
    return;
}
void print_q(Queue* q){
    printf("List:");
    for (int i = q->front; i < q->tail; i++){
        printf("%d ", q->buffer[i]);
    }
    return;
}

int main(void){
    Queue queue = {.front=-1, .tail=0, .counter=0};
    push_q(&queue, 1);
    push_q(&queue, 2);
    push_q(&queue, 3);
    push_q(&queue, 4);
    push_q(&queue, 1);
    pop_q(&queue);
    pop_q(&queue);
    pop_q(&queue);
    print_q(&queue);
    
}