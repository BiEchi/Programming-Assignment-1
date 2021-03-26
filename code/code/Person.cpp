#include <cstring>
#include <ctime>
#include <iostream>
#include <stdio.h>
#include <vector>
#include "Person.hpp"

using namespace std;

void Person::setID(char *data)
{
    ID = data; // automatically convert char* to string
    return;
}

void Person::setName(char *data)
{
    name = data;
    return;
}

void Person::setContactDetails(char *data)
{
    contactDetails = data;
    return;
}

/// set the year of birth
/// @param data char* YYYY
void Person::setBirthYear(char *data)
{
    birthDate.tm_year = (int)*data;
    return;
}

/// set the month of birth
/// @param data char* MM
void Person::setBirthMonth(char *data)
{
    birthDate.tm_mon = (int)*data;
    return;
}

/// set the day of birth
/// @param data char* DD
void Person::setBirthDay(char *data)
{
    birthDate.tm_mday = (int)*data;
    return;
}

void Person::setProfession(char *data)
{
    profession = (int)*data;
    return;
}

void Person::setRiskStatus(char *data)
{
    profession = (int)*data;
    return;
}

void Person::setLocation(char *data)
{
    location = (int)*data;
    return;
}

void Person::setTimestamp(char *data)
{
    return;
}

bool Person::withdraw(vector<Person> *blacklist_ptr)
{
    if(nullptr == blacklist_ptr)
        blacklist_ptr = &vector<Person>();
    switch (arrangeStage)
    {
    case buffer:
    {
        break;
    }
    case treatment:
    {
        
        break;
    }
    case appointment:
    {
        break;
    }
    default:
    {
        cout << "the patient is in wrong stage" << endl;
        return false;
    }
    }
    return true;
}