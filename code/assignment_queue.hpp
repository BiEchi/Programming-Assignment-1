#ifndef assignment_queue_hpp
#define assignment_queue_hpp

#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include "FibonacciPQ.hpp"
#include "Person.hpp"

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
    int init(int hc, int wh, int thePlace);
    void clear(vector<Person> *treated_list);
    int isFull(void) { return (occupied == length ? 1 : 0); }
    int addPerson(Person *const thePerson);
    int deletePerson(Person *thePerons);
    void assignTimeAndLocation(void);
    int getTheHospital(void) { return theHospital; }
    Person *isIn(string ID);
    int display(void);
};

class queueManger
{
private:
    assignmentQueue **locations;
    int capacity;
    int length;

private:
    int extendLocations(int hospital);

public:
    vector<Person> treated_list;
    vector<Person> assignment_list;
    int init(int num = 8);
    int addHospital(int hospital, int hc = 10, int wh = 8);
    // Handle assignment
    int reassign(FibonacciPQ *PQ);
    int doTreat(void);
    // Handle withdraw
    int doWithdraw(Person *thePerson);
    Person *isIn(string ID);
    int displayAll(void);
};

#endif
