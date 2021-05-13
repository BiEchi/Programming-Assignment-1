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
    do
    {
        cout << "Please choose a valid Person Type ;)" << endl;
        cout << "Person Type: 0 (treated), 1 (with assignment)" << endl; // Choice (in queue) has been deleted. 
        cin >> personType;
    } while (personType > 1 || personType < 0);

    do
    {
        cout << "Please choose a valid Sort Type ;)" << endl;
        cout << "Sort Type: 0 (name), 1 (profession), 2 (age)" << endl;
        cin >> sortType;
    } while (sortType > 2 || sortType < 0);

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
    localHospital->doTreat();
    return 1;
}

#endif /* MAINHELP_hpp */
