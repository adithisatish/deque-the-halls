typedef struct node {
    int data;
    struct node* next;
    struct node* prev;
} Node;

typedef struct deque {
    Node* head;
    Node* tail;
    int length;
} Deque;

Node* createNode(int, Node*, Node*);
void enqueueBack(Deque*, int);
void enqueueFront(Deque*, int);
int dequeueFront(Deque*);
int dequeueBack(Deque*);
int peekFront(Deque*);
int peekBack(Deque*);
int length(Deque*);