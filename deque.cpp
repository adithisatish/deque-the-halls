#include "deque.h"
#include<iostream>
#include<mutex>

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
    mutexBack.lock();
    bool flag = false;
    if(_length == 0){
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
    Node* newNode = createNode(data);
    mutexFront.lock();
    bool flag = false;
    if(_length == 0){
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
    mutexFront.lock();
    if (_length == 1){
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
    mutexBack.lock();
    if (_length == 1){
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
    mutexFront.lock();
    bool frontLocked = true;
    Node* cur = head;
    while(cur) {
        std::cout<<cur -> data<<" ";
        cur = cur -> next;
        if(frontLocked){
            mutexFront.unlock();
            frontLocked = false;
        }
    }
    mutexBack.unlock();
    if(frontLocked)
        mutexFront.unlock();    
    std::cout<<std::endl;    
}

int Deque::length() {
    return _length;
}