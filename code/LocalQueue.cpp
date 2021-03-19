#include <stdint.h>
#include "Person.hpp"

// class for each node 
class localNode {
    friend class localQueue;
    localNode* next;
    Person* person_ptr;
};

// class for each queue
class localQueue {
    localNode* front;
    localNode* back;
    int32_t length;
public:
    int32_t getLength(void) {
        return length;
    }
    void init(void);
    void pushBack(Person* const ptr);
    Person* popFront(void);
};

// Please call init function when creating new local queue.
void localQueue::init(void) {
    front = NULL; back = NULL; 
    length = 0;
    return;
}
// When the input pointer is NULL, the function will do nothing.
void localQueue::pushBack(Person* const ptr) {
    if (NULL == ptr) {return;}
    localNode* temp = new localNode;
    if (0 == length) {
        temp->next = NULL;
        temp->person_ptr = ptr;
        front = temp;
        back = temp;
        length++;
        return;
    } else {
        temp->next = NULL;
        temp->person_ptr = ptr;
        back->next = temp;
        back = temp;
        length++;
        return;
    }
}

Person* localQueue::popFront(void) {
    //if the queue is empty, function will return NULL
    if (0 == length) {return NULL;}
    localNode* temp = front;
    Person* ptr = temp->person_ptr;
    if (NULL == temp->next) {
        front = NULL;
        back = NULL;
    } else {
        front = temp->next;
    }
    delete temp;
    length--;
    return ptr;
}

