#include "deque.h"
#include<stdlib.h>

Node* createNode(int data, Node* prev = NULL, Node* next = NULL) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->prev = prev;
    newNode->next = next;
    return newNode;
}

void enqueueBack(Deque* deque, int data) {
    Node* newNode = createNode(data);
    if(deque->tail == NULL) {
        deque->tail = newNode;
        deque->head = newNode;
    } else {
        deque->tail->next = newNode;
        newNode->prev = deque->tail;
        deque->tail = newNode;
    }
    ++deque->length;
}

void enqueueFront(Deque* deque, int data) {
    Node* newNode = createNode(data);
    if(deque->head == NULL) {
        deque->tail = newNode;
        deque->head = newNode;
    } else {
        newNode->next = deque->head;
        deque->head->prev = newNode;
        deque->head = newNode;
    }
    ++deque->length;
}

int dequeueFront(Deque* deque) {
    if(deque->head){
        int temp = deque->head->data;
        Node* newHead = deque->head->next;
        if(newHead)
            newHead->prev = NULL;            
        free(deque->head);
        deque->head = newHead;        
        --deque->length;
        if(deque->length == 0)
            deque->tail = NULL;
        return temp;
    }
}

int dequeueBack(Deque* deque) {
    if(deque->tail){
        int temp = deque->tail->data;
        Node* newTail = deque->tail->prev;
        if(newTail)
            newTail->next = NULL;
        free(deque->tail)
        deque->tail = newTail;
        --deque->length;
        if(deque->length == 0)
            deque->head = NULL;
        return temp;
    }
}

int peekFront(Deque* deque) {
    if(deque->head)
        return deque->head->data;
}

int peekBack(Deque* deque) {
    if(deque->tail)
        return deque->tail->date;
}

int length(Deque* deque) {
    return deque->length;
}