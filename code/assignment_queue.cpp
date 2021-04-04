#include "assignment_queue.hpp"

// assignmentQueue class functions

int assignmentQueue::init(int hc, int wh, int thePlace)
{
    theHospital = thePlace;
    hourCapacity = hc;
    workingHour = wh;
    length = hc * wh;
    occupied = 0;
    timeSlot = new Person *[workingHour * hourCapacity];
    for (int i = 0; i < length; i++)
    {
        timeSlot[i] = NULL;
    }
    return 1;
}

// Clear the timeSlot array.
void assignmentQueue::clear(void)
{
    for (int i = 0; i < workingHour * hourCapacity; i++)
    {
        if (timeSlot[i])
        {
            delete timeSlot[i];
        }
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
int assignmentQueue::addPerson(Person *const thePerson)
{
    if (isFull())
    {
        return 0;
    }
    timeSlot[this->occupied] = thePerson;
    this->occupied++;
    return 1;
}

// Assumption: The Person pointer is not NULL.
int assignmentQueue::deletePerson(Person *thePerson)
{
    for (int i = 0; i < this->length; i++)
    {
        if (timeSlot[i] && thePerson->getID() == timeSlot[i]->getID())
        {
            delete timeSlot[i];
            timeSlot[i] = NULL;
            thePerson->assignLocation(-1);
            occupied--;
            return 1;
        }
    }
    fprintf(stderr, "The person to be deleted has not been assigned to hospital %d. \n", this->theHospital);
    return 0;
}

void assignmentQueue::assignTimeAndLocation(void)
{
    time_t currentTime;
    struct tm *baseTime;
    struct tm aTime;
    int addHour, addMin;
    int increment = 60 / hourCapacity;

    time(&currentTime);
    baseTime = localtime(&currentTime);
    baseTime->tm_sec = 0;
    baseTime->tm_min = 0;
    baseTime->tm_hour = 8;
    baseTime->tm_mday++;
    for (int i = 0; i < workingHour * hourCapacity; i++)
    {
        addHour = i / hourCapacity;
        addMin = (i % hourCapacity) * increment;
        aTime = *baseTime;
        aTime.tm_hour += addHour;
        aTime.tm_min += addMin;
        if (addHour > 3)
        {
            aTime.tm_hour++;
        }
        if (timeSlot[i])
        {
            timeSlot[i]->assignTime(&aTime);
            timeSlot[i]->assignLocation(this->theHospital);
        }
    }
}

int assignmentQueue::display(void)
{
    tm aTime;
    for (int i = 0; i < this->length; i++)
    {
        if (timeSlot[i])
        {
            aTime = timeSlot[i]->getAssignedTime();
            mktime(&aTime);
            cout << "       "
                 << "The appointment information of person with ID " << timeSlot[i]->getID() << " : \n";
            if (timeSlot[i]->getReassigned())
            {
                cout << "       "
                     << "Since the desired hospital is full, this person has been randomly assigned to another hospital other than the desired hospital " << stoi(timeSlot[i]->getContactDetails()) << ". \n";
            }
            cout << "       "
                 << "location:   Hospital " << timeSlot[i]->getAssignedLocation() << "\n";
            cout << "       "
                 << "time:       " << asctime(&aTime) << "\n";
        }
    }
    return 1;
}

// queueManger class functions
//--------------------------------------------------------------------------------------------

// Default length of hospital array is 8.
int queueManger::init(int num)
{
    capacity = (num < 8 ? 8 : num);
    length = 0;
    locations = new assignmentQueue *[capacity];
    for (int i = 0; i < capacity; i++)
    {
        locations[i] = NULL;
    }
    return 1;
}

int queueManger::extendLocations(int hospital)
{
    assignmentQueue **temp = new assignmentQueue *[hospital + 1];
    for (int i = 0; i < capacity; i++)
    {
        temp[i] = locations[i];
    }
    for (int i = capacity; i < hospital + 1; i++)
    {
        temp[i] = NULL;
    }
    capacity = hospital + 1;
    delete locations;
    locations = temp;
    return 1;
}

// Before addition, remember to call this function (initHospital).
int queueManger::addHospital(int hospital, int hc, int wh)
{
    if (hospital >= capacity)
    {
        extendLocations(hospital);
    }
    if (locations[hospital])
    {
        fprintf(stderr, "That hospital has been added already. \n");
        return 0;
    }
    length++;
    locations[hospital] = new assignmentQueue;
    return locations[hospital]->init(hc, wh, hospital);
}

int queueManger::reassign(FibonacciPQ *PQ)
{
    Person *thePerson;
    for (int i = 0; i < capacity; i++)
    {
        if (locations[i])
        {
            locations[i]->clear();
        }
    }

    int noSpace = 0;
    // Distribute Person into each assignment list.
    while (!PQ->isEmpty() && !noSpace)
    {
        // Add new hospital.
        thePerson = PQ->popMin();
        thePerson->setCurrentStage(appointment); // Add for withdraw functionality.
        cout << "Assigning the person with ID " << thePerson->getID() << " ...... \n";
        int theLocation = stoi(thePerson->getContactDetails());
        int otherLocation = std::rand() % capacity;
        if (theLocation >= capacity || NULL == locations[theLocation])
        {
            addHospital(theLocation);
            // fprintf(stderr, "The hospital %d to which the person will be assigned has not been initialized. \n", theLocation);
            // continue;
        }

        if (!locations[theLocation]->addPerson(thePerson))
        {
            thePerson->markReassigned();
            while (NULL == locations[otherLocation] || locations[otherLocation]->isFull())
            {
                otherLocation = std::rand() % capacity;
            }
            locations[otherLocation]->addPerson(thePerson);
        }

        // Checkout whether there is empty space.
        noSpace = 1;
        for (int i = 0; i < capacity; i++)
        {
            if (locations[i])
            {
                noSpace = noSpace & locations[i]->isFull();
            }
        }
        // if (!noSpace)
        // {
        //     cout << "There is empty space." << endl;
        // }
    }
    for (int i = 0; i < capacity; i++)
    {
        if (locations[i])
        {
            locations[i]->assignTimeAndLocation();
        }
    }
    return 1;
}

int queueManger::doWithdraw(Person *thePerson)
{
    if (NULL == thePerson)
    {
        fprintf(stderr, "The person to be deleted has a NULL pointer. \n");
        return 0;
    }
    int theLocation = thePerson->getAssignedLocation();
    if (locations[theLocation] && !locations[theLocation]->deletePerson(thePerson))
    {
        return 0;
    }
    return 1;
}

int queueManger::displayAll(void)
{
    cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
    for (int i = 0; i < capacity; i++)
    {
        if (locations[i])
        {
            cout << endl;
            cout << "The hospital " << locations[i]->getTheHospital() << " have the following assigned people: \n";
            locations[i]->display();
        }
    }
    cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;
    cout << endl;
    return 1;
}