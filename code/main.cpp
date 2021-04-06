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
   notification.notifyUserAboutIntroduction();
   thread threadForCentralQueue(ref(forwardToCentralQueueAtNoonTwiceADay), ref(people), ref(central_Queue));

   // notification.
   // thread threadForReportingWeekly(ref(reportingWeeklyWrapper), 2, 70000000, personType, sortType, treatedPeople, central_Queue, assignmentQueue);
   // thread threadForReportingMonthly(ref(reportingMonthlyWrapper), treatedPeople, central_Queue, assignmentQueue, blackList);

   temporaryRegisterRecordMethods.buildTemporaryRegisterRecord(data, people);
   appendTemporaryToPermanent(data);

   appointmentQueuesInit(&localHospitals);
   assignToLocalHospital(&localHospitals, &central_Queue);

   DeleteTemporaryRegisterRecord(data);

   threadForCentralQueue.detach();

   return 0;
}
