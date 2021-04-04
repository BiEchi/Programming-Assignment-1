#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdio>
#include <sstream>
#include <cstdlib>
#include <cstring>

#include "./Person.hpp"
#include "./TemporaryRegisterRecord.hpp"
#include "./Notifications.hpp"
#include "./PeopleLocalQueue.hpp"
#include "./FibonacciPQ.hpp"
#include "./assignment_queue.hpp"
#include "./blackList.hpp"
#include "./MULTITHREAD.hpp"

using namespace std;

void appendPermanentRegisterRecord(string data)
{
   system(" cat 'temporaryData.dat' >> 'permanentData.dat' ");
   return;
}

void appendTemporaryToPermanent(string data)
{
   cout << endl << endl;
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

int main()
{
   blackList blackListRegister = blackList();
   FibonacciPQ central_Queue = FibonacciPQ();
   Notifications notification;
   TemporaryRegisterRecord temporaryRegisterRecordMethods;
   notification.notifyUserAboutIntroduction();
   string data; // buffer
   PeopleLocalQueue people;
   queueManger localHospitals; // appointment queues
   people.init();

   while (1) MULTITHREAD_forwardToCentralQueueAtNoon(people, central_Queue);
   temporaryRegisterRecordMethods.buildTemporaryRegisterRecord(data, people);
   appendTemporaryToPermanent(data);
   DeleteTemporaryRegisterRecord(data);
   // cout << "Show if the central queue is empty before assignment (1 for true): " << central_Queue.isEmpty() << "\n";
   appointmentQueuesInit(&localHospitals);
   assignToLocalHospital(&localHospitals, &central_Queue);

   return 0;
}
