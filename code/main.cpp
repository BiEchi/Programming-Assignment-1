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
   cout << endl << endl;
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
void forwardToCentralQueue(string data, PeopleLocalQueue people, FibonacciPQ centralQueue)
{
   // readPeopleIntoCentralQueue();
   // withdraw?
   centralQueue.eatPeople(&people);
   delete &people;
   cout << "finish load people into central queue "<< endl;
   return;
}

// appointmentQueue()
void forwardToCentralQueueAtNoon(string data, PeopleLocalQueue people, FibonacciPQ centralQueue)
{
   cout << "Half a day (w.l.o.g. 1 sec) is gone." << endl;
   forwardToCentralQueue(data, people, centralQueue);
   cout << "Successfully forwarded your information to the Central Queue." << endl;
}

int main()
{
   FibonacciPQ central_Queue = FibonacciPQ();
   Notifications notification;
   TemporaryRegisterRecord temporaryRegisterRecordMethods;
   notification.notifyUserAboutIntroduction();
   string data; // buffer
   PeopleLocalQueue people;
   people.init();

   temporaryRegisterRecordMethods.buildTemporaryRegisterRecord(data, people);
   appendTemporaryToPermanent(data);
   localizeAndDeleteTemporaryRegisterRecord(data);
   forwardToCentralQueueAtNoon(data, people, central_Queue);
   // appointmentQueue(assignqueue, &FIbonaqi)

   return 0;
}
