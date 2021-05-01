#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdio>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <thread>
#include <mutex>

#include "./Person.hpp"
#include "./PeopleLocalQueue.hpp"
#include "./FibonacciPQ.hpp"
#include "./assignment_queue.hpp"
#include "./blackList.hpp"
#include "./MULTITHREAD.hpp"
#include "./withdrawProcess.hpp"
#include "./Tools.hpp"
#include "./CSVInputManipulations.hpp"

using namespace std;

// appointment queues functions
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

// Assumption: The appointent queues have already been initialized.
int assignToLocalHospital(queueManger *localHospital, FibonacciPQ *centralQueue)
{
    localHospital->reassign(centralQueue);
    localHospital->displayAll();
    return 1;
}

void getReportingWeeklyType(int &personType, int &sortType)
{
    cout << "Person Type = 0(treated), 1(in queue), 2(with assignment)" << endl;
    cin >> personType;

    cout << "Sort Type = 0(name), 1(profession), 2(age)" << endl;
    cin >> sortType;

    return;
}

// global variables
time_t startTime = time(NULL);
blackList blackListRegister = blackList();
FibonacciPQ central_Queue = FibonacciPQ();
PeopleLocalQueue people;
withdrawProcess withdrawProm;

int main()
{
    // data variable
    string searchFile = "temporaryData.dat";
    people.init();
    queueManger localHospitals; // appointment queues

    // process
    cout << "Please Enter the person type and sort type you want." << endl << endl;
    int personType, sortType;
    getReportingWeeklyType(personType, sortType);

    cout << "This is the presentation code for Computing Assignment 2, with authors Hao BAI, Liyang QIAN, Jiahao WEI and Yihong JIN." << endl;
    
    thread threadForCentralQueue(ref(forwardToCentralQueueAtNoonTwiceADay), ref(people), ref(central_Queue));

    thread threadForReportingWeekly(reportingWeeklyWrapper, 2, 70000000, personType, sortType, localHospitals.treated_list, central_Queue.returnStorePeople(), localHospitals.assignment_list);

    thread threadForReportingMonthly(reportingMonthlyWrapper, 3, 300000000, localHospitals.treated_list, central_Queue.returnStorePeople(), localHospitals.assignment_list, blackListRegister);
    
    readTheInputCSVIntoPeople(people);
    withdrawProm.withdrawAdvanced(blackListRegister,people,central_Queue,localHospitals,searchFile);
    appointmentQueuesInit(&localHospitals);
    assignToLocalHospital(&localHospitals, &central_Queue);

    threadForCentralQueue.detach();
    threadForReportingWeekly.detach();
    threadForReportingMonthly.detach();

    return 0;
}
