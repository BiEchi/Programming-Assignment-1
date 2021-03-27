#include <cstring>
#include <ctime>
#include <iostream>
#include <stdio.h>
#include <vector>
#include "Person.hpp"

using namespace std;

void Person::setID(string data)
{
    ID = data; // automatically convert char* to string
    return;
}

void Person::setName(string data)
{
    name = data;
    return;
}

void Person::setContactDetails(string data)
{
    contactDetails = data;
    return;
}


/// set the year of birth
/// @param data char* YYYY
void Person::setBirthYear(string data)
{
    birthDate.tm_year = stoi(data);
    return;
}

/// set the month of birth
/// @param data char* MM
void Person::setBirthMonth(string data)
{
    birthDate.tm_mon = stoi(data);
    return;
}

/// set the day of birth
/// @param data char* DD
void Person::setBirthDay(string data)
{
    birthDate.tm_mday = stoi(data);
    return;
}

void Person::setProfession(string data)
{
    profession = stoi(data);
    return;
}

void Person::setRiskStatus(string data)
{
    riskStatus = stoi(data);
    return;
}

void Person::setTimestamp(string data)
{
    return;
}

void Person::display()
{
    cout << "The person's Name is " << getName() << endl;
    cout << "The person's ID is " << getID() << endl;
    cout << "The person's Contact Detail is " << getContactDetails() << endl;
    cout << "The person's Birth Date is " << getBirthdate().tm_year << ":" \
        << getBirthdate().tm_mon << ":" << getBirthdate().tm_mday << endl;
    cout << "The person's Profession is " << getProfession() << endl;
    cout << "The person's Risk Status is " << getRiskStatus() << endl;
}
