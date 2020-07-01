#include "deque.h"
#include<iostream>

Node* createNode(int data, Node* prev = 0, Node* next = 0) {
    Node* newNode = new Node;
    newNode->data = data;
    newNode->prev = prev;
    newNode->next = next;
    return newNode;
}

Deque::Deque() {
    head = nullptr;
    tail = nullptr;
    _length = 0;
}

void Deque::enqueueBack(int data) {
    Node* newNode = createNode(data);
    if(tail == nullptr) {
       tail = newNode;
       head = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    ++_length;
}

void Deque::enqueueFront(int data) {
    Node* newNode = createNode(data);
    if(head == nullptr) {
        tail = newNode;
        head = newNode;
    } else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
    ++_length;
}

int Deque::dequeueFront() {
    if(head){
        int temp = head->data;
        Node* newHead = head->next;
        if(newHead)
            newHead->prev = nullptr;            
        delete head;
        head = newHead;        
        --_length;
        if(_length == 0)
            tail = nullptr;
        return temp;
    }
}

int Deque::dequeueBack() {
    if(tail){
        int temp = tail->data;
        Node* newTail = tail->prev;
        if(newTail)
            newTail->next = nullptr;
        delete tail;
        tail = newTail;
        --_length;
        if(_length == 0)
            head = nullptr;
        return temp;
    }
}

void Deque::display() {
    Node* cur = head;
    while(cur) {
        std::cout<<cur -> data<<" ";
        cur = cur -> next;
    }
    std::cout<<std::endl;
}

int Deque::peekFront() {
    if(head)
        return head->data;
}

int Deque::peekBack() {
    if(tail)
        return tail->data;
}

int Deque::length() {
    return _length;
}