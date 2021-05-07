#include "./Person.hpp"
#include "./PeopleLocalQueue.hpp"
#include "./FibonacciPQ.hpp"
#include "./assignment_queue.hpp"
#include "./blackList.hpp"
using namespace std;

#include <fstream>
#include <iostream>
#include <stdio.h>
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

int displayQueue(PeopleLocalQueue* theQueue, const char* theInfo)
{
    cout << endl;
    cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
    cout << theInfo << endl;
    theQueue->display();
    cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl << endl;
    return 0;
}


int main()
{
    tm aTime;
    tm* baseTime;
    blackList blackListRegister = blackList();
    FibonacciPQ central_Queue = FibonacciPQ();
    PeopleLocalQueue people;
    queueManger localHospitals; // appointment queues
    localHospitals.initTime();
    cout << "Start time is:       " << asctime(localtime(&(localHospitals.startTime))) << "\n";
    // Creat people
    int len = 10;
    Person manyPeople[len];
    for (int i = 0; i < len; i++)
    {
        manyPeople[i].setID(to_string(i));
        manyPeople[i].setProfession(to_string(i%8));
        manyPeople[i].setContactDetails(to_string(rand()%8));
    }
    for (int i = 0; i < len; i++)
    {
        manyPeople[i].display();
    }

    for (int i = 0; i < len; i++)
    {
        people.pushBack(&manyPeople[i]);
    }

    // Test isIn function of local queue.
    // for (int i = -1; i < 20; i ++)
    // {
    //     cout << people.isIn(to_string(i)) << endl;
    // }


    // displayQueue(&people, "Local queue before withdraw. ");
    // displayQueue(&people, "Local queue after withdraw. ");
    // displayQueue(&people, "Local queue after withdraw and insetion. ");

    central_Queue.eatPeople(people);
    cout << "now there is " << central_Queue.returnLength() << " people in the central queue" << endl;
    appointmentQueuesInit(&localHospitals);
    assignToLocalHospital(&localHospitals, &central_Queue);
    // Test isIn function of assignment queue manger.
    // for (int i = -1; i < 20; i++)
    // {
    //     cout << localHospitals.isIn(to_string(i)) << endl;
    // }

    // manyPeople[5].assignLocation(0);
    // localHospitals.doWithdraw(&manyPeople[5]);

    return 0;
}