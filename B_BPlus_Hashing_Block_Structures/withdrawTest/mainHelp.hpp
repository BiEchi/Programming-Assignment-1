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

int assignToLocalHospital(queueManger *localHospital, FibonacciPQ *centralQueue);
void getReportingWeeklyType(int &personType, int &sortType);
void forwardToCentralQueue(PeopleLocalQueue &people, FibonacciPQ &centralQueue);
int appointmentQueuesInit(queueManger *localHospital);


#endif /* MAINHELP_hpp */
