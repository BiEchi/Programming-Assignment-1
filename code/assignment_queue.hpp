#ifndef assignment_queue_hpp
#define assignment_queue_hpp

#include "FibonacciPQ.hpp"
#include "Person.hpp"
#include <stdint.h>
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

public:
    int init(int hc, int wh, int thePlace);
    void clear(void);
    int isFull(void) { return (occupied == length ? 1 : 0); }
    int addPerson(Person *const thePerson);
    int deletePerson(Person *const thePerons);
    void assignTimeAndLocation(void);
    int getTheHospital(void) {return theHospital;}
    int display(void);
};

class queueManger
{
private:
    assignmentQueue **locations;
    int capacity;
    int length;

    int extendLocations(int hospital);

public:
    int init(int num = 8);
    int addHospital(int hospital, int hc = 1, int wh = 8);
    // Handle assignment
    int reassign(FibonacciPQ *PQ);
    // Handle withdraw
    int doWithdraw(Person *thePerson);
    int displayAll(void);
};

#endif
