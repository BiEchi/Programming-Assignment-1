#include "FibonacciPQ.h"
#include "Person.hpp"
#include <stdint.h>
#include <cstdlib>
#include <time.h>

class assignmentQueue {
    friend class queueManger;
private:
    int theHospital;
    Person** timeSlot;
    int32_t hourCapacity;
    int32_t occupied;
    int32_t workingHour;
public:
    int init(int hc, int wh, int thePlace);
    void clear(void);
    int isFull(void) {return (occupied == workingHour*hourCapacity ? 1 : 0);}
    int addPerson(Person* thePerson);
    void assignTime(void);
};

class queueManger {
private:
    assignmentQueue** locations;
    int capacity;
    int length;
public:
    int init(int num = 7);
    int extendLocations(int hospital);
    int addHospital(int hospital, int hc, int wh);
    // Handle assignment
    int reassign(FibonacciPQ* PQ);
    // Handle withdraw
    int withdraw(Person* );
};