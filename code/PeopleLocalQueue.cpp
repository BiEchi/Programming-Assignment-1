#include "PeopleLocalQueue.hpp"

// Please call init function when creating new local queue.
int PeopleLocalQueue::init(void)
{
    front = NULL;
    back = NULL;
    length = 0;
    return 1;
}
// When the input pointer is NULL, the function will do nothing.
int PeopleLocalQueue::pushBack(Person *const ptr)
{
    if (NULL == ptr)
    {
        fprintf(stderr, "A NULL pointer is passed to function pushBack in PeopleLocalQueue. \n");
        return 0;
    }
    PeopleLocalNode *temp = new PeopleLocalNode;
    if (0 == length)
    {
        temp->next = NULL;
        temp->person_ptr = new Person;
        *temp->person_ptr = *ptr; // Use = to assign value!
        ptr->setCurrentStage(buffer); // Add for withdraw functionality. 
        front = temp;
        back = temp;
        length++;
        return 1;
    }
    else
    {
        temp->next = NULL;
        temp->person_ptr = new Person;
        *temp->person_ptr = *ptr; // Use = to assign value!
        back->next = temp;
        back = temp;
        length++;
        return 1;
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
    cout << "The removed person (at front) has ID " << ptr->getID() << "." << endl;
    delete temp;
    length--;
    return ptr;
}

/*
 * OUTPUT:
 * 1    the person has been removed from the queue successfully
 * 0    the person is not in the queue
 */
int PeopleLocalQueue::doWithdraw(Person *thePerson)
{
    if (0 == length)
    {
        cout << "The queue is empty when trying to delete a person." << endl;
        return 0;
    }
    PeopleLocalNode *itor;
    PeopleLocalNode *temp;
    int i;
    Person* aPerson;
    itor = front;

    if (itor->person_ptr->getID() == thePerson->getID())
    {
        popFront();
        return 1;
    }
    for (i = 1, itor = front; i < length; i++, itor = itor->next)
    {
        if (itor->next->person_ptr->getID() != thePerson->getID())
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
                aPerson = temp->person_ptr;
                cout << "The removed person (at back) has ID " << aPerson->getID() << "." << endl;
                delete temp;
                length--;
                return 1;
            }
            else
            {
                temp = itor->next;
                itor->next = temp->next;
                aPerson = temp->person_ptr;
                cout << "The removed person has ID " << aPerson->getID() << "." << endl;
                delete temp;
                length--;
                return 1;
            }
        }
    }
    fprintf(stderr, "The person to be deleted is not in the people local queue. \n");
    return 0;
}

// Print the ID of the last person in the queue.
bool PeopleLocalQueue::display(void)
{
    if (0 == length)
    {
        cout << "The queue is empty." << endl;
        return false;
    }
    cout << "The length of the people local queue is " << length << ". \n";

    PeopleLocalNode* temp;
    int i;
    for (i = 0, temp = front; i < length; i++, temp = temp->next)
    {
        cout << "The " << i << "th person has the ID " << temp->person_ptr->getID() << ". \n";
    }
    return true;
}
