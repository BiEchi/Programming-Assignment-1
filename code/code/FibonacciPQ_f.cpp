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
    PQlength--;
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
    newPerson(handle);
    PQlength++;
    return true;
}

// 更改handle的key值，返回更改的句柄
Person *FibonacciPQ::decreaseKey(Person *handle, int k)
{
    if (handle->Key < k)
    {
        cout << "the Key shouldn't be bigger or equal\n";
        return NULL;
    }
    else
    {
        handle->Key = k;
        if ((handle->Parent != NULL) && (k < handle->Parent->Key))
        {
            cut(handle, handle->Parent);
            newPerson(handle);
            cascadingCut(handle->Parent);
        }
        if (k < Minptr->Key)
        {
            Minptr = handle;
        }
        return handle;
    }
}

Person *FibonacciPQ::remove(Person *handle)
{
    decreaseKey(handle, Minptr->Key - 1);
    popMin();
    return handle;
}

bool FibonacciPQ::isEmpty()
{
    if (PQlength == 0)
        return true;
    else
        return false;
}

int FibonacciPQ::returnLength()
{
    return PQlength;
}