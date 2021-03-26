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
    void init(int hc, int wh, int thePlace);
    void clear(void);
    int isFull(void) {return (occupied == workingHour*hourCapacity ? 1 : 0);}
    int addPerson(Person* thePerson);
    void assignTime(void);
};

class queueManger {
private:
    assignmentQueue* locations;
public:
    void init(int a = 2, int b = 2, int c = 2, int d = 2, int e = 2, int f = 2, int g = 2, int ah = 8, int bh = 8, int ch = 8, int dh = 8, int eh = 8, int fh = 8, int gh = 8);
    // Handle assignment
    int reassign(FibonacciPQ* PQ);
    // Handle withdraw
    int withdraw(Person* );
};

//--------------------------------------------------------------------------------------------
void assignmentQueue::init(int hc, int wh, int thePlace) {
    theHospital = thePlace;
    hourCapacity = hc;
    occupied = 0;
    workingHour = wh;
    timeSlot = new Person*[workingHour*hourCapacity];
    this->clear();
    return;
}

void assignmentQueue::clear(void) {
    for (int i = 0; i < workingHour*hourCapacity; i++) {
        timeSlot[i] = NULL;
    }
    occupied = 0;
    return;
}

/*
 * OUTPUT: 
 *  1   when add a person to the queue successfully
 *  0   when the queue is full
 */

int assignmentQueue::addPerson(Person* thePerson) {
    if(isFull()) {return 0;}
    timeSlot[this->occupied];
    this->occupied++;
    thePerson->assignLocation(this->theHospital);
    return 1;
}

void assignmentQueue::assignTime(void) {
    time_t currentTime;
    struct tm *baseTime;
    struct tm aTime;
    int addHour, addMin;
    int increment = 60/hourCapacity;

    time(&currentTime);
    baseTime = localtime(&currentTime);
    baseTime->tm_sec = 0;
    baseTime->tm_min = 0;
    baseTime->tm_hour = 8;
    baseTime->tm_mday++;
    for (int i = 0; i < workingHour*hourCapacity; i++) {
        addHour = i/hourCapacity;
        addMin = (i%hourCapacity)*increment;
        aTime = *baseTime;
        aTime.tm_hour += addHour;
        aTime.tm_min += addMin;
        if(addHour > 3) {aTime.tm_hour++;}
        timeSlot[i]->assignTime(&aTime);
    }
}

//--------------------------------------------------------------------------------------------
void queueManger::init(
    int a = 2, int b = 2, int c = 2, int d = 2, int e = 2, int f = 2, int g = 2,
    int ah = 8, int bh = 8, int ch = 8, int dh = 8, int eh = 8, int fh = 8, int gh = 8
    ) 
{
    int hourCapacityArray[7] = {a, b, c, d, e, f, g};
    int workingHourArray[7] = {ah, bh, ch, dh, eh, fh, gh};
    int hospitals[7] = {A, B, C, D, E, F, G};
    locations = new assignmentQueue[7];
    for (int i = 0; i < 7; i++) {
        locations[i].init(hourCapacityArray[i], workingHourArray[i], hospitals[i]); 
    }
    return;
}

int queueManger::reassign(FibonacciPQ* PQ) {
    Person* thePerson;
    for (int i = 0; i < 7; i++) {
        locations[i].clear();
    }
    int noSpace;
    // Distribute Person into each assignment list.
    while (!PQ->Isempty()) {
        noSpace = 1;
        for (int i = 0; i < 7; i++) {
            noSpace = noSpace && locations[i].isFull(); 
        }
        if (noSpace) {break;}

        thePerson = PQ->Popmin();
        int otherLocation = std::rand()%7;
        switch (thePerson->getLocation())
        {
        case A:
            if(!locations[A].addPerson(thePerson)) {
                while(!locations[std::rand()%7].addPerson(thePerson));
            };
            break;
        case B:
            if(!locations[B].addPerson(thePerson)) {
                while(!locations[std::rand()%7].addPerson(thePerson));
            };
            break;
        case C:
            if(!locations[C].addPerson(thePerson)) {
                while(!locations[std::rand()%7].addPerson(thePerson));
            };
            break;
        case D:
            if(!locations[D].addPerson(thePerson)) {
                while(!locations[std::rand()%7].addPerson(thePerson));
            };
            break;
        case E:
            if(!locations[E].addPerson(thePerson)) {
                while(!locations[std::rand()%7].addPerson(thePerson));
            };
            break;
        case F:
            if(!locations[F].addPerson(thePerson)) {
                while(!locations[std::rand()%7].addPerson(thePerson));
            };
            break;
        case G:
            if(!locations[G].addPerson(thePerson)) {
                while(!locations[std::rand()%7].addPerson(thePerson));
            };
            break;
        }
    }
    for (int i = 0; i < 7; i++) {
        locations[i].assignTime();
    }
    return 1;
}