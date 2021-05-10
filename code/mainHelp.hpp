#ifndef MAINHELP_hpp
#define MAINHELP_hpp

void getReportingWeeklyType(int &personType, int &sortType)
{
    cout << "Person Type = 0(treated), 1(in queue), 2(with assignment)" << endl;
    cin >> personType;

    cout << "Sort Type = 0(name), 1(profession), 2(age)" << endl;
    cin >> sortType;

    return;
}

void forwardToCentralQueue(PeopleLocalQueue &people, FibonacciPQ &centralQueue) {
  centralQueue.eatPeople(people);
  return;
}

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

int assignToLocalHospital(queueManger *localHospital, FibonacciPQ *centralQueue)
{
    localHospital->reassign(centralQueue);
    localHospital->displayAll();
    return 1;
}

#endif /* MAINHELP_hpp */
