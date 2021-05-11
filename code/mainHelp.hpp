#ifndef MAINHELP_hpp
#define MAINHELP_hpp
#include <iostream>
#include "./Person.hpp"
#include "./PeopleLocalQueue.hpp"
#include "./FibonacciPQ.hpp"
#include "./assignment_queue.hpp"
#include "./blackList.hpp"
#include "./Reporting.hpp"
#include "./withdrawProcess.hpp"
#include "./TimePredef.hpp"
#include "./CSVInputManipulations.hpp"
using namespace std;

void getReportingWeeklyType(int &personType, int &sortType)
{
    cout << "Person Type = 0(treated), 2(with assignment)" << endl; // Delete choose 1(in queue)
    cin >> personType;

    cout << "Sort Type = 0(name), 1(profession), 2(age)" << endl;
    cin >> sortType;

    return;
}

void forwardToCentralQueue(PeopleLocalQueue &people, FibonacciPQ &centralQueue) {
  centralQueue.eatPeople(people);
  return;
}

int appointmentQueuesInit(queueManger *localHospital)
{
    // initialize
    localHospital->init();
    for (int i = 0; i < 8; i++)
    {
        localHospital->addHospital(i);
    }
    return 1;
}

int assignToLocalHospital(queueManger *localHospital, FibonacciPQ *centralQueue)
{
    localHospital->reassign(centralQueue);
    localHospital->displayAll();
    return 1;
}

#endif /* MAINHELP_hpp */
