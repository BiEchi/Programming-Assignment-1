//
//  MULTITHREAD.hpp
//  code
//
//  Created by Jack's Macbook Pro on 2021/4/4.
//

#ifndef MULTITHREAD_hpp
#define MULTITHREAD_hpp

#include <stdio.h>
#include <ctime>

// FibonacciPQ for 治疗队列
void forwardToCentralQueue(PeopleLocalQueue &people, FibonacciPQ &centralQueue)
{
    cout << endl;
    cout << "-------------CentralQueueStart---------------" << endl;
    cout << "Forwarding temporary record to central queue because half a day is gone." << endl
         << endl;

    // readPeopleIntoCentralQueue();
    // withdraw?
    centralQueue.eatPeople(people);
    // delete &people;

    cout << "now there is " << centralQueue.returnLength() << " people in the central queue" << endl;
    cout << "Successfully forwarded your information to the Central Queue." << endl;
    cout << endl
         << "-------------CentralQueueFinish--------------" << endl
         << endl;

    return;
}

/// set up the timer
/// @param id the id number of the timer
/// @param msec the number of milli-seconds you want to lapse in one epoch
void settimer(unsigned int id, int msec, PeopleLocalQueue &people, FibonacciPQ &centralQueue)
{
    if (msec < 0) // 判断时间段是否满足 >=0
    {
        return;
    }
    clock_t start, finish;
    start = clock();      // 计时函数
    double totaltime = 0; // 定义时间变量
    while (1)
    {
        finish = clock();
        totaltime = (double)(finish - start);
        if (totaltime > msec)
        {
            forwardToCentralQueue(people, centralQueue);
            break;
        }
    }

    return;
}

void MULTITHREAD_forwardToCentralQueueAtNoon(PeopleLocalQueue &people, FibonacciPQ &centralQueue)
{
    settimer(1, 2000000, people, centralQueue);
}

#endif /* MULTITHREAD_hpp */
