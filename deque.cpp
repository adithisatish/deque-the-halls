#include "deque.h"
#include<iostream>
#include<mutex>

Node* createNode(int data, Node* prev = 0, Node* next = 0) {
    // Helper function to create a new node
    Node* newNode = new Node;
    newNode->data = data;
    newNode->prev = prev;
    newNode->next = next;
    return newNode;
}

Deque::Deque() {
    // Class constructor
    head = nullptr;
    tail = nullptr;
    _length = 0;
}

void Deque::enqueueBack(int data) {
    // Function to add element to back of queue
    Node* newNode = createNode(data);
    mutexBack.lock(); // Prevent another operation from happening at the back of the queue
    bool flag = false;
    if(_length == 0){ 
        // If the length is 0, an enqueue must not occur in the front in parallel
        enqueueCommon.lock();
        flag = true;        
    }
    if(tail == nullptr) {
       tail = newNode;
       head = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }    
    ++_length;
    if(flag)
        enqueueCommon.unlock();
    mutexBack.unlock();
}

void Deque::enqueueFront(int data) {
    // Function to add element to front of queue
    Node* newNode = createNode(data);
    mutexFront.lock(); // Prevent another operation from happening at the front of the queue
    bool flag = false;
    if(_length == 0){
        // If the length is 0, an enqueue must not occur in the back in parallel
        enqueueCommon.lock();
        flag = true;
    }
    if(head == nullptr) {
        tail = newNode;
        head = newNode;
    } else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }    
    ++_length;
    if(flag)
        enqueueCommon.unlock();
    mutexFront.unlock();
}

void Deque::dequeueFront() {
    bool flag = false;
    mutexFront.lock(); // Prevent another operation from happening in the front
    if (_length == 1){
        // If there's only 1 element, a parallel dequeue must not happen in the back
        dequeueCommon.lock();
        flag = true;
    }
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
    }
    mutexFront.unlock();
    if(flag)
        dequeueCommon.unlock();
}

void Deque::dequeueBack() {
    bool flag = false;
    mutexBack.lock(); // Prevent another operation from happening in the back
    if (_length == 1){
        // If there's only 1 element, a parallel dequeue must not happen in the front
        dequeueCommon.lock();
        flag = true;
    }
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
    }
    mutexBack.unlock();
    if(flag)
        dequeueCommon.unlock();
}

void Deque::display() {    
    mutexBack.lock();
    mutexFront.lock(); // Lock the front and back of the queue
    bool frontLocked = true;
    Node* cur = head;
    while(cur) {
        std::cout<<cur -> data<<" ";
        cur = cur -> next;
        if(frontLocked){
            /* After the first element has been traversed, 
                the front can be opened up to other operations */
            mutexFront.unlock();
            frontLocked = false; 
        }
    }
    mutexBack.unlock();
    // If there were no elements, the front may not have been unlocked previously
    if(frontLocked)
        mutexFront.unlock();    
    std::cout<<std::endl;    
}

int Deque::length() {
    return _length;
}