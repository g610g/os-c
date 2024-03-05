#include <stdio.h>
#include<stdlib.h>
typedef struct Node{
    int value;
    struct Node* next;
}Node;

Node* create_node(int val){
    Node* new_node = malloc(sizeof(Node));
    new_node->value = val;
    new_node->next = NULL;
    return new_node;
}
Node* insertnode(Node* new_node, Node* head){
    if (head == NULL){
        head = new_node;
    }
    Node* temp = head;
    new_node->next = temp;
    head = new_node;
    return head;
}
void print_list(Node* head){
    Node* temp = head;
    while(temp->next != NULL){
        printf("%d-> ", temp->value);
        temp = temp->next;
    }
}
int main(void){

    Node* head  = NULL;
    head = insertnode(create_node(1), head);
    head = insertnode(create_node(3), head);
    head = insertnode(create_node(2), head);
    print_list(head);
}