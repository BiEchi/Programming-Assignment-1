#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdio>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <thread>
#include <mutex>
#include <condition_variable>

#include "./Person.hpp"
#include "./TemporaryRegisterRecord.hpp"
#include "./Notifications.hpp"
#include "./PeopleLocalQueue.hpp"
#include "./FibonacciPQ.hpp"
#include "./assignment_queue.hpp"
#include "./blackList.hpp"
#include "./MULTITHREAD.hpp"
#include "./withdrawProcess.hpp"
#include "./Tools.hpp"

using namespace std;

void appendPermanentRegisterRecord(string data)
{
   system(" cat 'temporaryData.dat' >> 'permanentData.dat' ");
   return;
}

void appendTemporaryToPermanent(string data)
{
   cout << endl
        << endl;
   appendPermanentRegisterRecord(data);
   cout << "Successfully put your information into the Permanent Database." << endl;
   return;
}

void DeleteTemporaryRegisterRecord(string data)
{
   IOManipulations vectorIOManipulation;
   vectorIOManipulation.dumpTemporaryRegisterRecord(data);
   cout << "Successfully dumped your information in the Temporary Database." << endl;
}

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

time_t startTime = time(NULL);
blackList blackListRegister = blackList();
FibonacciPQ central_Queue = FibonacciPQ();
PeopleLocalQueue people;
withdrawProcess withdrawProm;

int main()
{
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
   withdrawProm.withdrawAdvanced(blackListRegister,people,central_Queue,localHospitals,searchFile);
   appointmentQueuesInit(&localHospitals);
   assignToLocalHospital(&localHospitals, &central_Queue);

   DeleteTemporaryRegisterRecord(data);

   threadForCentralQueue.detach();
   threadForReportingWeekly.detach();
   threadForReportingMonthly.detach();

   return 0;
}
