#ifndef assignment_queue_hpp
#define assignment_queue_hpp

#include "FibonacciPQ.hpp"
#include "Person.hpp"
#include <stdint.h>
#include <stdio.h>
#include <time.h>


class assignmentQueue
{
    friend class queueManger;

private:
    int theHospital;
    Person **timeSlot;
    int32_t hourCapacity;
    int32_t workingHour;
    int32_t length;
    int32_t occupied;

private:
    void clear(void);
    int init(int hc, int wh, int thePlace);
    int isFull(void) { return (occupied == length ? 1 : 0); }
    int addPerson(Person *const thePerson);
    int deletePerson(Person* thePerons);
    void assignTimeAndLocation(time_t startTime);
    int getTheHospital(void) { return theHospital; }
    bool isIn(string ID);
    int display(void);
};

class queueManger
{
private:
    assignmentQueue **locations;
    int capacity;
    int length;

    int extendLocations(int hospital);

private:
    
public:
    time_t startTime;
    int init(int num = 8);
    void initTime() {startTime = time(NULL);}
    int addHospital(int hospital, int hc = 1, int wh = 8);
    // Handle assignment
    int reassign(FibonacciPQ *PQ);
    // Handle withdraw
    int doWithdraw(Person *thePerson);
    bool isIn(string ID);
    int displayAll(void);
};

#endif