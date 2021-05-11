#ifndef localqueue_hpp
#define localqueue_hpp

#include "Person.hpp"
#include <iostream>
#include <stdint.h>
#include <stdio.h>

// class for each node
class PeopleLocalNode
{
    friend class PeopleLocalQueue;
    PeopleLocalNode *next;
    Person *person_ptr;
};

// class for each queue
class PeopleLocalQueue
{
    PeopleLocalNode *front = NULL;
    PeopleLocalNode *back = NULL;
    int32_t length = 0;

public:
    int32_t getLength(void)
    {
        return length;
    }
    int init(void);
    bool display(void);
    
    int pushBack(Person *const ptr);
    Person *popFront(void);

    string returnID(int pos);
    Person* isIn(string ID);
    int doWithdraw(Person *thePerson);
};

#endif
