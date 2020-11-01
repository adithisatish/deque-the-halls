struct Node {
    int data;
    Node* next;
    Node* prev;
};

class Deque {
    Node* head;
    Node* tail;
    int _length;
    public:
        Deque();
        void enqueueBack(int);
        void enqueueFront(int);
        int dequeueFront();
        int dequeueBack();
        int peekFront();
        int peekBack();
        int length();
        void display();
};

Node *createNode(int, Node*, Node*);