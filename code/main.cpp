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
using namespace std;

#include <fstream>
#include <iostream>
using namespace std;

void appendPermanentRegisterRecord(string data)
{
   system(" cat 'temporaryData.dat' >> 'permanentData.dat' ");
   return;
}

// take 1 minute as half a day
bool halfDayIsGone(int realTimeBegin, int realTimeEnd)
{
   /* // TODO
   if (realTimeBegin - realTimeEnd) return true;
   else return false;
   */
   return true;
}

void appendTemporaryToPermanent(string data)
{
   cout << endl
        << endl;
   appendPermanentRegisterRecord(data);
   cout << "Successfully put your information into the Permanent Database." << endl;
   return;
}

void localizeAndDeleteTemporaryRegisterRecord(string data)
{
   IOManipulations vectorIOManipulation;
   vectorIOManipulation.buildTheVectorOfPersonInformationWithIO(data);

   cout << "Successfully built your information into Data Structure inside C++." << endl;
   vectorIOManipulation.dumpTemporaryRegisterRecord(data);
   cout << "Successfully dumped your information in the Temporary Database." << endl;
}

// FibonacciPQ for 治疗队列
void forwardToCentralQueue(PeopleLocalQueue &people, FibonacciPQ &centralQueue)
{
   // readPeopleIntoCentralQueue();
   // withdraw?
   centralQueue.eatPeople(people);
   // delete &people;
   cout << "now there is " << centralQueue.returnLength() << " people in the central queue" << endl;
   return;
}

void forwardToCentralQueueAtNoon(PeopleLocalQueue &people, FibonacciPQ &centralQueue)
{
   cout << endl;
   cout << "------------------CentralQueue-------------------" << endl
        << endl;
   cout << "Half a day (w.l.o.g. 1 sec) is gone." << endl;
   forwardToCentralQueue(people, centralQueue);
   cout << "Successfully forwarded your information to the Central Queue." << endl;
   cout << endl
        << "-------------CentralQueueFinish--------------" << endl
        << endl;
}

// appointment queues functions
int appointmentQueuesInit(queueManger *localHospital)
{
   int32_t hourCapacity = 1;
   int32_t workingHour = 2;

   // initialize
   localHospital->init(8); // The number ranges from 1 to 7 (need index 7).
   for (int i = 0; i < 8; i++)
   {
      localHospital->addHospital(i, hourCapacity, workingHour);
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

   temporaryRegisterRecordMethods.buildTemporaryRegisterRecord(data, people);
   appendTemporaryToPermanent(data);
   localizeAndDeleteTemporaryRegisterRecord(data);
   forwardToCentralQueueAtNoon(people, central_Queue);
   // cout << "The forward To Central Queue At Noon function has been run. \n";
   // cout << "Show if the central queue is empty before assignment (1 for true): " << central_Queue.isEmpty() << "\n";
   appointmentQueuesInit(&localHospitals);
   assignToLocalHospital(&localHospitals, &central_Queue);

   return 0;
}