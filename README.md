# Concurrent Deque Implementation

A deque is an abstract data structure that generalizes a queue, allowing insertion(enqueuing) and deletion(dequeuing) of elements from both front and rear ends. This repository contains the concurrent implementation of the same.

#### To run
1. ``` make ```

2. There are 3 input text files provided. However, the following command can be executed to generate other (randomized) test cases:
``` 
python3 generator.py > input.txt 
```

3. ``` ./a < input.txt ```

<<<<<<< HEAD
=======
#### Implementation
- Follows a linked list implementation as opposed to using ```std::deque``` from the template library
- Makes use of 4 mutex locks to ensure synchronization
    
#### Locks used:
1.  ```C++
    std::mutex mutexFront;
    ```
    - To lock the front of the queue, preventing simultaneous enqueue and dequeue operations on the front.

2.  ```C++
    std::mutex mutexBack;
    ```
    - To lock the back of the queue, preventing simultaneous enqueue and dequeue operations on the back.

3.  ```C++
    std::mutex dequeueCommon;
    ```
    - To prevent race condition that may occur during a dequeue operation performed on a deque consisting of only one element,
      since front and back are the same node.

4.  ```C++
    std::mutex enqueueCommon;
    ```
    - To prevent race condition that may occur while enqueuing into an empty deque.

#### Methods implemented:
1.  ```C++
    void Deque::enqueueFront(int data);
    ```
    - Function to enqueue an element at the front.
    - Utilizes two locks, ```mutexFront``` used always, and ```enqueueCommon``` , used only when the deque is empty at the time of enqueuing.

2.  ```C++
    void Deque::enqueueBack(int data);
    ```
    - Function to enqueue an element at the back.
    - Similar to ```enqueueFront```, it utilizes two locks, ```mutexBack``` used always, and ```enqueueCommon```, used only when the deque is currently empty.

3.  ```C++
    void Deque::dequeueFront();
    ```
    - Function to dequeue an element from the front.
    - Utilizes two locks, ```mutexFront``` that's always used, ```dequeueCommon``` ,used only when there's a single element at the moment of dequeing.

4.  ```C++
    void Deque::dequeueBack();
    ```
    - Function to dequeue an element from the back.
    - Similar to ```dequeueFront```, it utilizes two locks, ```mutexBack``` that's always used, ```dequeueCommon``` ,used only when there's a single element at the moment of dequeing.

5.  ```C++
    void Deque::display();
    ```
    - Function to print all elements from the front of the queue to the back.
    - Locks both ```mutexBack``` and ```mutexFront``` in the beginning.
    - ```mutexFront``` is unlocked as soon as the first element has been traversed, because the front can be modified freely at that point.
    - ```mutexBack``` is unlocked only when the entire queue has been traversed.
>>>>>>> 22260f3... Added documentation
