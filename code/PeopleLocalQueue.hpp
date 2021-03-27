#ifndef localqueue_hpp
#define localqueue_hpp

#include <iostream>
#include <stdint.h>
#include "Person.hpp"

class PeopleLocalNode
{
private:
    friend class PeopleLocalQueue;
    PeopleLocalNode* next;
    Person* person_ptr;
};

class PeopleLocalQueue
{
private:
    PeopleLocalNode* front;
    PeopleLocalNode* back;
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
