#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdio>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <thread>

// To run F5
// #include "./Person.cpp"
// #include "./PeopleLocalQueue.cpp"
// #include "./FibonacciPQ.cpp"
// #include "./assignment_queue.cpp"
// #include "./blackList.cpp"
// #include "./withdrawProcess.cpp" 
// #include "./Database.cpp"
// #include "./BPlusTree.cpp"
// #include "./BTree.cpp"
// #include "./HashMap.cpp"
// #include "./block.cpp"

#include "./Person.hpp"
#include "./PeopleLocalQueue.hpp"
#include "./FibonacciPQ.hpp"
#include "./assignment_queue.hpp"
#include "./blackList.hpp"
#include "./withdrawProcess.hpp"
#include "./Reporting.hpp"
#include "./TimePredef.hpp"
#include "./CSVInputManipulations.hpp"
#include "./mainHelp.hpp"
#include "./Database.hpp"
#include "./DatabaseManipulation.hpp"

using namespace std;

// global variables
time_t startTime = time(NULL);
block blockList;
BPlusTree bPlusTree(&blockList);
BTree bTree;
HashMap hashMap;
hospitalDatabase database(bPlusTree,bTree,hashMap);
blackList blackListRegister = blackList();
FibonacciPQ central_Queue = FibonacciPQ();
PeopleLocalQueue people;
withdrawProcess withdrawProm;

int main()
{
    people.init();
    queueManger localHospitals; // appointment queues

    sleep(1);
    cout << "This is the presentation code for Computing Assignment 2, with authors Hao BAI, Liyang QIAN, Jiahao WEI and Yihong JIN." << endl;
    sleep(1);
    system("echo '\033[41m\033[37m\033[1m\033[4m ### The presentation starts in 1 second... ### \33[0m' ");
    sleep(1);

    system("echo '\033[41m\033[37m\033[1m\033[4mReading the input CSV file into People Local Queue...\33[0m' ");
    sleep(1);
    
    // thread thread_readCSVEmergency();
    // for first one
    
    readTheInputCSVIntoPeople(people, "RegistrationEmergency1.csv");
    sleep(1);
    
    system("echo '\033[41m\033[37m\033[1m\033[4m ### Database operations starting... ### \33[0m' ");
    cout << people.getLength() << " people in list " <<endl;
    readPeopleIntoDatabase(people, database);
    
    withdrawProm.LoadingDemoData(people);
    withdrawProm.PeopleWithdrawDemo(blackListRegister, people);
    sleep(3);
    
    cout << "Forwarding to central queue." << endl;
    forwardToCentralQueue(people, central_Queue);
    sleep(1);

    appointmentQueuesInit(&localHospitals);
    system("echo '\033[41m\033[37m\033[1m\033[4mAssigning to the local hospitals...\33[0m' ");
    sleep(1);
    
    assignToLocalHospital(&localHospitals, &central_Queue);
    sleep(1);
    system("echo '\33[32mSuccessfully assigned patients to the local hospitals.\33[0m' ");
    sleep(1);
    
    system("echo '\33[32mGenerating monthly report to report.txt ...\33[0m' ");
    Reporting_monthly(localHospitals.treated_list, central_Queue.returnStorePeople(), localHospitals.assignment_list, blackListRegister);
    sleep(1);
    
    system("echo '\033[32m\033[37m\033[1m\033[4mThe programme ends with exit flag EXIT_SUCCESS\33[0m' ");
    sleep(1);

    return EXIT_SUCCESS;
}
