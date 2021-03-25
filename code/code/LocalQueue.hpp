#ifndef localqueue_hpp
#define localqueue_hpp

#include <iostream>
#include <stdint.h>
#include "Person.hpp"
#include "LocalQueue.hpp"

class localNode 
{
private:
    friend class localQueue;
    localNode* next;
    Person* person_ptr;
};

class localQueue 
{
private:
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


#endif