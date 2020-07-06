# Concurrent Deque Implementation
#### To run
1. ``` make ```

2. Generate test cases
``` python3 generator.py > t1.txt ```

3. ``` ./a < t1.txt ```

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
    - To prevent race condition that may occur during a dequeue when there's a single element,
      since front and back are the same node.

4.  ```C++
    std::mutex enqueueCommon;
    ```
    - To prevent race condition that may occur during an enqueue when there's no elements.

#### Methods implemented:
1.  ```C++
    void Deque::enqueueFront(int data);
    ```
    - Function to enqueue an element at the front.
    - Utilizes two locks, ```mutexFront``` that's always used, ```enqueueCommon``` that's used only when there's 0 elements at the moment on enqueueing.

2.  ```C++
    void Deque::enqueueBack(int data);
    ```
    - Function to enqueue an element at the back.
    - Utilizes two locks, ```mutexBack``` that's always used, ```enqueueCommon``` that's used only when there's 0 elements at the moment on enqueueing.

3.  ```C++
    void Deque::dequeueFront();
    ```
    - Function to dequeue an element from the front.
    - Utilizes two locks, ```mutexFront``` that's always used, ```dequeueCommon``` that's used only when there's a single element at the moment of dequeing.

4.  ```C++
    void Deque::dequeueBack();
    ```
    - Function to dequeue an element from the back.
    - Utilizes two locks, ```mutexBack``` that's always used, ```dequeueCommon``` that's used only when there's a single element at the moment of dequeing.

5.  ```C++
    void Deque::display();
    ```
    - Functino to print all elements from the front of the queue to the back.
    - Locks both ```mutexBack``` and ```mutexFront``` in the beginning.
    - ```mutexFront``` is unlocked as soon as the first element has been traversed, because the front can be modified freely at  that point.
    - ```mutexBack``` is unlocked only when the entire queue has been traversed.
