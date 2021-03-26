#include "FibonacciPQ.h"
// 相应函数

// Add a new Person in the forest
// 用双链表实现根列表
void FibonacciPQ::newPerson(Person *newroot)
{
    // the Person root Person shouldn't have any sibling Person
    newroot->Parent = NULL;
    newroot->CutMark = false;
    // add the newroot Person in the root set
    Rootlist.push_back(newroot);
    // judge whether there is a requirement to change the min_ptr
    if (Minptr == NULL)
        Minptr = newroot;
    else if (newroot->Key < Minptr->Key)
        Minptr = newroot;
    Rootsize++;
    return;
}

// the function link is used to merge two Persons in one Person
// 返回成为根节点的ptr。
Person *FibonacciPQ::link(Person *a_ptr, Person *b_ptr)
{
    if (a_ptr->Key > b_ptr->Key) // root a_ptr should be the SonPerson of b_ptr
    {
        addSonPerson(a_ptr, b_ptr);
        // delete a_ptr from the root set
        Rootlist.remove(a_ptr);
        return b_ptr;
    }
    else
    {
        // 同理
        addSonPerson(b_ptr, a_ptr);
        Rootlist.remove(b_ptr);
        return a_ptr;
    }
    // error
    return nullptr;
}

// rebalance the forest after one min_ptr has been popped.
void FibonacciPQ::rebalance()
{
    auto vect_ptr = Rootlist.begin();
    // 防止list的remove操作将一开始的rootlist的迭代器给打爆，用while
    while (vect_ptr != Rootlist.end())
    {
        int pos = (*vect_ptr)->Degree;
        if (NULL == Degreebucket[pos])
        {
            Degreebucket[pos] = (*vect_ptr);
            vect_ptr++;
        }
        else if ((*vect_ptr) == Degreebucket[pos])
        {
            vect_ptr++;
        }
        else
        {
            Person *root = link(Degreebucket[pos], (*vect_ptr));
            Degreebucket[(root->Degree - 1)] = NULL;
            vect_ptr = Rootlist.begin();
        }
    }
    // 更新最小值
    for (auto i = Rootlist.begin(); i != Rootlist.end(); i++)
    {
        if (NULL == Minptr)
            Minptr = (*i);
        else if ((*i)->Key < Minptr->Key)
            Minptr = (*i);
    }
    Rootsize = Rootlist.size();
    return;
}

// add one Person as the SonPerson to another Person
// 假设加入的子节点是没有younger的且链表的最后一个子节点也是没有younger
void FibonacciPQ::addSonPerson(Person *sonPerson, Person *parentPerson)
{
    parentPerson->Son.push_back(sonPerson);
    sonPerson->Parent = parentPerson;
    parentPerson->Degree++;
    return;
}

// cut the SonPerson branch from the Person to be a new Person
void FibonacciPQ::cut(Person *sonPerson, Person *parentPerson)
{
    // cut the sonPerson from its parent Person.
    parentPerson->Son.remove(sonPerson);
    parentPerson->Degree--;
    return;
}

Person *FibonacciPQ::popMin()
{
    Person *return_obj = Minptr;
    Degreebucket[Minptr->Degree] = NULL;
    // 一个一个儿子变成新的
    Person *newroot = (*Minptr->Son.begin());
    while (newroot != NULL)
    {
        cut(newroot, Minptr);
        newPerson(newroot);
        newroot = (*Minptr->Son.begin());
    }
    Rootlist.remove(Minptr);
    Minptr = NULL;
    rebalance();
    PQ_length--;
    cout << "the popped person's id is " << return_obj->ID << endl;
    if (PQ_length > 0)
        cout << "now the top priority is " << Minptr->ID << endl;
    return return_obj;
}

bool FibonacciPQ::cascadingCut(Person *parent)
{
    if (parent == NULL)
    {
        return true;
    }
    else
    {
        if (parent->CutMark == false)
        {
            parent->CutMark = true;
        }
        else
        {
            Person *newroot = (*parent->Son.begin());
            while (newroot != NULL)
            {
                cut(newroot, parent);
                newPerson(newroot);
                newroot = (*parent->Son.begin());
            }
            cut(parent, parent->Parent);
            cascadingCut(parent->Parent);
        }
    }
    return true;
}

// operation list
bool FibonacciPQ::inSert(Person *handle)
{
    cout << "add new person " << handle->ID << endl;
    handle->arrangeStage = treatment;
    cout << "the person's current Stage is " << treatment;
    newPerson(handle);
    PQ_length++;
    return true;
}

// 更改handle的key值，返回更改的句柄
Person *FibonacciPQ::decreaseKey(Person *changeStatusPerson, int profession_status, int riskStatus_status)
{
    // 造个提升进行假想比较
    Person *imaginary_handle = stand_in(changeStatusPerson);
    changeStatusPerson->profession = profession_status;
    changeStatusPerson->riskStatus = riskStatus_status;
    if ((changeStatusPerson->Parent != NULL) && (Is_smaller(changeStatusPerson, changeStatusPerson->Parent)))
    {
        cut(changeStatusPerson, changeStatusPerson->Parent);
        newPerson(changeStatusPerson);
        cascadingCut(changeStatusPerson->Parent);
    }
    if (Is_smaller(changeStatusPerson, Minptr))
    {
        Minptr = changeStatusPerson;
    }
    delete imaginary_handle;
    cout << "successfully decrease the priority of the patient " << changeStatusPerson->name << endl;
    delete imaginary_handle;
    return changeStatusPerson;
}

// change_status
Person *FibonacciPQ::changeStatus(Person* changingPatient, int profession_status, int riskStatus_status)
{
    return nullptr;
}

Person *FibonacciPQ::remove(Person *handle)
{
    decreaseKey(handle, Minptr->Key - 1);
    popMin();
    return handle;
}

bool FibonacciPQ::isEmpty()
{
    if (PQ_length == 0)
        return true;
    else
        return false;
}

int FibonacciPQ::returnLength()
{
    return PQ_length;
}

bool FibonacciPQ::eatPeople(PeopleLocalQueue *local_queue)
{
    int length = local_queue->getLength();
    while (length > 0)
    {
        Person *pop_person = local_queue->popFront();
        cout << "there is " << length << "people needed to be eaten" << endl;
        cout << "the person's id is " << pop_person->ID << endl;
        inSert(pop_person);
        length--;
    }
    return true;
}

Person *FibonacciPQ::stand_in(Person *copy_person_ptr)
{
    Person *stand = new Person;
    stand->profession = copy_person_ptr->getProfession();
    stand->profession = copy_person_ptr->getRiskStatus();
    return stand;
}