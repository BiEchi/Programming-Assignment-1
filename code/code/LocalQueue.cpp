#include <iostream>
#include <stdint.h>
#include "Person.hpp"
#include "LocalQueue.hpp"

void 
{
    front = NULL;
    back = NULL;
    length = 0;
    return;
}

void localQueue::pushBack(Person *const ptr)
{
    if (NULL == ptr)
    {
        return;
    }
    localNode *temp = new localNode;
    if (0 == length)
    {
        temp->next = NULL;
        temp->person_ptr = ptr;
        front = temp;
        back = temp;
        length++;
        return;
    }
    else
    {
        temp->next = NULL;
        temp->person_ptr = ptr;
        back->next = temp;
        back = temp;
        length++;
        return;
    }
}

Person *localQueue::popFront(void)
{
    if (0 == length)
    {
        return NULL;
    }
    localNode *temp = front;
    Person *ptr = temp->person_ptr;
    if (NULL == temp->next)
    {
        front = NULL;
        back = NULL;
    }
    else
    {
        front = temp->next;
    }
    delete temp;
    length--;
    return ptr;
}
