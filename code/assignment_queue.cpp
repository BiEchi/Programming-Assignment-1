#include "assignment_queue.hpp"
#include "TimePredef.hpp"
#include <unistd.h>

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
void assignmentQueue::clear(vector<Person> *treated)
{
    for (int i = 0; i < workingHour * hourCapacity; i++)
    {
        if (timeSlot[i])
        {
            treated->push_back(*timeSlot[i]);
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
    int32_t diffday;
    struct tm *baseTime;
    struct tm aTime;
    int addHour, addMin;
    int increment = 60 / hourCapacity;

    time(&currentTime);
    diffday = difftime(currentTime, startTime)/10; // Compute the difference between start time and current system time.
    baseTime = localtime(&startTime);
    baseTime->tm_sec = 0;
    baseTime->tm_min = 0;
    baseTime->tm_hour = 8;
    baseTime->tm_mday += diffday;
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

Person* assignmentQueue::isIn(string ID)
{
    for (int i = 0; i < this->length; i++)
    {
        if(timeSlot[i])
        {
            if (timeSlot[i]->getID() == ID) {return timeSlot[i];}
        }
    }
    return NULL;
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
            usleep(100000);
            cout << "       "
                 << "The appointment information of person with ID " << timeSlot[i]->getID() << " : \n";
            if (timeSlot[i]->getReassigned())
            {
                usleep(100000);
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

/**
 * @brief Initialize the instance. 
 * Default length of hospital array is 8. length >= 8
 * 
 * @param num the capacity of hospital array. 
 * @return 1 for indication.  
 */
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

/**
 * @brief Extand the length of hospital array. 
 * Allocate a new array and copy all the hospital into the new array. 
 * 
 * @param hospital 
 * @return 1 for indication. 
 */
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

/**
 * @brief Add a new hospital into the 
 * Before addition, remember to call this initHospital function.
 * 
 * @param hospital 
 * @param hc 
 * @param wh 
 * @return int 
 */
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
            locations[i]->clear(&treated_list);
        }
    }
    for (int i = 0; i < assignment_list.size(); i++)
    {
        assignment_list.pop_back();
    }

    int noSpace = 0;
    // Distribute Person into each assignment list.
    while (!PQ->isEmpty() && !noSpace)
    {
        // Add new hospital.
        thePerson = PQ->popMin();
        thePerson->setCurrentStage(appointment); // Add for withdraw functionality.
        usleep(100000);
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

        assignment_list.push_back(*thePerson);
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

Person* queueManger::isIn(string ID)
{
    Person* temp;
    for (int i = 0; i < this->capacity; i++)
    {
        if (locations[i]) 
        {
            temp = locations[i]->isIn(ID);
            if (temp) {return temp;}
        }
    }
    return NULL;
}

int queueManger::displayAll(void)
{
    for (int i = 0; i < capacity; i++)
    {
        if (locations[i])
        {
            usleep(500000);
            cout << endl;
            system("echo '\33[33mA new hospital is created.\33[0m' ");
            cout << "The hospital " << locations[i]->getTheHospital() << " have the following assigned people: \n";
            sleep(1);
            locations[i]->display();
        }
    }
    cout << endl;
    return 1;
}
