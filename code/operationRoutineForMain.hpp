//
//  operationRoutineForMain.hpp
//  code
//
//  Created by Jack's Macbook Pro on 2021/5/14.
//

#ifndef operationRoutineForMain_hpp
#define operationRoutineForMain_hpp

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>

#include "./CSVInputManipulations.hpp"
#include "./Database.hpp"
#include "./DatabaseManipulation.hpp"
#include "./FibonacciPQ.hpp"
#include "./PeopleLocalQueue.hpp"
#include "./Person.hpp"
#include "./Reporting.hpp"
#include "./TimePredef.hpp"
#include "./assignment_queue.hpp"
#include "./blackList.hpp"
#include "./mainHelp.hpp"
#include "./query.hpp"
#include "./withdrawProcess.hpp"

void operationRoutine(time_t startTime, block& blockList, hospitalDatabase& database, blackList& blackListRegister, FibonacciPQ& central_Queue, PeopleLocalQueue& people, withdrawProcess& withdrawProm, queueManger& localHospitals, string treatmentType)
{
    readTheInputCSVIntoPeople(people, treatmentType);
    sleep(1);

    /* Database Operations */

    system(
           "echo '\033[41m\033[37m\033[1m\033[4m ### Database operations "
           "starting... ### \33[0m' ");
    cout << "There are " << people.getLength() << " people in list " << endl;
    readPeopleIntoDatabase(people, database);
    sleep(2);

    withdrawProm.LoadingDemoData(people);
    withdrawProm.PeopleWithdrawDemo(blackListRegister, people);

    cout << "Forwarding to central queue." << endl;
    sleep(1);
    forwardToCentralQueue(people, central_Queue);
    sleep(1);

    appointmentQueuesInit(&localHospitals);
    system(
           "echo '\033[41m\033[37m\033[1m\033[4mAssigning to the local "
           "hospitals...\33[0m' ");
    sleep(1);

    assignToLocalHospital(&localHospitals, &central_Queue);
    sleep(1);
    system(
           "echo '\33[32mSuccessfully assigned patients to the local "
           "hospitals.\33[0m' ");
    sleep(1);
}





#endif /* operationRoutineForMain_hpp */
