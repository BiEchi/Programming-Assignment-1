#include <iostream>
#include <stdint.h>
#include "Person.hpp"
#include "PeopleLocalQueue.hpp"

void PeopleLocalQueue::init(void)
{
    front = NULL; back = NULL; 
    length = 0;
    return;
}

void PeopleLocalQueue::pushBack(Person* const ptr)
{
    if (NULL == ptr) {return;}
    PeopleLocalNode* temp = new PeopleLocalNode;
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

Person* PeopleLocalQueue::popFront(void)
{
    if (0 == length) {return NULL;}
    PeopleLocalNode* temp = front;
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

