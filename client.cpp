#include<iostream>
#include "deque.h"

using namespace std;

// 1. Enqueue front
// 2. Enqueue back
// 3. Dequeue front
// 4. Dequeue back
// 5. Display

int main() {
    Deque deque;
    int choice = 0;
    int data;
    do {
        cin >> choice;
        switch(choice){
            case 1: cin >> data; deque.enqueueFront(data); break;
            case 2: cin >> data; deque.enqueueBack(data); break;
            case 3: deque.dequeueFront(); break;
            case 4: deque.dequeueBack(); break;
            case 5: deque.display(); break;
            default: choice = 0;
        }
    } while(choice);
    return 0;
}