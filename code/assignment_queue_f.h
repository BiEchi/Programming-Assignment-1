#include "assignment_queue.h"
#include <stdio.h>

// assignmentQueue class functions

int assignmentQueue::init(int hc, int wh, int thePlace) {
    theHospital = thePlace;
    hourCapacity = hc;
    occupied = 0;
    workingHour = wh;
    timeSlot = new Person*[workingHour*hourCapacity];
    this->clear();
    return 1;
}

// Clear the timeSlot array.
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

// queueManger class functions
//--------------------------------------------------------------------------------------------
// Default number of hospital array is 7.
int queueManger::init(int num = 7) {
    capacity = (num < 7 ? 7 : num);
    length = 0;
    locations = new assignmentQueue*[capacity];
    for (int i = 0; i < capacity; i++) {
        locations[i] = NULL;
    }
    return 1;
}

int queueManger::extendLocations(int hospital) {
    assignmentQueue** temp = new assignmentQueue*[hospital+1];
    for (int i = 0; i < capacity; i++) {
        temp[i] = locations[i];
    }
    for (int i = capacity; i < hospital + 1; i ++) {
        temp[i] = NULL;
    }
    capacity = hospital + 1;
    delete locations;
    locations = temp;
    return 1;
}

// Before addition, remember to call this function (initHospital).
int queueManger::addHospital(int hospital, int wh, int hc) {
    if (hospital >= capacity) {
        extendLocations(hospital);
    }
    if (locations[hospital]) {
        fprintf(stderr, "That hospital has been added already. \n"); 
        return 0;
    }
    length++;
    locations[hospital] = new assignmentQueue;
    return locations[hospital]->init(hc, wh, hospital);
}

int queueManger::reassign(FibonacciPQ* PQ) {
    Person* thePerson;
    for (int i = 0; i < capacity; i++) {
        locations[i]->clear();
    }
    int noSpace;
    // Distribute Person into each assignment list.
    while (!PQ->Isempty()) {
        noSpace = 1;
        for (int i = 0; i < capacity; i++) {
            if (NULL == locations[i]) {continue;}
            noSpace = noSpace && locations[i]->isFull(); 
        }
        if (noSpace) {break;}

        thePerson = PQ->Popmin();
        int theLocation = thePerson->getLocation();
        int otherLocation = std::rand()%7;
        if (theLocation >= capacity || NULL == locations[theLocation]) {
            fprintf(stderr, "The hospital to which a person will be assigned has not been initialized. \n");
            continue;
        }
        if(!locations[theLocation]->addPerson(thePerson)) {
            do {
                while (NULL == locations[otherLocation]) {
                    otherLocation = std::rand()%capacity;
                }
            } while (!locations[otherLocation]->addPerson(thePerson));
        }
    for (int i = 0; i < 7; i++) {
        if (locations[i]) {locations[i]->assignTime();}
    }
    return 1;
}