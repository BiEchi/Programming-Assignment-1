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
#include "./Reporting.hpp"
#include "./withdrawProcess.hpp"
#include "./TimePredef.hpp"
#include "./CSVInputManipulations.hpp"
#include "mainHelp.hpp"

using namespace std;

// global variables
time_t startTime = time(NULL);
blackList blackListRegister = blackList();
FibonacciPQ central_Queue = FibonacciPQ();
PeopleLocalQueue people;
withdrawProcess withdrawProm;

int main()
{
<<<<<<< HEAD
   // programme variable
   Notifications notification;
   TemporaryRegisterRecord temporaryRegisterRecordMethods;
   // data variable
   string searchFile = "temporaryData.dat";
   string data; //buffer
   people.init();
   queueManger localHospitals; // appointment queues

   // process
   notification.notifyUserAboutReportingWeeklyType();
   int personType, sortType;
   getReportingWeeklyType(personType, sortType);

   notification.notifyUserAboutIntroduction();
   thread threadForCentralQueue(ref(forwardToCentralQueueAtNoonTwiceADay), ref(people), ref(central_Queue));

   thread threadForReportingWeekly(reportingWeeklyWrapper, 2, 70000000, personType, sortType, localHospitals.treated_list, central_Queue.returnStorePeople(), localHospitals.assignment_list);

   thread threadForReportingMonthly(reportingMonthlyWrapper, 3, 300000000, localHospitals.treated_list, central_Queue.returnStorePeople(), localHospitals.assignment_list, blackListRegister);

   temporaryRegisterRecordMethods.buildTemporaryRegisterRecord(data, people);
   appendTemporaryToPermanent(data);
   // withdrawProm.withdrawAdvanced(blackListRegister,people,central_Queue,localHospitals,searchFile);
   appointmentQueuesInit(&localHospitals);
   assignToLocalHospital(&localHospitals, &central_Queue);

   DeleteTemporaryRegisterRecord(data);

   threadForCentralQueue.detach();
   threadForReportingWeekly.detach();
   threadForReportingMonthly.detach();

   return 0;
=======
    // data variable
    // string searchFile = "../database/People.csv";
    people.init();
    queueManger localHospitals; // appointment queues

    // process
    cout << "Please Enter the person type and sort type you want." << endl
         << endl;
    int personType, sortType;
    getReportingWeeklyType(personType, sortType);

    sleep(1);
    cout << "This is the presentation code for Computing Assignment 2, with authors Hao BAI, Liyang QIAN, Jiahao WEI and Yihong JIN." << endl;
    sleep(1);
    system("echo '\033[41m\033[37m\033[1m\033[4m ### The presentation starts in 1 second... ### \33[0m' ");
    sleep(1);

    system("echo '\033[41m\033[37m\033[1m\033[4mReading the input CSV file into People Local Queue...\33[0m' ");
    sleep(1);
    readTheInputCSVIntoPeople(people);
    sleep(1);
    
    cout << "Forwarding to central queue." << endl;
    forwardToCentralQueue(people, central_Queue);
    sleep(1);

    // system("echo '\033[41m\033[37m\033[1m\033[4mChoose whether you want to withdraw...\33[0m' ");
    // withdrawProm.withdrawAdvanced(blackListRegister, people, central_Queue, localHospitals, searchFile);
    // sleep(1);

    appointmentQueuesInit(&localHospitals);
    system("echo '\033[41m\033[37m\033[1m\033[4mAssigning to the local hospitals...\33[0m' ");
    sleep(1);
    assignToLocalHospital(&localHospitals, &central_Queue);
    sleep(1);
    system("echo '\33[32mSuccessfully assigned patients to the local hospitals.\33[0m' ");
    sleep(1);
    
    system("echo '\33[32mReporting Weekly...\33[0m' ");
    Reporting_weekly(personType, sortType, localHospitals.treated_list, central_Queue.returnStorePeople(), localHospitals.assignment_list);
    sleep(1);
    
    system("echo '\33[32mReporting Monthly...\33[0m' ");
    Reporting_monthly(localHospitals.treated_list, central_Queue.returnStorePeople(), localHospitals.assignment_list, blackListRegister);
    sleep(1);
    
    system("echo '\033[32m\033[37m\033[1m\033[4mThe programme ends with exit flag EXIT_SUCCESS\33[0m' ");
    sleep(1);

    return EXIT_SUCCESS;
>>>>>>> main
}
