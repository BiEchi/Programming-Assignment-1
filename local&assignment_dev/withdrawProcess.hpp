#ifndef WITHDRAWPROCESS_hpp
#define WITHDRAWPROCESS_hpp

#include "FibonacciPQ.hpp"
#include "assignment_queue.hpp"
#include "Person.hpp"
#include "blackList.hpp"
#include "PeopleLocalQueue.hpp"

class withdrawProcess
{
public:
    void askUserWhetherWithdraw(blackList &blackList, FibonacciPQ &centralList, PeopleLocalQueue& people, queueManger &hospitals);

private:
    string askForID();
    Person *findAndReturnPersonPointer(string ID);
    bool decideAndOperateWithdraw(Person *person, blackList &blackList, FibonacciPQ &centralList, PeopleLocalQueue& people, queueManger &hospitals);
};

#endif