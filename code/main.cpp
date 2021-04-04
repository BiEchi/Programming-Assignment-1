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
#include "./withdrawProcess.hpp"

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

// FibonacciPQ for 治疗队列
void forwardToCentralQueue(PeopleLocalQueue &people, FibonacciPQ &centralQueue)
{
   // readPeopleIntoCentralQueue();
   // withdraw?
   centralQueue.eatPeople(people);
   // delete &people;
   cout << "now there are " << centralQueue.returnLength() << " patients in the central queue" << endl;
   return;
}

void forwardToCentralQueueAtNoon(PeopleLocalQueue &people, FibonacciPQ &centralQueue, withdrawProcess &withdrawProg, blackList &blacklist, string &filename)
{
   cout << endl;
   cout << "------------------CentralQueue-------------------" << endl
        << endl;
   cout << "Half a day (w.l.o.g. 1 sec) is gone." << endl;
   forwardToCentralQueue(people, centralQueue);
   cout << "Successfully forwarded your information to the Central Queue." << endl;
   withdrawProg.askUserWithdraw_inFibonacciPQ(blacklist,centralQueue, filename);
   cout << endl
        << "-------------CentralQueueFinish--------------" << endl
        << endl;
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

// void loadTheTemporaryRegister(withdrawProcess &withdrawProg, string filename)
// {
//    withdrawProg.readFile(filename);
//    cout << "successfully open the file" << endl;
//    return;
// }

// void closeTheTemporaryRegister(withdrawProcess &withdrawProg, string filename)
// {
//    withdrawProg.closeFile(filename);
//    cout << "successfully close the file " << endl;
//    return;
// }

int main()
{
   // programe variable
   Notifications notification;
   TemporaryRegisterRecord temporaryRegisterRecordMethods;
   withdrawProcess withdrawProm;
   // data variable
   blackList blackListRegister = blackList();
   FibonacciPQ central_Queue = FibonacciPQ();
   string searchFile = "temporaryData.dat";
   string data; //buffer
   PeopleLocalQueue people;
   people.init();
   queueManger localHospitals; // appointment queues

   // process
   notification.notifyUserAboutIntroduction();

   while (1) MULTITHREAD_forwardToCentralQueueAtNoon(people, central_Queue);
   temporaryRegisterRecordMethods.buildTemporaryRegisterRecord(data, people);
   appendTemporaryToPermanent(data);

   forwardToCentralQueueAtNoon(people, central_Queue, withdrawProm,blackListRegister, searchFile);
   appointmentQueuesInit(&localHospitals);
   assignToLocalHospital(&localHospitals, &central_Queue);

   DeleteTemporaryRegisterRecord(data);
   return 0;
}
