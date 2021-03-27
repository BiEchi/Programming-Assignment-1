#include <stdint.h>
#include "Person.hpp"

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
    void init(void);
    void pushBack(Person *const ptr);
    Person *popFront(void);
    int deleteNode(const Person *thePerson);
};

// Please call init function when creating new local queue.
void PeopleLocalQueue::init(void)
{
    front = NULL;
    back = NULL;
    length = 0;
    return;
}
// When the input pointer is NULL, the function will do nothing.
void PeopleLocalQueue::pushBack(Person *const ptr)
{
    if (NULL == ptr)
    {
        return;
    }
    PeopleLocalNode *temp = new PeopleLocalNode;
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

Person *PeopleLocalQueue::popFront(void)
{
    //if the queue is empty, function will return NULL
    if (0 == length)
    {
        return NULL;
    }
    PeopleLocalNode *temp = front;
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

/*
 * OUTPUT:
 * 1    the person has been removed from the queue successfully
 * 0    the person is not in the queue
 */
int PeopleLocalQueue::deleteNode(const Person *thePerson)
{
    if (0 == length)
    {
        return 0;
    }
    PeopleLocalNode *itor;
    PeopleLocalNode *temp;
    int i;
    itor = front;

    if (itor->person_ptr == thePerson)
    {
        popFront();
    }
    for (i = 1, itor = front; i < length; i++, itor = itor->next)
    {
        if (itor->next->person_ptr != thePerson)
        {
            continue;
        }
        else
        {
            // the person is in the the queue
            if ((length - 1) == i)
            {
                temp = back;
                back = itor;
                back->next = NULL;
                delete temp;
                return 1;
            }
            else
            {
                temp = itor->next;
                itor->next = temp->next;
                delete temp;
                return 1;
            }
        }
    }
    return 0;
}