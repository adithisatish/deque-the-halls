#include<mutex>

struct Node {
    int data;
    Node* next;
    Node* prev;
};

class Deque {
    Node* head;
    Node* tail;
    int _length;
    std::mutex mutexFront;
    std::mutex mutexBack;
    std::mutex dequeueCommon;
    public:
        Deque();
        void enqueueBack(int);
        void enqueueFront(int);
        void dequeueFront();
        void dequeueBack();
        int peekFront();
        int peekBack();
        int length();
        void display();
};

Node *createNode(int, Node*, Node*);