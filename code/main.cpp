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
#include "./TimePredef.hpp"
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

    sleep(1);
    cout << "This is the presentation code for Computing Assignment 2, with authors Hao BAI, Liyang QIAN, Jiahao WEI and Yihong JIN." << endl;
    sleep(1);
    system("echo '\033[41m\033[37m\033[1m\033[4m ### The presentation starts in 3 seconds... ### \33[0m' ");
    sleep(3);
    
    cout << "Thread 1 begins." << endl;
    thread threadForCentralQueue(ref(forwardToCentralQueueAtNoonTwiceADay), ref(people), ref(central_Queue));
    sleep(1);

    cout << "Thread 2 begins." << endl;
    thread threadForReportingWeekly(reportingWeeklyWrapper, 2, 70000000, personType, sortType, localHospitals.treated_list, central_Queue.returnStorePeople(), localHospitals.assignment_list);
    sleep(1);

    cout << "Thread 3 begins." << endl;
    thread threadForReportingMonthly(reportingMonthlyWrapper, 3, 300000000, localHospitals.treated_list, central_Queue.returnStorePeople(), localHospitals.assignment_list, blackListRegister);
    sleep(1);
    
    system("echo '\033[41m\033[37m\033[1m\033[4mReading the input CSV file into People Local Queue...\33[0m' ");
    sleep(2);
    readTheInputCSVIntoPeople(people);
    sleep(3);
    
    system("echo '\033[41m\033[37m\033[1m\033[4mChoose whether you want to withdraw...\33[0m' ");
    withdrawProm.withdrawAdvanced(blackListRegister,people,central_Queue,localHospitals,searchFile);
    sleep(1);
    
    appointmentQueuesInit(&localHospitals);
    system("echo '\033[41m\033[37m\033[1m\033[4mAssigning to the local hospitals...\33[0m' ");
    sleep(1);
    assignToLocalHospital(&localHospitals, &central_Queue);
    sleep(3);
    
    cout << "Detaching thread 1..." << endl;
    threadForCentralQueue.detach();
    sleep(1);
    cout << "Detaching thread 2..." << endl;
    threadForReportingWeekly.detach();
    sleep(1);
    cout << "Detaching thread 3..." << endl;
    threadForReportingMonthly.detach();
    sleep(1);
    
    return 0;
}
